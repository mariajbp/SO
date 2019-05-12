#include "../include/aux.h"
#include "../include/ma.h" 



ssize_t readln(int fildes, void* buff, size_t n){ 
    char c = ' ';
    size_t s = 0, r = 1;
    char* temp = (char *)buff;

    while( (s < n) && r && (c != '\n')){  

    	r = read(fildes, &c, 1);

        if(r && (c != '\n')){
        	temp[s] = c;
        	s++;
        }
    }
    temp[s] = 0;
    if(s == 0 && temp[s] == '\n')
    	return -1;

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
	int lixo = 0;
	int fd = open("strings", O_CREAT | O_WRONLY, 0664);

	if(fd == -1)
		_exit(-1);
	else
	{	if( (lseek(fd, 0 , SEEK_END)) == 0 ){
			lixo = 0;
			write(fd, &lixo, sizeof(int));
		}
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


//Função que vai ao ficheiros strings e acrescenta no fim do ficheiro o nome novo
int renameStr(int code, char* new_name, short size)
{	
	int ref = -1;
	int fd = open("strings", O_RDWR);
	int lixo;

	if(fd == -1)
		_exit(-1);
	else
	{	
		//Ler o lixo
		read(fd, &lixo, sizeof(int));
		
		//Incrementar o lixo
		lixo = lixo+size;

		//Escrever o lixo
		lseek(fd, 0, SEEK_SET);
		write(fd, &lixo, sizeof(int));

		//Update ref
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
		int r = read(fd, &size, sizeof(short));
		if(r == 0)
			_exit(0);
	}
	close(fd);
	return size;
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

//calculo dos 20%
int twenty()
{
	int res = 0, lixo, fd;
	fd = open("strings", O_RDONLY);
	read(fd, &lixo, sizeof(int));
	lseek(fd, -sizeof(int), SEEK_CUR);
	int fsize = lseek(fd, 0, SEEK_END);
	close(fd);

	if( lixo >= (fsize*0.2) )
		return 1;	

	return res;
}

//	
void clearTrash()
{
	int fd, fs, fa, code, ref, lixo = 0;
	short size;
	
	//Ficheiro temporário das strings
	fd = open("temp", O_CREAT | O_WRONLY, 0644);
	int w = write(fd, &lixo, sizeof(int));

	//Calcular o número de códigos totais
	fa = open("artigos", O_RDONLY);
	int codeT = lseek(fa, 0, SEEK_END);
	codeT = codeT/(size_artigos);
	close(fa);

	//Copiar para o ficheiro temporário
	fs = open("strings", O_RDONLY);
	for(code = 1; code <= codeT; code++){
			//Get ref e get size no ficheiro artigos
			fa = open("artigos", O_RDONLY);
			lseek(fa, (code-1)*size_artigos, SEEK_SET);
			read(fa, &ref, sizeof(int));
			read(fa, &size, sizeof(short));
			close(fa);

			/*
			getRef
			getSize
			*/
			//Get line no ficheiro strings
			lseek(fs, ref, SEEK_SET);
			char* line = malloc(size);
			read(fs, line, size);

			//Escreve no ficheiro temp
			w = lseek(fd, 0, SEEK_CUR);
			write(fd, line, size);

			//Atualiza ref no artigos
			updateRef(code, w, size);
			free(line);

	}
	close(fd);
	close(fa);
	
}

int renameTemp(){
	
	int pid;
	int status;
	if(!(pid = fork())){
		execlp("mv", "mv", "temp" , "strings", NULL);
		exit(1);
	}
	wait(&status);

	return WIFEXITED(status);
	
}

/*
int validaInputMA(char** args){
	

}*/

int main(int argc, char *argv[]){
	char* buff = malloc(150);
	int r ;

	/*
		if(argc == 2)
			if(!(strcmp(argv[1], "a"))
				fork/exec
					exec(sv, sv, a,NULL)
				wait
				return
		

	*/
		while( (r = readln(0, buff, 150)) ){
				
				//buff[r-1] = '\0';

				if(buff[0] == 'i')
				{
					char** args = malloc(sizeof(char**));
					parse(buff, args);
					float p = atof(args[2]);

					if(p > 0){
						int code = insertArtigo(args[1], p);

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
						short size = getSize(code);
						int ref = renameStr(code , args[2], size);
						updateRef( code, ref, (short)strlen(args[2]));
					}

					free(args);

					if( twenty() ){
						
						clearTrash();
						renameTemp();

						
					}
					
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
	
	
	free(buff);
	return 0;
}


