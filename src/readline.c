#include "readline.h" 


int readln(int fildes, char *buf)
{
    int n = 0, r = 1, i;
    int c = 0;
    char* buff[100]
    int buf_size = 99;

    r = read(fildes, &c, buff_size);

    for(i = 0; i <= r; i++)
    {
        if(buff[i] == '\n')
        {
            buff[i] = "\0";
            break;
        }
        c++;
    }
    return c;
}