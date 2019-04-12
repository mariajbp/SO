#include <unistd.h>  
#include <fcntl.h>
#include <stdlib.h>
#include "ma.h"

#define LENGTH 1024


struct artigo
{
	char name[LENGTH];
	char description[LENGTH];
	double price;
	size_t code;
}; 

Artigo create_Artigo(char name, char descricao, double price, size_t code) //abrir ficheiro e escrever lá
{
	Artigo a = (Artigo)malloc(sizeof(struct artigo));

	a->name = NULL;
	a->description = NULL;
	a->price = 0;
	a->code = 0;
}

void destroy_Artigo(Artigo a)
{
	free(a);
}

/**** Gets e Sets para alterar os dados *****/

char nameArtigo(Artigo a)
{
	return a->name;
}

void changeName(Artigo a, char new_name)
{
	a->name = new_name;
}

char descriptionArtigo(Artigo a)
{
	return a->description;
}

void changeDescription(Artigo a, char new_description)
{
	a->description = new_description;
}

double priceArtigo(Artigo a)
{
	return a->price;
}

void changePrice(Artigo a, double new_price)
{
	a->price = new_price;
}
	
int main()
{
	return 0;
}

