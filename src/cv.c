#include "../include/cv.h"

//Função que lê uma linha
ssize_t readln(int fildes, void* buff, size_t n){ 
    char c = ' ';
    size_t s = 0, r = 1;
    char* temp = (char *)buff;

    while( (s < n) && r && (c != '\n')){  

    	r = read(fildes, &c, 1);

        if(r && (c != '\n')){
        	temp[s] = c;
        	s++;
        }
    }
    temp[s] = 0;
    if(s == 0 && temp[s] == '\n')
    	return -1;

    return s;
}

//Handler para o CTR-C
void terminar(int signum){
	pid_t p = getpid();
	char* pid = malloc(10);
	sprintf(pid, "%d", p);
	unlink(pid);
	kill(p, SIGQUIT);
}

//«««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

int main(int argc, char const *argv[])
{
	int n_read = 0;
	int flag = 0;
	int fd_r = 0;


	pid_t pid = getpid();
	char* nome_pid = malloc(10);
	sprintf(nome_pid, "%d", pid);

	signal(SIGINT, terminar);
	

	mkfifo(nome_pid, 0644);
	char* line = malloc(50);


		while( (n_read = readln(0, line, 50)) ){

				
				char* args = malloc( n_read + (strlen(nome_pid)) );
				
				sprintf(args, "%s %s", nome_pid, line);
				
				int fd = open("pedidos", O_WRONLY);
					if(fd == -1)
					_exit(-1);
				write(fd, args, strlen(args));
				char* out_line = malloc(50);
				close(fd);

				//Se for o 1º pedido
				if(flag == 0){
					fd_r = open(nome_pid, O_RDONLY);
					flag++;
				}
				while( !strcmp(out_line, "") )
					readln(fd_r, out_line, 50);
				if( strcmp(out_line, "i")){
					write(1, out_line, strlen(out_line));
					write(1, "\n", 1);
				}
				free(out_line);
				free(args);		
		}
	

	close(fd_r);
	unlink(nome_pid);
	
	free(line);
	free(nome_pid);
	return 0;
}