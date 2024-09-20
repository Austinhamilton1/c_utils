CC = gcc
CFLAGS = -Iinclude -Wall -g
LDFLAGS = -Llibs -llist -lstack

all: liblist.a libstack.a main clean

main: main.o
	$(CC) -g main.o $(LDFLAGS) -o main

main.o: 
	$(CC) -c $(CFLAGS) src/main.c -o main.o

list.o: src/list.c include/list.h
	$(CC) -c $(CFLAGS) src/list.c -o list.o

stack.o: src/stack.c include/stack.h
	$(CC) -c $(CFLAGS) src/stack.c -o stack.o

liblist.a: list.o
	ar rcs libs/liblist.a list.o

libstack.a: stack.o
	ar rcs libs/libstack.a stack.o

clean:
	rm *.o
