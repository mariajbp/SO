#ifndef __CV_H__
#define __CV_H__

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


/**
 * Handler do Ctr-C para terminar o processo e fazer unlink do pipe pedidos
 * @param sinal
 */
void terminar(int signum);

#endif
