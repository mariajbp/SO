#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main(){

	FILE* fd = fopen("testes.txt", "w");
	float f = 0.0;

	for(int i = 0; i < 5000; i++){
		f++;
		fprintf(fd, "i bola %f\n", f);
	}

	fclose(fd);
	printf("DONE");
}