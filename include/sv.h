#ifndef __SV_H__
#define __SV_H__

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


/**Readline 
 * @param descritor do ficheiro
 * @param buffer para onde vai ler
 * @param numero de bytes a ler
 */
ssize_t readln(int fildes, void* buff, size_t n);

/**Função que faz parsing de uma linha de vendas
 * @param buffer
 * @param string
 * @return numero de bytes lidos
 */
int parse(char* buff, char** str);

/**
 * Função que dado o código do artigo retorna o seu preço
 * @param código do artigo
 * @returns preço do artigo
 */
float getPrice(int code);

/**
 * Função que procura um código no ficheiro stocks 
 * @param código de um artigo
 * @returns quantidade de um artigo em stock
 */
int stocksReadQ(int code);

/**
 * Função que atualiza o ficheiro stocks.
 * @param codigo de um produto
 * @param quantidade existente do artigo em stock
 * @returns quantidade do artigo em questão
 */
int stocksWrite(int code, int q);

/**
 * Função que calcula o montante de uma venda dado o code e a quantidade
 * @param codigo de um artigo 
 * @param quantidade existente do artigo em stock
 * @returns montante de uma venda
 */
float calculaMont(int code, int quant);

/**
 * Função que acrescenta uma venda ao ficheiro vendas.
 * @param uma venda (código, quantidade e montante)
 */
void vendasAppend(int code, int quant, float mont);

/**
 * Função que realiza uma venda/restock
 * @param codigo do artigo
 * @param quantidade existente do artigo em stock
 * @returns quantidade existente do artigo em stock atualizada
 */
int makeVenda(int code, int quant);

/**
 * Handler do Ctr-C para terminar o processo e fazer unlink do pipe pedidos
 * @param sinal
 */
void terminar(int signum);

/**
 * Função que valida o input do CV
 * @param argumentos passados na linha de comandos
 * @param numero de argumentos passados
 * @returns validação do input
 */
int validaInputCV(char** args, int i);


/**
 * Função que gera o ficheiro logs com o numero de bytes da ultima agregação colocado em apendice
 * @param tamanho do ficheiro novo para guardar
 * @returns inicio da nova agregação
 */
int logs(int size);

#endif
