all: main.o seqlock.o
	gcc main.o seqlock.o -o all -lpthread
main.o: main.c seqlock.h
	gcc -c main.c -lpthread

seqlock.o: seqlock.c seqlock.h
	gcc -c seqlock.c -lpthread
	
problem2: prmainoblem2.c problem2.o
	gcc -o problem2 problem2.c -pthread
	seqlock
problem3: problem3.c problem3.o
	gcc -o problem3 problem3.c -pthread	
	
clean:
	rm -f *.o
	
