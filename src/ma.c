#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
//#include "ma.h" 


//FORMATO : <ref> <size> <price>
//size_artigos = sizeof(int) + sizeof(short) + sizeof(float) 
#define size_artigos 10


/*
	Função que adiciona o nome de artigo no final do ficheiro strings e devolve a referência
*/
int insertString(char* name, short size)
{
	int ref = 0;
	int fd = open("strings", O_CREAT | O_WRONLY, 0600);

	if(fd == -1)
	{
		perror("Unable to open file strings");
		_exit(-1);
	}
	else
	{	
		ref = lseek(fd, 0, SEEK_END);
		write(fd, name, size);
	}
	close(fd);
	return ref;
}


/*
	Função que insere um artigo no fim do ficheiro artigos ǵerando e devolvendo o código 
*/
int insertArtigo(char* name, float price)
{
	int code = -1;
	int fd = open("artigos", O_CREAT | O_RDWR , 0600);

	if(fd == -1)
	{
		perror("Unable to open file stocks");
		_exit(-1);
	}
	else
	{	
		short size = strlen(name);
		int ref = 0;

		code = lseek(fd, 0, SEEK_END);

		ref = insertString(name, size);
		code += write(fd, &ref, sizeof(int));

		code += write(fd, &size, sizeof(short));

		code += write(fd, &price, sizeof(float));
	}
	close(fd);

	return (code/size_artigos);
}

// Função que recebe um codigo, vai ao ficheiros de artigos e altera o preço desse artigo
void changePrice(int code, float newp)
{
	int fd = open("artigos", O_WRONLY);
	if(fd == -1)
	{
		perror("Unable to open file");
		_exit(-1);
	}
	else
	{
		lseek(fd, (code - 1)*size_artigos, SEEK_SET);  //(code-1) porque os códigos começam no 1
		lseek(fd, sizeof(int)+sizeof(short), SEEK_CUR); 
		write(fd, &newp, sizeof(float));
	}
	close(fd);

}

//Função que vai ao ficheiros de artigos e acrescenta no fim do ficheiro o nome novo
int renameStr(char* new_name)
{	
	int ref = -1;
	int fd = open("strings", O_WRONLY);
	if(fd == -1)
	{
		perror("Unable to open file");
		_exit(-1);
	}
	else
	{	
		ref = lseek(fd, 0 ,SEEK_END);
		write(fd, new_name, strlen(new_name));
	}
	close(fd);
	return ref;
}

//Função que faz update da referencia
void updateRef(int code, int ref, short size)
{
	int fd = open("artigos", O_WRONLY);
	if(fd == -1)
	{
		perror("Unable to open file");
		_exit(-1);
	}
	else
	{
		short t;
		lseek(fd, (code-1) *size_artigos, SEEK_SET);
		
		write(fd, &ref, sizeof(int));
		write(fd, &size, sizeof(short));
	}
	close(fd);
}

//Função que faz parsing de uma linha
void parse(char* buff, char** str){

	char* tok;
	tok = strtok(buff, " ");
	int i;
	for( i = 0; tok; i++){
		str[i] = strdup(tok);
		tok = strtok(NULL, " ");
	}
}
/*
//função que verifica se o lixo já chegou a 20%
int checkTrash(){}
	


//função que faz a limpeza do ficheiro strings
void cleanSTR()
{

}





// funcao que apaga um artigo, corre o ficheiro STRINGS = mesmo nome, mesmo preco -> delete
void deleteArtigo(char[LENGTH] name, float price)
{
	int fp = open("strings", O_TRUNC | O_RDWR, 0777);
	while(!EOF)
	{
		

	}

 //flush
}


//«««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

/*
	Função que imprime os artigos, 
	Recebe quantos artigos quer imprimir
	APENAS PARA TESTES
*/


void printfArtigos(int n){

	int fd = open("artigos", O_RDONLY);

	if(fd == -1){
			perror("Unable to open file strings");
			_exit(-1);
		}
	else{
			short size = -1;
			int ref = -1;
			float price = 0.0; 
			while(n > 0){
			

			read(fd, &ref, 4);
			printf("Ref: %d\n", ref);
		//	write(1, &ref, 4);

			read(fd, &size, 2);
			printf("Size: %d\n", size);
		//	write(1, &size, 2);

			read(fd, &price, 4);
			printf("Price: %f\n", price);
		//	write(1, &price, 4);
			n--;
		}
	}
	 close(fd);

}

/*
	Função que imprime as strings, 
	APENAS PARA TESTES
*/
void printStrings(int size){

	int fd = open("strings", O_RDONLY);

	if(fd == -1){
		perror("Unable to open file strings");
		_exit(-1);
	}
	else{
		char buff[size];

		int r = read(fd, buff, sizeof(char)*size);

		close(fd);

		write(1, buff, r);
	}

}




	

int main(int argc, char *argv[]){
	char* buff = malloc(40);
	int r ;
	
	while( (r = read(0, buff, 39)) ){
			//checkTrash();
			
			buff[r+1] = "\0";

			if(buff[0] == 'i')
			{
				char** args = malloc(sizeof(char*));
				
				parse(buff, args);

				insertArtigo(args[1], atof(args[2]));

				//Pipe para o sv
					int fd = open("art", O_WRONLY);
					if(fd < 0){
						perror("Unable to open pipe art");
						_exit(-1);
					}
					else{
						write(fd, "1", 1);
						close(fd);
					}

				free(args);
			}
	

			if(buff[0] == 'n')
			{
				char** args = malloc(sizeof(char*));
				
				parse(buff, args);

				int ref = renameStr(args[2]);
				updateRef( atoi(args[1]), ref, (short)strlen(args[2]));

				free(args);
				
			}
			
			if(buff[0] == 'p') 
			{
				char** args = malloc(sizeof(char*));
				
				parse(buff, args);
				
				changePrice(atoi(args[1]), atof(args[2]));
				
				free(args);
			}
			
		}
		free(buff);

	return 0;
}

