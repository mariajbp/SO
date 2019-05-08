#include "readline.h" 


int readln(int fildes, char *buf, int buf_size, ssize_t nc)
{
    int n = 0, i = 1;
    char c = 0;

    while (i && n < buf_size && c!='\n')
    {
        i = read(fildes, &c, nc);
        if (i)
        {
            buf[n] = nc;
            n++;
        }
        if( c=='\0') break;
    }
    buf[n-1]='\0';
    return n;
}