#include "../include/aux.h"


ssize_t readln(int fildes, void *buff, size_t n){ 
    char c ;
    size_t s = 0;
    char* temp = (char *)buff;

    while( s < n && read(fildes, &c, 1) == 1 ){      
        if(c == '\0')
        	return s;
        temp[s++] = c;
        if(c == '\n')
        	return s;
    }

    return s;
}


void terminar(int signum){
	pid_t p = getpid();
	char* pid = malloc(10);
	sprintf(pid, "%d", p);
	unlink(pid);
	kill(p, SIGQUIT);
}


int main(int argc, char const *argv[])
{
	int n_read = 0;

	pid_t pid = getpid();
	char* nome_pid = malloc(10);
	sprintf(nome_pid, "%d", pid);

	signal(SIGINT, terminar);

	mkfifo(nome_pid, 0644);
	char* line = malloc(50);
	char* out_line = malloc(50);

	while(1){
		n_read = readln(0, line, 50);
		char* args = malloc( n_read + (strlen(nome_pid)) );
		sprintf(args, "%s %s", nome_pid, line);

		int fd = open("pedidos", O_WRONLY);
		write(fd, args, strlen(args));
		close(fd);

		int fd_r = open(nome_pid, 0644);
		readln(fd_r, out_line, 50);
		close(fd_r);
		write(1, out_line, strlen(out_line));
		
	}
	return 0;
}