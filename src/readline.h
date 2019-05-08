#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>


/**
 * O QUE FAZ
 * @param O QUE RECEBE
 * @param O QUE RETORNA
 */

int readln(int fildes, char *buf, int buf_size, ssize_t nc);