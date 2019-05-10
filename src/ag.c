#include <time.h>

/** O programa agregador deve processar entradas no formato do ficheiro 
de vendas, recebidas no stdin, até end-of-file. Deve produzir para o 
stdout entradas contendo o código do artigo, a quantidade total e o 
montante total (apenas para os artigos com vendas efectuadas)**/

/** Formato do ficheiro vendas:<código do artigo> <quantidade vendida> <montante total> **/

//ssize_t readln(int fildes, void* buf, size_t n)

//1 linha de venda = 15 bytes int+\0+int+\0+float+\0

//vai receber o nome do ficheiro agregado mais recentemente para o abrir e voltar a agregar
void agregar(char* filename)
{
  int size, s, c, cod;
  int quantidade, mont, q, m;
  pid_t pid;
  int status;
  int fd = open(filename, O_RDWR, 0644);

	if(fd == -1)
		_exit(-1);
	else
	{	
    	
    for(int i=0;i<s-(sizeof(int));i++)
  	{
 			read(fd, &cod, sizeof(int));
      read(fd, &quantidade, sizeof(int));
   		read(fd, &mont, sizeof(float));
   		for(int j=0; j<s; j++)
			{
    		lseek(fd, (sizeof(int)+sizeof(float)), SEEK_CUR);
    		read(fd, &c, sizeof(int));
   			if(c == cod)
   			{
   				c = 0;
    			lseek(fd, -(sizeof(int)), SEEK_CUR);
    			write(fd, &c, sizeof(int));
    			read(fd, &q, sizeof(int));
    			read(fd, &m, sizeof(float));
  				quantidade += q;
 					mont += m;
    		}
    	}
    }
  }	
	close(fd);		
}
	

void wrToFile(char* oldfile)
{
  char date_time[30];   //Collect system date and time in this character array
  char filename[40];
  sprintf(filename, "%s", date_time);
  int fdw = open(filename, O_CREAT | O_WRONLY , 0644);
  int fdr = open(oldfile, O_RDONLY, 0644)

}







int main(int argc, char *argv[])
{

}
