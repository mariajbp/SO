#ifndef __AG_H__
#define __AG_H__

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

/**
 * Função que dá append de um ficheiro tail num ficheiro head
 * @param head file 
 * @param tail file
 * @returns quantidade total do ficheiro head no fim do append
 */
int append_file(const char* head,const char* tail);

/**
 * Função cria um ficheiro com o nome de um inteiro
 * @param o número do pid
 * @returns string com o número do pid
 */
char* creat_file(int pid);

/**
 * Função que agrega um ficheiro de formato vendas de forma sequencial, do inicio escolhido ao fim escolhido
 * @param nome do ficheiro a agregar
 * @param nome do ficheiro final agregado 
 * @param inicio da agregação
 * @param fim da agregação
 * @returns numero de bytes lidos
 */
int agregacao_simples(const char* filename,const char* new_file, int init, int fim);

/**
 * Função que agrega um ficheiro de formato vendas de forma sequencial, do inicio escolhido ao fim escolhido
 * @param nome do ficheiro a agregar
 * @param nome do ficheiro final agregado 
 * @param inicio da agregação
 * @param fim da agregação
 * @returns numero de vezes que a venda aparece no ficheiro
 */
void agregacao_final(const char* filename,const char* new_file, int init, int fim, int num);

/**
 * Função que cria concorrencia dos processos de agregação
 * @param nome do ficheiro a agregar
 * @param nome do ficheiro final agregado 
 * @param inicio da agregação
 */
void split_work(const char* filename,const char* new_file, int init);

#endif
