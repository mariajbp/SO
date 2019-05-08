#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>


/**
 * Lê uma linha de um descritor
 * @param fildes e um buffer
 * @param o numero de caracteres lidos
 */

int readln(int fildes, char *buf);