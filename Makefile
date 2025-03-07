# Compiler and flags

CC = gcc


build: main.o
	$(CC) -Wall -std=c99 -pedantic -o  scapeGoat main.o ScapeGoat.o -lm

main.o: main.c ScapeGoat.c ScapeGoat.h
	$(CC) -Wall -std=c99 -pedantic  -c main.c ScapeGoat.c


run: build
	./scapeGoat

test: build
	python3 testC.py ./scapeGoat tests


clean:

	rm -f freq *.o
	rm -f scapeGoat
	clear