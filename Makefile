CC = gcc
CFLAGS = -Iinclude -Wall -g
LDFLAGS = -Llibs -llist

all: liblist.a main clean

main: main.o
	$(CC) -g main.o $(LDFLAGS) -o main

main.o: 
	$(CC) -c $(CFLAGS) src/main.c -o main.o

list.o: src/list.c include/list.h
	$(CC) -c $(CFLAGS) src/list.c -o list.o

liblist.a: list.o
	ar rcs libs/liblist.a list.o

clean:
	rm *.o