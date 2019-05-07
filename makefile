INC = ../include/
OBJ = ../src/

objects = $(OBJ)ma.o $(OBJ)sv.o
CFLAGS = -g -Wall -O2
CC = gcc


all: $(objects) 

ma : 
	$(CC) $(CFLAGS) -o ma ma.c
sv : 
	$(CC) $(CFLAGS) -o ma ma.c


.PHONY : clean
clean : 
	rm  $(objects)
