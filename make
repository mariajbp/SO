INC = ../include/
OBJ = ../src/


objects = 
CFLAGS = -g -Wall 
CC = gcc


SGV : $(objects)
	$(CC) $(CFLAGS) -o SGV $(objects) 



.PHONY : clean
clean : 
	rm GV $(objects)