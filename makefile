INC = include/
OBJ = src/

objects = $(OBJ)aux.o $(OBJ)ma $(OBJ)sv $(OBJ)cv 
CFLAGS = -g -Wall -O2 -Wno-unused-result
CC = gcc

.DEFAULT_GOAL := all

all: $(objects) 

sv : $(INC)aux.h $(INC)sv.h
cv : $(INC)aux.h $(INC)cv.h
ma : $(INC)ma.h  $(INC)aux.h 
aux.o : $(INC)aux.h 


.PHONY : clean
clean : 
	rm  $(objects)
