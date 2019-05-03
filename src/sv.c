#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

/**Este programa deve controlar stocks, receber pedidos do cliente de 
vendas, e registar as vendas efectuadas. A quantidade em stock de 
cada artigo deverá ser mantida num único ficheiro stocks, para todos os 
artigos. Cada venda efectuada deverá ser registada, acrescentando uma 
entrada a um ficheiro vendas, contendo código, quantidade e montante 
total da venda.
O servidor de vendas deve ainda providenciar para correr o agregador a 
pedido, fazendo com que este receba o intervalo (para ser agregado) do 
ficheiro de vendas desde a última agregação, e fazendo com que o 
resultado da agregação seja escrito num ficheiro cujo nome reflecte o 
período em causa (e.g., 20190324T14). **/

/*

TO DO:
	*função para aceder ao ficheiro stocks e LER/ESCREVER 
	*função para aceder ao ficheiro vendas e LER/ESCREVER
	*função que recebe um código de artigo, vai ao ficheiro stocks e devolve  a quantidade
	*função que pede ao ma o preço de um artigo
	*função que recebe um código e uma quantidade e atualiza no ficheiro stocks
	*função que acrescenta uma venda no ficheiro vendas
	*função de parsing dos buffers lidos?
	(*funções para o agregador)

NOTAS:
	->Ficheiro vendas é quase como um logbook, vão se acrescentando 
	->Quando um artigo é adicionado no MA, é necessário incluir esse no ficheiro stocks?
	->Formato do stock: <código do artigo/index> <quantidade em stock>
	->Formato das vendas: <código do artigo/index> <quantidade vendida> <montante total>
	->Nome dos ficheiros: stocks.txt vendas.txt
	->O SV não envia nada para o stdout nem recebe nada do stdin, apenas dos outros módulos

*/



//Code size = sizeof(int) = 4 bytes
//Quantidade size = sizeof(int) = 4 bytes
// Montante = sizeof(float) = 4 bytes

/*
	Função que acrescenta um codigo de artigo ao ficheiro stocks,
	sempre que for acrescentado no ficheiro ARTIGOS (ou seja, pelo ma).
*/
void stockAppend(int code){
	int q = 0;
	int w = -1;
	int fd = open("stocks.txt", O_WRONLY | O_CREAT, 0600);

	if(fd == -1){
		perror("Unable to open file stocks");
		exit(1);
	}
	else{
		lseek(fd, 0, SEEK_END);
		w = write(fd, &code, sizeof(int));
		w += write(fd, &q, sizeof(int) );
	}
	close(fd);
}

/*
	Função que procura um código linha a linha no ficheiro 
 	stocks e escreve a quantidade que foi lida num buffer
*/
int stocksReadQ(int code){							 	
	int quant = 0;
	int r = -1;

	int fd = open("stocks.txt", O_RDONLY);

	if(fd == -1){
		perror("Unable to open file stocks");
		exit(1);
	}
	else{
		//Atualiza o apontador para o local do código + da quantidade
		lseek(fd, code*sizeof(int)*2 + sizeof(int), SEEK_SET);
		
		r = read(fd, &quant, sizeof(int));
			
		if(r == 0){
			perror("Artigo not found");
			exit(-1);
		}
	}
	close(fd);
	return quant;
}


/*
	Função que dado um código e uma quantidade 
	atualiza no ficheiro stocks.
*/
void stocksWrite(int code, int q){
	int quant = 0;
	int r = -1;
	int w = -1;

	int fd = open("stocks.txt", O_WRONLY);

	if(fd == -1){
		perror("Unable to open file stocks");
		exit(1);
	}
	else{
		//Atualiza o apontador para o local do código + local da quantidade
		lseek(fd, code*sizeof(int)*2 + sizeof(int), SEEK_SET);
		r = read(fd, &quant, sizeof(int));
			
		if(r == 0){
			perror("Artigo not found");
			exit(-1);
		}
		else{
			quant += q;
			w = write(fd, &quant, sizeof(int));
		}
	}
	close(fd);
}

/*
	Função que dado uma venda, 
	acrescenta-a no ficheiro vendas.
*/
void vendasAppend(int code, int quant, float mont){
	int w = -1;
	int fd = open("vendas.txt", O_WRONLY | O_CREAT, 0600);

	if(fd == -1){
		perror("Unable to open file strings");
		exit(1);
	}
	else{
		lseek(fd, 0, SEEK_END);
		w = write(fd, &code, sizeof(int));
		w += write(fd, &quant, sizeof(int) );
		w += write(fd, &mont, sizeof(float));
	}

	close(fd);
} 

//«««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
/*
	Função que imprime o ficheiro stocks 
	na totalidade no ecrã usando printf. 
	PARA TESTES!
*/
void printfStocks(){
	int code = 0;
	int q = 0;
	int r = 1;
	int w = 1;

	int fd = open("stocks.txt", O_RDONLY);


		while(r != 0){
			r = read(fd, &code, sizeof(int));
			w = write(1, &code, sizeof(int));
			//printf("Código do artigo: %d\n", code);

			r = read(fd, &q, sizeof(int));
			w = write(1, &q, sizeof(int));
			//printf("Quantidade em stock: %d\n", q);
		}

	 close(fd);

}

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


/*
	Função que consulta o ficheiro
	stocks e imprime as informações de um
	dado código de artigo, usando printf.
	PARA TESTES!
*/
void printfSingleStocks(int code){
	int quant = -1;
	int q = -1;
	int r = -1;

	int fd = open("stocks.txt", O_RDONLY);

		lseek(fd, code*sizeof(int)*2, SEEK_SET);
		read(fd, &r, sizeof(int));
		read(fd, &quant, sizeof(int));


	 close(fd);
	 printf("Code: %d\nQuantidade: %d\n", r, quant);
}

/*
	Função que imprime o ficheiro vendas 
	na totalidade no ecrã usando printf. 
	PARA TESTES!
*/
void printfVendas(){
	int code = 0;
	int q = 0;
	float m = 0.0;
	int r = 1;

	int fd = open("vendas.txt", O_RDONLY);

		while(r != 0){
			r = read(fd, &code, sizeof(int));
			printf("Código do artigo: %d\n", code);

			r = read(fd, &q, sizeof(int));
			printf("Quantidade vendida: %d\n", q);

			r = read(fd, &m, sizeof(float));
			printf("Montante: %f\n", m); 
		}

	 close(fd);
}
//Imprime 1 vez a mais não sei porquê

//«««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

int main(int argc, char const *argv[]){
	int code = 0;

	stockAppend(0);
	stockAppend(1);
	stockAppend(2);
	stockAppend(3);
	stockAppend(4);
	
	stocksWrite(3, 200);
	//printfStocks();

	//printfSingleStocks(3);
	//int q = stocksReadQ(3);
	//printf("%d\n", q);
	
/*
	vendasAppend(0, 12, 5.0);
	printfVendas();
*/
	return 0;
}
