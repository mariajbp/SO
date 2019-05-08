#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include "sv.h"
#include "ma.h"

/*
NOTAS:
	->Formato do stock: <quantidade em stock>
	->Formato das vendas: <código do artigo/index> <quantidade vendida> <montante total>
	->Nome dos ficheiros: stocks vendas
	->O SV não envia nada para o stdout nem recebe nada do stdin, apenas dos outros módulos
*/



//Code size = sizeof(int) = 4 bytes
//Quantidade size = sizeof(int) = 4 bytes
// Montante = sizeof(float) = 4 bytes


/*
	Função que procura um código no ficheiro 
 	stocks e escreve a quantidade que foi lida num buffer
*/
int stocksReadQ(int code){							 	
	int quant = 0;
	int r = -1;

	int fd = open("stocks", O_RDONLY);

	if(fd == -1)
		_exit(-1);
	else{
		//Atualiza o apontador para o local do código + da quantidade
		lseek(fd, (code-1)*sizeof(int), SEEK_SET);
		
		r = read(fd, &quant, sizeof(int));
			
		if(r == 0)
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
	int quant = 0;
	int r = -1;
	int w = -1;

	int fd = open("stocks", O_WRONLY);

	if(fd == -1)
		_exit(-1);
	else{
		
		lseek(fd, (code-1)*sizeof(int), SEEK_SET);
		r = read(fd, &quant, sizeof(int));
			
		if(r == 0)
			_exit(-1);
		else{
			quant += q;
			lseek(fd, -sizeof(int),SEEK_CUR);
			w = write(fd, &quant, sizeof(int));
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
	int fd = open("artigos", O_RDONLY);

	if(fd == -1)
			_exit(-1);
	else{
		lseek(fd, (code-1)*(sizeof(int)+sizeof(short)) , SEEK_SET);
		read(fd, &price, sizeof(float));
		price*=quant;
	}
	close(fd);
	return price;
}


/*
	Função que dado uma venda, 
	acrescenta-a no ficheiro vendas.
*/
void vendasAppend(int code, int quant, float mont){

	int w = -1;
	int fd = open("vendas", O_WRONLY | O_CREAT, 0600);

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


// Função que recebe um codigo, vai ao ficheiros de artigos e retorna o preço desse artigo
float getPrice(int code)
{
	float price;
	int fd = open("artigos.txt", O_RDONLY);

	if(fd == -1)
		_exit(-1);
	else
	{
		lseek(fd, (code-1)*10, SEEK_SET);
		lseek(fd, 4, SEEK_CUR);
		read(fd, &price, sizeof(float));
		close(fd);
	}

	return price;
}


/*
	Função que realiza uma venda/restock
*/
int makeVenda(int code, int quant){
	
	int ns;
	float m;

	if(quant <= stocksReadQ(code)){
		m = calculaMont(code, quant);
		vendasAppend(code, quant, m);
		ns = stocksWrite(code, -m);
	}
	else{
		int q = stocksReadQ(code);
		m = calculaMont(code, q);
		vendasAppend(code, q, m);
		ns = stocksWrite(code, -m);
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


//«««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

int main(int argc, char const *argv[]){
	char** args = malloc(sizeof(char*));
	char *c = malloc(100);
	int r, i;

	signal(SIGINT, terminar);
	int a = mkfifo("pedidos", 0600);		//pipes para os artigos

	if(a == -1)
		_exit(-1);
	else{

		while(1){
			int fd = open("pedidos", O_RDONLY);
			
			while( (r = read(fd, c, 99 )) ){

				c[r+1] = "\0";
				i = parse(c,args);

				if(i == 2){	
					char* pid = args[0];
					int code = atoi(args[1]);

					float p = getPrice(code);
					int q = stocksReadQ(code);
					int resp = open(pid, O_WRONLY);
						if(resp == -1)
							_exit(-1);
						else{
							write(resp, &p, sizeof(float));
							write(resp, &q, sizeof(int));
							close(resp);
						}
			 	}
			 	if(i == 3){
				 		char* pid = args[0];
						int code = atoi(args[1]);
						int quant = atoi(args[2]);

			 			if(quant > 0){
			 				stocksWrite(code, quant);
			 			}
			 			else{
			 				makeVenda(code, quant);
							int resp = open(pid, O_WRONLY);

								if(resp == -1)
									_exit(-1);
								else{
									write(resp, &ns, sizeof(int));
									close(resp);
								}
			 			}
			 	}
			}
			close(fd);		
		}
	}
	return 0;
}
