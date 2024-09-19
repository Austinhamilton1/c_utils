CC = gcc
CFLAGS = -Iinclude -Wall -g
LDFLAGS = -Llibs -lutils

all: libutils.a main clean

main: main.o
	$(CC) -g main.o $(LDFLAGS) -o main

main.o: 
	$(CC) -c $(CFLAGS) src/main.c -o main.o

list.o: src/list.c include/list.h
	$(CC) -c $(CFLAGS) src/list.c -o list.o

libutils.a: list.o
	ar rcs libs/libutils.a list.o

clean:
	rm *.o