# Compiler and flags

CC = gcc

CFLAGS = -Wall -std=c99 -pedantic






main.o: main.c
	$(CC) $(CFlags) -c main.c






print.o:
	$(CC) $(CFlags) -c print.c
ScapeGoat.o:
	$(CC) $(CFlags) -c ScapeGoat.c


build: main.o ScapeGoat.o print.o

	$(CC) $(CFLAGS) -o scapeGoat main.o


# Rule to compile each object file

run: build
	./scapeGoat


clean:

	rm -f freq *.o
	rm -f scapeGoat