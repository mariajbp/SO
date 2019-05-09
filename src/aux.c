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

//Função que faz parsing de uma linha
int parse(char* buff, char** str){

	char* tok;
	tok = strtok(buff, " ");
	int i;
	for( i = 0; tok; i++){
		str[i] = strdup(tok);
		tok = strtok(NULL, " ");
	}
	return i;
}

/*

//main de teste

int main(){

	int fd = open("testes.txt", O_RDONLY);
	char* buff = malloc(100);
	int r = 0;
	while( (r = readln(fd, buff, 100)) ){
		buff[r+1] = '\0';
		printf("%s\n", buff);
	}
	close(fd);
	return 0;
}
*/