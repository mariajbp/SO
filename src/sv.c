#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


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
	Função que acrescenta um codigo de artigo ao ficheiro stocks,
	sempre que for acrescentado no ficheiro ARTIGOS (ou seja, pelo ma).
*/
void stockAppend(){
	int q = 0;
	int w = -1;
	int fd = open("stocks", O_WRONLY | O_CREAT, 0600);

	if(fd == -1){
		perror("Unable to open file stocks");
		_exit(-1);
	}
	else{
		lseek(fd, 0, SEEK_END);
		w += write(fd, &q, sizeof(int) );
	}
	close(fd);
}

/*
	Função que procura um código no ficheiro 
 	stocks e escreve a quantidade que foi lida num buffer
*/
int stocksReadQ(int code){							 	
	int quant = 0;
	int r = -1;

	int fd = open("stocks", O_RDONLY);

	if(fd == -1){
		perror("Unable to open file stocks");
		_exit(-1);
	}
	else{
		//Atualiza o apontador para o local do código + da quantidade
		lseek(fd, (code-1)*sizeof(int), SEEK_SET);
		
		r = read(fd, &quant, sizeof(int));
			
		if(r == 0){
			perror("Artigo not found");
			_exit(-1);
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

	int fd = open("stocks", O_WRONLY);

	if(fd == -1){
		perror("Unable to open file stocks");
		_exit(-1);
	}
	else{
		//Atualiza o apontador para o local do código + local da quantidade
		lseek(fd, (code-1)*sizeof(int), SEEK_SET);
		r = read(fd, &quant, sizeof(int));
			
		if(r == 0){
			perror("Artigo not found");
			_exit(-1);
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
	int fd = open("vendas", O_WRONLY | O_CREAT, 0600);

	if(fd == -1){
		perror("Unable to open file strings");
		_exit(-1);
	}
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
	{
		perror("Unable to open file");
		_exit(-1);
	}
	else
	{
		lseek(fd, (code-1)*10, SEEK_SET);
		lseek(fd, 4, SEEK_CUR);
		read(fd, &price, sizeof(float));
		close(fd);
	}

	return price;
}

//«««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
/*
	Função que imprime o ficheiro stocks 
	na totalidade no ecrã usando printf. 
	PARA TESTES!

void printfStocks(){
	int q = 0;
	int w = 1;

	int fd = open("stocks", O_RDONLY);


		while(r = (read(fd, &q, sizeof(int)) ) ){
			w = write(1, &q, r);
			//printf("Quantidade em stock: %d\n", q);
		}

	 close(fd);

}
*/

/*
	Função que consulta o ficheiro
	stocks e imprime as informações de um
	dado código de artigo, usando printf.
	PARA TESTES!
*/
void printfSingleStocks(int code){
	int quant = -1;
	int q = -1;


	int fd = open("stocks", O_RDONLY);

		lseek(fd, code*sizeof(int), SEEK_SET);
		read(fd, &quant, sizeof(int));


	 close(fd);
	 printf("Quantidade: %d\n", quant);
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

	int fd = open("vendas", O_RDONLY);

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
	int a = mkfifo("art", 0600);		//pipes para os artigos

	if(a == -1){
		perror("Pipe art");
		_exit(-1);
	}
	else{
		int fd = open("art", O_RDONLY);
		char c;
		while(1){
			read(fd, &c, 1);
			if(c == "1")
				stockAppend();
		}
		close(fd);
	}
	return 0;
}
