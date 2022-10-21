all: main.o factorial.o readline.o
	gcc main.o factorial.o readline.o -o main

main.o: main.c factorial.h readline.h
	gcc -c main.c

factorial.o: factorial.c factorial.h
	gcc -c factorial.c

readline.o: readline.c readline.h
	gcc -c readline.c

problem4: problem4.o
	gcc -o problem4 problem4.o

problem4.o: problem4.c
	gcc -c problem4.c
