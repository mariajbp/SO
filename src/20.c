#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

//calculo dos 20%
int twenty(short s, int ns)
{
	int res;
	if((ns*0.2) >= s)
		res = 0;
		
	else
		res = 1;
	return res;
}

//recebe um nome e adiciona a um novo ficheiro e retorna a nova ref desse nome
int addToNewFile(char* name)
{
	int fdn = open("NOME",O_WRONLY | O_CREAT,0664);  //dar um nome, quando acaba a escrita eliminar o antigo e passar-lhe esse nome do antigo
	int offset = lseek(fdn, 0, SEEK_CUR);
	write(fdn, name, strlen(name));	
	close(fdn);
	return offset;
}

//abre o artigos e o string e vai ver quais os que vão ser escritos no novo ficheiro
int clearTrash(int cod, char* name)
{
	int ref;
	int fda = open("artigos", O_RDONLY,0664);
	int fds = open("strings", O_RDONLY,0664);
	int asize = lseek(fda, 0, SEEK_END);
	lseek(fda, 0, SEEK_SET);
	int ssize = lseek(fds, 0, SEEK_END);
	int offset = lseek(fds, 0, SEEK_SET);

	for(int i = 0; i < asize; i++)
	{
		read(fda, &ref, sizeof(int)); 
		for(int j = 0; j < ssize; j++)
		{
			if(ref ==  offset)
				addToNewFile(name);

			else
			{
				lseek(fds, strlen(name), SEEK_CUR);
			}
		}

	}

	close(fda);
	close(fds);
}


void cleanSTR(char* new_name, int cod)
{
	int t, lixo;
	short scod = getSize(cod); //tamanho do nome
	int fds = open("strings", O_RDWR); //abre strings
	int fsize = lseek(fds, 0, SEEK_END); //lê tam do ficheiro strings
	lseek(fds, 0, SEEK_SET); //volta ao inicio do fich

	read(fds, &lixo, sizeof(int)); //lê o primeiro inteiro aka contador do lixo, na main tem que se inicializar a 0 ??
	renameStr(cod, new_name);
	lixo += scod;
	t = twenty(lixo,fsize); //calcula de passa os 20%
	if(t == 0) 
	{
		clearTrash(cod, new_name); // chama a cleartrash que limpa o lixo
		int offset = addToNewFile(new_name);
		updateRef(cod, offset ,strlen(new_name));
	}
}
