#include "ma.h" 
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int insertString(char* name, int size)
{
	int ref = 0;
	int w = -1;
	int fd = open("strings.txt", O_CREAT | O_WRONLY, 0600);

	if(fd == -1)
	{
		perror("Unable to open file strings");
		exit(-1);
	}
	else
	{
		ref = lseek(fd, 0, SEEK_END);
		w = write(fd, name, size);
	}
	close(fd);
	return ref;
}


void insertArtigo(char* name, double price)
{
	int size = strlen(name);
	int code = 0;
	int ref = 0;
	int w = -1;

	int fd = open("artigos.txt", O_CREAT | O_RDWR , 0600);

	if(fd == -1)
	{
		perror("Unable to open file stocks");
		exit(-1);
	}
	else
	{	
		lseek(fd, -(2*sizeof(int)+sizeof(double)), SEEK_END);
		read(fd, &code, sizeof(int));

		code++;
		lseek(fd, 0, SEEK_END);
		w = write(fd, &code, sizeof(int));

		ref = insertString(name, size);
		w += write(fd, &ref, sizeof(int));

		w += write(fd, &price, sizeof(double));
	}
	close(fd);
}

void printfArtigos(){
	int code = 0;
	int ref = 0;
	double q = 0.0;
	int r = -1;
	int w = -1;

	int fd = open("artigos.txt", O_RDONLY);


		for(int i = 0; r != 0; i++){
			r = read(fd, &code, sizeof(int));
			//w = write(1, &code, sizeof(int));
			printf("Code: %d\n", code);

			r = read(fd, &ref, sizeof(int));
			//w += write(1, &ref, sizeof(int));
			printf("Ref: %d\n", ref);

			r = read(fd, &q, sizeof(double));
			//w += write(1, &q, sizeof(double));
			printf("Price: %f\n", q);
		}

	 close(fd);

}

void printStrings(){

char buff[4];

	int fd = open("strings.txt", O_RDONLY);

	if(fd == -1){
		perror("Unable to open file strings");
		exit(-1);
	}
	else{
	read(fd, buff, sizeof(char)*4);

	close(fd);

	write(1, buff, sizeof(char)*4);
	}

}

/**

// funcao que apaga um artigo, corre o ficheiro STRINGS = mesmo nome, mesmo preco -> delete
void deleteArtigo(char[LENGTH] name, double price)
{
	int fp = open("STRINGS.txt", O_TRUNC | O_RDWR, 0777);
	while(!EOF)
	{
		

	}

 //flush
}
**/

// Função que recebe um codigo, vai ao ficheiros de artigos e retorna o preço desse artigo
double getPrice(int code)
{
	double price;
	int fd = open("artigos.txt", O_RDONLY);

	if(fd == -1)
	{
		perror("Unable to open file");
		exit(-1);
	}
	else
	{
		lseek(fd, code*(sizeof(int)*2+sizeof(double)), SEEK_SET);
		lseek(fd, 2*sizeof(int), SEEK_CUR);
		read(fd, &price, sizeof(double));
		close(fd);
	}

	return price;
}

// Função que recebe um codigo, vai ao ficheiros de artigos e altera o preço desse artigo
void changePrice(int code, double newp)
{
	int fd = open("artigos.txt", O_RDONLY);
	if(fd == -1)
	{
		perror("Unable to open file");
		exit(-1);
	}
	else
	{
		lseek(fd, code*(sizeof(int)*2+sizeof(double)), SEEK_SET); 
		lseek(fd, 2*sizeof(int), SEEK_CUR); 
		write(fd, &newp, sizeof(double));
		close(fd);
	}

}

//Função que recebe um codigo, vai ao ficheiros de artigos e altera o nome desse artigo
int rename(int code, char* new_name)
{
	int fd = open("strings.txt", O_WRONLY);
	if(fd == -1)
	{
		perror("Unable to open file");
		exit(-1);
	}
	else
	{

		int ref = lseek(fd, 0 ,SEEK_END);
		write(fd, new_name, strlen(new_name));
		close(fd);
	}
	return ref;
}

//Função que faz update da referencia
void updateRef(int code, int ref)
{
	int fd = open("artigos.txt", O_WRONLY);
	if(fd == -1)
	{
		perror("Unable to open file");
		exit(-1);
	}
	else
	{
		lseek(fd, code*(sizeof(int)*2+sizeof(double)), SEEK_SET); 
		lseek(fd, sizeof(int), SEEK_CUR); 
		write(fd, &ref, sizeof(int));
		close(fd);
	}
}

void cleanSTR()
{

}

int main(int argc, char *argv[]) //main do MA
{
	/**if(argv[1] == i)
	{
		//( <nome> <preco> ) -> insere
	}
	if(argv[1] == n)
	{
		// n ( <codigo> <new_nome> ) -> altera nome
	}
	if(argv[1] == p)
	{
		// p ( <codigo> <new_preco> ) -> altera preco
	}

	*/
	insertArtigo("asdf", 2.0);
	printfArtigos();
	printStrings();

	return 0;
}

