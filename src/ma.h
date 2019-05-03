#ifndef __MA_H__
#define __MA_H__

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>



/**
 * Função que escreve o nome de um artigo no ficheiro strings.txt
 * @param nome e tamanho do nome a escrever
 * @param referencia do artigo inserido
 */

int insertString(char* name, int size);

/**
 * Função que insere um artigo no ficheiro artigos.txt
 * @param nome e preço do artigo
 */
void insertArtigo(char* name, double price);

/**
 * Função que dado o código do artigo retorna o seu preço
 * @param código do artigo
 * @param preço do artigo
 */
double getPrice(int code);

/**
 * Função que dado o código do artigo e um novo preço, altera o seu preço atual
 * @param código e preço atual de um artigo
 * @param novo preço de um artigo
 */
void changePrice(int code, double newp);

/**
 * Função que dado o código do artigo e um novo nome, altera o seu nome atual
 * @param código e novo nome de um artigo
 */
int rename(int code, char* new_name);

/**
 * Função que dado o código do artigo e uma nova referencia, atualiza a referencia
 * @param código e referencia de um artigo
 */
void updateRef(int code, int ref);


#endif
