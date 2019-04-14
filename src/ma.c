#include "ma.h" 


struct artigo
{
	char name[LENGTH];
	double price;
	size_t code[7]; 
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

double priceArtigo(Artigo a)
{
	return a->price;
}

void changePrice(Artigo a, double new_price)
{
	a->price = new_price;
}


void insertArtigo()
{
	//abrir ficheiro, se não existir é criado
	int fp = open("ARTIGOS.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	//escrever em argv[1] o nome e argv[2] o preço, gerar um código consoante o numero da linha do ficheiro em que está

}

// funcao que apaga um artigo, corre o ficheiro STRINGS = mesmo nome, mesmo preco -> delete
void deleteArtigo(char[LENGTH] name, double price)
{
	int fp = open("STRINGS.txt", O_TRUNC | O_RDWR, 0777);
	while(!EOF)
	{
		

	}

 //flush
}

int main()
{

	// i ( <nome> <preco> ) -> insere
	// n ( <codigo> <new_nome> ) -> altera nome
	// p ( <codigo> <new_preco> ) -> altera preco
	
	return 0;
}

