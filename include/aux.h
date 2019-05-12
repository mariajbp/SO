#ifndef __AUX_H__
#define __AUX_H__

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


/**
 * Função que lê linha a linha de um descritor fildes
 * @param 
 * @param 
 * @param
 * @returns
 */
ssize_t readln(int fildes, void *buff, size_t n);


/**
 * Função que faz parsing de uma linha
 * @param 
 * @param 
 * @returns
 */
int parse(char* buff, char** str);


#endif
