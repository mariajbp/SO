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
		int i , c = 0;

		for(i = 0; i < 5000; i++){
			f++;
			fprintf(fd, "i bola %f\n", f);
		}
		for(i = 0; i < 20; i++){
			c+= 200;
			fprintf(fd, "n %d quadrado\n", c);
		}


		fclose(fd);
		printf("DONE");
	}
	else{
		FILE* fd = fopen("testesCV.txt", "w");
		int f = 50;

		for(int i = 1; i < 5000; i++){
			f++;
			fprintf(fd, "%d %d\n", i, -f);
		}

		fclose(fd);
		printf("DONE");
	}
}