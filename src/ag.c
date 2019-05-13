#include "../include/ag.h"

//Função que faz parsing de uma linha
int parse(char* buff, char** str){

	char* tok;
	tok = strtok(buff, " ");
	int i;

	for( i = 0; tok ; i++){
		str[i] = strdup(tok);
		tok = strtok(NULL, " ");
	}
	return i;
}

// Função que dá append de um ficheiro tail num ficheiro head
int append_file(const char* head, const char* tail){

	int cod, quantidade, montante;
	int fd_1 = open(head, O_WRONLY);
	int fd_2 = open(tail, O_RDONLY);

	int size1 = lseek(fd_1, 0, SEEK_END); // determina o tamanho do ficheiro 1
	int size2 = lseek(fd_2, 0, SEEK_END); // determina o tamanho do ficheiro 2

	lseek(fd_2, 0, SEEK_SET);

	for (int i = 0; i < size2; i++)
	{
		read(fd_2, &cod, sizeof(int));
		read(fd_2, &quantidade, sizeof(int));
		read(fd_2, &montante, sizeof(float));
		
		write(fd_1, &cod, sizeof(int));
		write(fd_1, &quantidade, sizeof(int));
		write(fd_1, &montante, sizeof(float));

		i += (2*sizeof(int) + sizeof(float)) - 1;
	}

	close(fd_1);
	close(fd_2);

	return (size1 + size2);
}

// Função cria um ficheiro com o nome de um inteiro
char* creat_file(int pid){
	char* nome = malloc(6);
	sprintf(nome, "%d", pid);

	int fd = open(nome, O_CREAT, 0644);
	close(fd);
	
	return nome;
}

// Função que agrega um ficheiro de formato vendas de forma sequencial, do inicio escolhido ao fim escolhido
int agregacao_simples(const char* filename, const char* new_file, int init, int fim)
{
	int num_linhas;
	int i, c, cod, quantidade, montante, q, m;
	int fd = open(filename, O_RDWR| O_CREAT, 0644);
	int n_fd = open(new_file, O_WRONLY);

	if(fd == -1)
		_exit(-1);
	else
	{
		lseek(fd, init, SEEK_SET); // coloca o fd na posicao inicial para agregacao

		for(num_linhas = init; num_linhas < fim - (2*sizeof(int) + sizeof(float)); num_linhas++)
		{
			read(fd, &cod, sizeof(int));
			if(cod)
			{
				read(fd, &quantidade, sizeof(int));
				read(fd, &montante, sizeof(float));
				for(i = num_linhas; i < fim; i++)
				{
					read(fd, &c, sizeof(int));

					if(c == cod)
					{
						c = 0;
						lseek(fd, -(sizeof(int)), SEEK_CUR);
						write(fd, &c, sizeof(int));

						read(fd, &q, sizeof(int));
						read(fd, &m, sizeof(float));

						quantidade += q;
						montante += m;
					}
					else lseek(fd, sizeof(int) + sizeof(float), SEEK_CUR);
					i += (2*sizeof(int) + sizeof(float)) - 1;
				}
				lseek(fd, num_linhas + 2*sizeof(int) + sizeof(float), SEEK_SET);
				
				write(n_fd, &cod, sizeof(int));
				write(n_fd, &quantidade, sizeof(int));
				write(n_fd, &montante, sizeof(float));
			}
			else lseek(fd, sizeof(int) + sizeof(float), SEEK_CUR);
			num_linhas += (2*sizeof(int) + sizeof(float)) - 1;
		}
	}

	close(fd);
	close(n_fd);
	return num_linhas;
}

// Função que agrega um ficheiro de formato vendas de forma sequencial, do inicio escolhido ao fim escolhido
void agregacao_final(const char* filename, const char* new_file, int init, int fim, int num)
{
	int x, c, cod, quantidade, montante, q, m;
	int fd = open(filename, O_RDWR, 0644);
	int n_fd = open(new_file, O_WRONLY | O_CREAT, 0644);

	if(fd == -1)
		_exit(-1);
	else
	{
		lseek(fd, init, SEEK_SET); // coloca o fd na posicao inicial para agregacao

		for(int j = init; j < fim - (2*sizeof(int) + sizeof(float)); j++)
		{
			read(fd, &cod, sizeof(int));
			if(cod)
			{
				x = 0;
				read(fd, &quantidade, sizeof(int));
				read(fd, &montante, sizeof(float));
				for(int i = j; i < fim; i++)
				{
					read(fd, &c, sizeof(int));

					if(c == cod)
					{
						c = 0;
						lseek(fd, -(sizeof(int)), SEEK_CUR);
						write(fd, &c, sizeof(int));

						read(fd, &q, sizeof(int));
						read(fd, &m, sizeof(float));

						quantidade += q;
						montante += m;

						x++;
						if(x == num) break;
					}
					else lseek(fd, sizeof(int) + sizeof(float), SEEK_CUR);
					i += (2*sizeof(int) + sizeof(float)) - 1;
				}
				write(n_fd, &cod, sizeof(int));
				write(n_fd, &quantidade, sizeof(int));
				write(n_fd, &montante, sizeof(float));

				lseek(fd, j + sizeof(int) + sizeof(float), SEEK_SET);
			}
			else lseek(fd, sizeof(int) + sizeof(float), SEEK_CUR);
			
			j += (2*sizeof(int) + sizeof(float)) - 1;
		}
	}

	close(fd);
	close(n_fd);
}

// Função que cria concorrencia dos processos de agregação
void split_work(const char* filename, const char* new_file, int init)
{
	char* nome_pid = malloc(6);
	int pid, status, num, y = init;
	
	int fd = open(filename, O_RDONLY);
	int size = lseek(fd, init, SEEK_END); // determina o tamanho do ficheiro a partir de onde se quer começar
	close(fd);
	
	int fdi = open("file_intermedio", O_RDWR | O_CREAT, 0644);

	if (size < 10000) num = 2;
	else num = size % 10;

	
	for (int i = 0; i <= size; i += (size/num) )
	{
		if(!(y == 0 && i == 0)){
			if(!fork())
			{
				nome_pid = creat_file(getpid());
				agregacao_simples(filename, nome_pid, y, i);
				_exit(1);
			}
			y = i;
		}
	}
	for (int i = 0; i <= num; i++)
		if((pid = wait(&status)) != -1){
			sprintf(nome_pid, "%d", pid);
			append_file("file_intermedio", nome_pid);
			remove(nome_pid);
		}


	agregacao_final("file_intermedio", new_file, 0, lseek(fdi, 0, SEEK_END), num);

	close(fdi);
	remove("file_intermedio");
}


int main(int argc, char const *argv[]){
	//O agregador recebe o nome do ficheiro a agregar, o ficheiro onde se vai colocar a agregação e o inicio pretendido da agregação.
	
	if(argc == 4){
		
		split_work(argv[1], argv[2], atoi(argv[3]));
	}

	return 0;
}
