INC = include/
OBJ = src/

objects =  $(OBJ)ma $(OBJ)sv $(OBJ)ag $(OBJ)cv
files = $(OBJ)artigos $(OBJ)stocks $(OBJ)strings $(OBJ)vendas
CFLAGS = -g -Wall -O2 -Wno-unused-result
CC = gcc

.DEFAULT_GOAL := all

all: $(objects) 

ag : $(INC)ag.h
sv : $(INC)sv.h
cv : $(INC)cv.h
ma : $(INC)ma.h  



.PHONY : clean
clean : 
	rm  $(objects) $(files)
