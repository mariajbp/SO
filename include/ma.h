#ifndef __MA_H__
#define __MA_H__

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>
#include <time.h>


#define size_artigos 10

/**
 * Função que escreve o nome de um artigo no ficheiro strings.txt
 * @param nome a escrever no ficheiro
 * @param tamanho do nome a escrever no ficheiro
 * @returns referencia do artigo inserido
 */

int insertString(char* name, short size);

/**
 * Função que insere um artigo no ficheiro artigos.txt
 * @param nome do ficheiro a escrever
 * @param preço do artigo
 * @returns código do artigo
 */
int insertArtigo(char* name, float price);


/**
 * Função que dado o código do artigo e um novo preço, altera o seu preço atual
 * @param codigo do artigo
 * @param novo preço do artigo
 */
void changePrice(int code, float newp);

/**
 * Função que dado o código do artigo e um novo nome, altera o seu nome atual
 * @param codigo do artigo
 * @param novo nome do artigo
 * @returns referencia do artigo no ficheiro strings
 */
int renameStr(int code, char* new_name, short size);

/**
 * Função que dado o código do artigo e uma nova referencia, atualiza a referencia
 * @param código de um artigo
 * @param referencia de um artigo
 * @param tamanho do nome do artigo
 */
void updateRef(int code, int ref, short size);

/**
 * Função que devolve o tamanho do nome de um artigo
 * @param código de um artigo
 * @returns tamanho do nome do artigo
 */
short getSize(int code);

/**
 * Função que dado o código do artigo retorna o seu preço
 * @param código do artigo
 * @returns preço do artigo
 */
float getPrice(int code);

/**
 * Função que acrescenta um codigo de artigo ao ficheiro stocks
 */
void stockAppend();

#endif
