INC = ../include/
OBJ = ../src/


objects = $(OBJ)main.o $(OBJ)ma.o $(OBJ)sv.o $(OBJ)cv.o $(OBJ)ag.o
CFLAGS = -g -Wall 
CC = gcc


GV : $(objects)
	$(CC) $(CFLAGS) -o GV $(objects) 

main.o : $(INC)main.h $(INC)ma.h $(INC)sv.h $(INC)cv.h $(INC)ag.h
ma.o : $(INC)ma.h $(INC)sv.h $(INC)cv.h $(INC)ag.h
sv.o : $(INC)sv.h $(INC)ma.h $(INC)cv.h $(INC)ag.h
cv.o : $(INC)cv.h $(INC)ma.h $(INC)sv.h $(INC)ag.h
ag.o : $(INC)ag.h $(INC)ma.h $(INC)sv.h (INC)cv.h


.PHONY : clean
clean : 
	rm GV $(objects)