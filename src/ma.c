#include <unistd.h>  
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "ma.h"

#define LENGTH 1024 //


struct artigo
{
	char name[LENGTH];
	char description[LENGTH];
	double price;
	size_t code; //
};

Artigo create_Artigo(char n[LENGTH], char d[LENGTH], double p, size_t c) //abrir ficheiro e escrever lá
{
	Artigo a = malloc(sizeof(struct artigo));

	memcpy(a->name,n,LENGTH);
	memcpy(a->description,d,LENGTH);
	a->price = p;
	a->code = c;

	return a;
}

void destroy_Artigo(Artigo a)
{
	free(a);
}

/**** Gets e Sets para alterar os dados *****/

char* nameArtigo(Artigo a)
{
	return a->name;
}

void changeName(Artigo a, char new_name[LENGTH])
{
	memcpy(a->name,new_name,LENGTH);
}

char* descriptionArtigo(Artigo a)
{
	return a->description;
}

void changeDescription(Artigo a, char new_description[LENGTH])
{
	memcpy(a->description,new_description,LENGTH);
}

double priceArtigo(Artigo a)
{
	return a->price;
}

void changePrice(Artigo a, double new_price)
{
	a->price = new_price;
}


// funcao inserçao (<nome> <preco>) -> 

// funcao que apague, corre o ficheiro STRINGS = mesmo nome, mesmo preco -> delete


int main()
{

	// i ( <nome> <preco> ) -> insere
	// n ( <codigo> <new_nome> ) -> altera nome
	// p ( <codigo> <new_preco> ) -> altera preco
	
	return 0;
}

