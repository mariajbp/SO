#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main(int argc, char const *argv[]){

	if(argc == 1){
		FILE* fd = fopen("testesMA.txt", "w");
		float f = 0.0;

		for(int i = 0; i < 1000000; i++){
			f++;
			fprintf(fd, "i bola %f\n", f);
		}

		fclose(fd);
		printf("DONE");
	}
	else{
		FILE* fd = fopen("testesCV.txt", "w");
		int f = 50;

		for(int i = 1; i < 1000000; i++){
			f++;
			fprintf(fd, "%d %d\n", i, -f);
		}

		fclose(fd);
		printf("DONE");
	}
}