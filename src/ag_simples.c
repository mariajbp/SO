#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


int agregacao_simples(char* filename, int init, int fim)
{
	
	int num_linhas;
	int i, c, cod, quantidade, montante, q, m;
	int fd = open(filename, O_RDWR | O_CREAT, 0644);

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
				lseek(fd, num_linhas, SEEK_SET);
				
				write(fd, &cod, sizeof(int));
				write(fd, &quantidade, sizeof(int));
				write(fd, &montante, sizeof(float));
			}
			else lseek(fd, sizeof(int) + sizeof(float), SEEK_CUR);
			num_linhas += (2*sizeof(int) + sizeof(float)) - 1;

			if((num_linhas/12) % 100 == 0) printf("a.%d / %d\n", num_linhas/12, fim/12);
		}
	}

	close(fd);
	return num_linhas;
}

void agregacao_final(char* filename, char* new_file, int init, int fim)
{
	int c, cod, quantidade, montante, q, m;
	int fd = open(filename, O_RDWR, 0644);
	int n_fd = open(new_file, O_WRONLY, 0644);

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

						break;
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

			if((j/12) % 100 == 0) printf("b.%d / %d\n", j/12, fim/12);
		}
	}

	close(fd);
	close(n_fd);
}


int main(){

	clock_t start, end;
	double cpu_time_used;
	start = clock();

	int fd = open("vendas_0_1", O_RDONLY);
	int size = lseek(fd, 0, SEEK_END); // determina o tamanho do ficheiro a partir de onde se quer começar
	close(fd);

	agregacao_simples("vendas_0_1", 0, size);
	agregacao_final("vendas_0_1", "vendas_1_1", 0, size);

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("CPU Time:%f\n", cpu_time_used );

	return 0;
}