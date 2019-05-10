#include "../include/aux.h"
#include "../include/ma.h" 


ssize_t readln(int fildes, void *buff, size_t n){ 
    char c ;
    size_t s = 0;
    char* temp = (char *)buff;

    while( s < n && read(fildes, &c, 1) == 1 ){      
        if(c == '\0')
        	return s;
        temp[s++] = c;
        if(c == '\n')
        	return s;
    }

    return s;
}

//Função que faz parsing de uma linha
int parse(char* buff, char** str){

	char* tok;
	tok = strtok(buff, " ");
	int i;
	for( i = 0; tok; i++){
		str[i] = strdup(tok);
		tok = strtok(NULL, " ");
	}
	return i;
}

//------------------------------------------------------
#define size_artigos 10


/*
	Função que adiciona o nome de artigo no final do ficheiro strings e devolve a referência
*/
int insertString(char* name, short size)
{
	int ref = 0;
	int fd = open("strings", O_CREAT | O_WRONLY, 0664);

	if(fd == -1)
		_exit(-1);
	else
	{	
		ref = lseek(fd, 0, SEEK_END);
		write(fd, name, size);
	}
	close(fd);
	return ref;
}


/*
	Função que insere um artigo no fim do ficheiro artigos gerando e devolvendo o código 
*/
int insertArtigo(char* name, float price)
{
	int code = -1;
	int fd = open("artigos", O_CREAT | O_RDWR , 0664);

	if(fd == -1)
		_exit(-1);
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
		_exit(-1);
	else
	{
		lseek(fd, (code - 1)*size_artigos, SEEK_SET);  //(code-1) porque os códigos começam no 1
		lseek(fd, sizeof(int)+sizeof(short), SEEK_CUR); 
		write(fd, &newp, sizeof(float));
	}
	close(fd);

}


//Função que vai ao ficheiros de artigos e acrescenta no fim do ficheiro o nome novo
int renameStr(int code, char* new_name)
{	
	int ref = -1;
	int fd = open("strings", O_WRONLY);
	if(fd == -1)
		_exit(-1);
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
		_exit(-1);
	else
	{
		lseek(fd, (code-1) *size_artigos, SEEK_SET);
		
		write(fd, &ref, sizeof(int));
		write(fd, &size, sizeof(short));
	}
	close(fd);
}

//função que devolve o tamanho de um artigo dado o seu código
short getSize(int code)
{
	short size;
	int fd = open("artigos", O_RDONLY);
	if(fd == -1)
		_exit(-1);
	else
	{
		lseek(fd, (code - 1)*size_artigos, SEEK_SET);  //(code-1) porque os códigos começam no 1
		lseek(fd, sizeof(int), SEEK_CUR); 
		read(fd, &size, sizeof(short));
	}
	close(fd);
	return size;
}

// Função que recebe um codigo, vai ao ficheiros de artigos e retorna o preço desse artigo
float getPrice(int code)
{
	float price;
	int fd = open("artigos", O_RDONLY);

	if(fd == -1)
		_exit(-1);
	else
	{
		lseek(fd, (code-1)*10, SEEK_SET);
		lseek(fd, 6, SEEK_CUR);
		read(fd, &price, sizeof(float));
	}
	close(fd);
	return price;
}


/*
	Função que acrescenta um codigo de artigo ao ficheiro stocks,
	sempre que for acrescentado no ficheiro ARTIGOS (ou seja, pelo ma).
*/
void stockAppend(){
	int q = 0;
	int w = -1;
	int fd = open("stocks", O_WRONLY | O_CREAT,0664);

	if(fd == -1)
		_exit(-1);
	else{
		lseek(fd, 0, SEEK_END);
		w += write(fd, &q, sizeof(int) );
	}
	close(fd);
}

	

int main(int argc, char *argv[]){
	char* buff = malloc(150);
	int r ;
	
	while(1){
		while( (r = readln(0, buff, 150)) ){
				
				buff[r+1] = '\0';

				if(buff[0] == 'i')
				{
					char** args = malloc(sizeof(char**));
					parse(buff, args);
					float p = atof(args[2]);

					if(p > 0){
						int code = insertArtigo(args[1], atof(args[2]));

						char c[150];
						sprintf(c, "%d\n", code);

						write(1, c, strlen(c));

						stockAppend();
					}

					free(args);
				}
		

				if(buff[0] == 'n')
				{
					char** args = malloc(sizeof(char**));
					
					parse(buff, args);
					int code  = atoi(args[1]);

					if(code > 0){
						int ref = renameStr(code , args[2]);
						updateRef( code, ref, (short)strlen(args[2]));
					}

					free(args);
					
				}
				
				if(buff[0] == 'p') 
				{
					char** args = malloc(sizeof(char**));
					
					parse(buff, args);
					int code  = atoi(args[1]);
					float p = atof(args[2]);
					
					if(code > 0 && p > 0)
						changePrice(code, p);
						
					free(args);
				}
				
			}
	}
	
	free(buff);
	return 0;
}


