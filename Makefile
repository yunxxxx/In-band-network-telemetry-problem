OBJS=c_program.o
DEBUG=-g
CC=gcc
CFLAGS=-Wall -c $(DEBUG)
LFLAGS=-Wall $(DEBUG)
EXE=c_program

&(EXE): $(OBJS)
	$(CC) $(OBJS) -o $(EXE)

c_program.o: c_program.c
		 $(CC) c_program.c

clean:
	rm *~ *.o $(EXE) -v