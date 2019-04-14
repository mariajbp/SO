INC = ../include/
OBJ = ../src/


objects = $(OBJ)main.o
CFLAGS = -g -Wall 
CC = gcc


GV : $(objects)
	$(CC) $(CFLAGS) -o GV $(objects) 

main.o : $(INC)main.h


.PHONY : clean
clean : 
	rm GV $(objects)