#include "../include/aux.h"
#include "../include/sv.h"


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

	for( i = 0; tok ; i++){
		str[i] = strdup(tok);
		tok = strtok(NULL, " ");
	}
	return i;
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
		lseek(fd, (code-1)*(sizeof(int)+sizeof(short)+sizeof(float)), SEEK_SET);
		lseek(fd, 6, SEEK_CUR);
		read(fd, &price, sizeof(float));
	}
	close(fd);
	return price;
}

//--------------------------------------------------------------

/*
	Função que procura um código no ficheiro 
 	stocks e escreve a quantidade que foi lida num buffer
*/
int stocksReadQ(int code){							 	
	int quant = -1;
	

	int fd = open("stocks", O_RDONLY);

	if(fd == -1)
		_exit(-1);
	else{
		//Atualiza o apontador para o local do código + da quantidade
		lseek(fd, (code-1)*sizeof(int), SEEK_SET);
		
		if( (read(fd, &quant, sizeof(int))) == 0)
			_exit(-1);
		
	}
	close(fd);
	return quant;
}


/*
	Função que dado um código e uma quantidade 
	atualiza no ficheiro stocks.
*/
int stocksWrite(int code, int q){
	int quant = -1;
	int r = -1;

	int fd = open("stocks", O_RDWR);

	if(fd == -1)
		_exit(-1);
	else{
		
		lseek(fd, (code-1)*sizeof(int), SEEK_SET);

		if(q == 0){
			write(fd, &q, sizeof(int));
			close(fd);
			return q;
		}
		else{
			r = read(fd, &quant, sizeof(int));
				
			if(r > 0){
				quant += q;
				lseek(fd, -sizeof(int),SEEK_CUR);
				write(fd, &quant, sizeof(int));
			}
			else{
				_exit(-1);
			}
		}
	}
	close(fd);
	return quant;
}
/*
 	Função que calcula o montante de uma venda dado o code e a quantidade
*/
float calculaMont(int code, int quant){
	float price = -1.0;

	price = getPrice(code);
	printf("price: %f\n", price);
	price*=quant;
	
	return price;
}


/*
	Função que dado uma venda, 
	acrescenta-a no ficheiro vendas.
*/
void vendasAppend(int code, int quant, float mont){

	int w = -1;
	int fd = open("vendas", O_WRONLY | O_CREAT, 0664);

	if(fd == -1)
		_exit(-1);
	else{
		lseek(fd, 0, SEEK_END);
		w = write(fd, &code, sizeof(int));
		w += write(fd, &quant, sizeof(int) );
		w += write(fd, &mont, sizeof(float));
	}

	close(fd);
} 



/*
	Função que realiza uma venda
*/
int makeVenda(int code, int quant){
	
	int ns;
	float m;

	if( (-quant) <= stocksReadQ(code)){
		m = calculaMont(code,(-quant));
		printf("%f\n", m);
		vendasAppend(code, -quant, m);
		ns = stocksWrite(code, quant);
	}
	else{
		int q = stocksReadQ(code);
		m = calculaMont(code, -q);
		vendasAppend(code, -q, m);
		ns = stocksWrite(code, 0);

	}
	return ns;
}

/*
	Handler do Ctr-C para terminar o processo e fazer unlink do pipe pedidos
*/
void terminar(int signum){
	unlink("pedidos");
	pid_t p = getpid();
	kill(p, SIGQUIT);
}




/*
	Função que valida o input 
*/
int validaInputCV(char** args, int i){

	int r = 0;
	if(i <= 1 || i > 3)
		return r;
	if(i == 2){
		if ( atoi(args[0]) && atoi(args[1]) )
			r = 1;
	}
	if(i == 3){
		if( atoi(args[0]) && atoi(args[1]) && atoi(args[2]))
			r = 1;
	}
	return r;
}

void printVenda(){

	int fd = open("vendas", O_RDONLY);
	int c, q;
	float m;
	lseek(fd, -(sizeof(int)*2 + sizeof(float)), SEEK_END);
	read(fd, &c, sizeof(int));
	read(fd, &q, sizeof(int));
	read(fd, &m, sizeof(float));

	close(fd);
	char buff[50];
	sprintf(buff, "%d %d %f", c, q, m);
	printf("%s\n", buff);
	

}
//«««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

int main(int argc, char const *argv[]){
	char *c = malloc(100);
	int r, i;

	signal(SIGINT, terminar);

	mkfifo("pedidos", 0600);		//pipes para os artigos

	while(1){
		int fd = open("pedidos", O_RDONLY);

			
			while( (r = readln(fd, c, 100)) ){
				
				char** args = malloc(sizeof(char**));
				i = parse(c,args);

				if( validaInputCV(args, i)){
					
					if(i == 2){	

						char* pid = args[0];
						int code = atoi(args[1]);
						
						if(code > 0){
							float p = getPrice(code);
							int q = stocksReadQ(code);

							char *r = malloc(50);
							int size = sprintf(r, "%d %f\n", q, p);
							int resp = open(pid, O_WRONLY);

							if(resp < 0)
								_exit(-1);

								write(resp, r, size);
								close(resp);
							free(r);
						}
				 	}
				 	if(i == 3){
				 			
				 			int ns = 0;
					 		char* pid = args[0];
							int code = atoi(args[1]);
							int quant = atoi(args[2]);

							if(code > 0){
					 			if(quant >= 0){
					 				ns = stocksWrite(code, quant);
					 			}
					 			else{
					 			 	ns = makeVenda(code, quant);
					 			 	printf("%d %d\n", code, quant);
					 			 	printVenda();
					 			}

						 		char *r = malloc(50);
						 		int size = sprintf(r, "%d\n", ns);
								
						 		int resp = open(pid, O_WRONLY);
						 		
						 		if(resp < 0)
									_exit(-1);

								write(resp, r, size);

								close(resp);
								free(r);
							}
				 	}
				}
				else{
					char* pid = args[0];
					int resp = open(pid, O_WRONLY);
						 		
						 		if(resp < 0)
									_exit(-1);

								write(resp, "i", 1);

								close(resp);
				}
				free(args);

			}
		close(fd);	
	}
	free(c);		

	return 0;
}
