#include "ma.h" 
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

/*
struct artigo
{
	char name[LENGTH];
	double price;
	size_t code[7]; 
};

Artigo create_Artigo(char n[LENGTH], double p, size_t c) //abrir ficheiro e escrever lá
{
	Artigo a = malloc(sizeof(struct artigo));
	memcpy(a->name,n,LENGTH);
	a->price = p;
	a->code = c;

	return a;
}

void destroy_Artigo(Artigo a)
{
	free(a);
}
*/

/**** Gets e Sets para alterar os dados *****/

/*

char* nameArtigo(Artigo a)
{
	return a->name;
}

void changeName(Artigo a, char new_name[LENGTH])
{
	memcpy(a->name,new_name,LENGTH);
}	

double priceArtigo(Artigo a)
{
	return a->price;
}

void changePrice(Artigo a, double new_price)
{
	a->price = new_price;
}

*/

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

