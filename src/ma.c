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


void insertArtigo(char[LENGTH] name, double price)
{
	endln = "\n"; 
	space = " "
	//abrir ficheiro, se não existir é criado
	int fp = open("ARTIGOS.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	//escrever em argv[2] o nome e argv[3] o preço, gerar um código consoante o numero da linha do ficheiro em que está e escreve-o 
	write(fp,name,strlen(name));
	write(fp,space,strlen(space));
	write(fp,price,sizeof(double));
	write(fp,endln,strlen(endln));

}

/**

// funcao que apaga um artigo, corre o ficheiro STRINGS = mesmo nome, mesmo preco -> delete
void deleteArtigo(char[LENGTH] name, double price)
{
	int fp = open("STRINGS.txt", O_TRUNC | O_RDWR, 0777);
	while(!EOF)
	{
		

	}

 //flush
}
**/

int main(int argc, char *argv[]) //main do MA
{
	/**if(argv[1] == i)
	{
		//( <nome> <preco> ) -> insere
	}
	if(argv[1] == n)
	{
		// n ( <codigo> <new_nome> ) -> altera nome
	}
	if(argv[1] == p)
	{
		// p ( <codigo> <new_preco> ) -> altera preco
	}

	*/
	insertArtigo(name,price);

	return 0;
}

