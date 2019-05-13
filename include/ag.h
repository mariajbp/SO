#ifndef __AG_H__
#define __AG_H__

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

/**
 * Função que dá append de um ficheiro tail num ficheiro head
 * @param head file, tail file
 * @returns quantidade total do ficheiro head no fim do append
 */
int append_file(char* head, char* tail);

/**
 * Função cria um ficheiro com o nome de um inteiro
 * @param o número do pid
 * @returns string com o número do pid
 */
char* creat_file(int pid);

/**
 * Função que agrega um ficheiro de formato vendas de forma sequencial, do inicio escolhido ao fim escolhido
 * @param filename, new_file, inicio da agregação, fim da agregação
 * @returns quantidade de bytes lidos
 */
int agregacao_simples(char* filename, char* new_file, int init, int fim);

/**
 * Função que agrega um ficheiro de formato vendas de forma sequencial, do inicio escolhido ao fim escolhido
 * @param filename, new_file, inicio da agregação, fim da agregação, num de vezes que um artigo pode lá aparecer
 */
void agregacao_final(char* filename, char* new_file, int init, int fim, int num);

/**
 * Função que cria concorrencia dos processos de agregação
 * @param filename, new_file, inicio da agregação
 */
void split_work(char* filename, char* new_file, int init);

#endif
