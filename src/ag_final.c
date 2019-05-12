#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


int append_file(char* head, char* tail){

	int cod, quantidade, montante;
	int fd_1 = open(head, O_WRONLY, 0644);
	int fd_2 = open(tail, O_RDONLY, 0644);

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


char* creat_file(int pid){
	char* nome = malloc(6);
	sprintf(nome, "%d", pid);

	int fd = open(nome, O_CREAT, 0777);
	close(fd);
	
	return nome;
}


int agregacao_simples(char* filename, char* new_file, int init, int fim)
{
	int num_linhas;
	int i, c, cod, quantidade, montante, q, m;
	int fd = open(filename, O_RDWR| O_CREAT, 0777);
	int n_fd = open(new_file, O_WRONLY, 0777);

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


void agregacao_final(char* filename, char* new_file, int init, int fim, int num)
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
			if((j/12) % 200 == 0) printf("%d / %d (%d) . final\n", j/12, fim/12, fim);
		}
	}

	close(fd);
	close(n_fd);
}


void split_work(char* filename, char* new_file, int init)
{
	char* nome_pid = malloc(6);
	int pid, status, num, y = init;
	
	int fd = open(filename, O_RDONLY);
	int size = lseek(fd, init, SEEK_END); // determina o tamanho do ficheiro a partir de onde se quer começar
	close(fd);
	
	int fdi = open("file_intermedio", O_RDWR | O_CREAT);

	if (size < 10000) num = 2;
	else num = size % 10;

	printf("size %d, vou fazer %d forks\n", size, num);
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
			printf("\t%d . .", append_file("file_intermedio", nome_pid));
			remove(nome_pid);
			printf("\tacabei um fork %d, apaguei o %s\n", i, nome_pid);
		}

	printf("vou agregar tudo\n");

	agregacao_final("file_intermedio", new_file, 0, lseek(fdi, 0, SEEK_END), num);

	close(fdi);
	remove("file_intermedio");
}


int main(){

	clock_t start, end;
	double cpu_time_used;
	start = clock();

	split_work("vendas_in", "vendas_out", 0);

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\n\n\tCPU Time:%f\n\n", cpu_time_used );

	return 0;
}
