all: main.o
	gcc -o main main.o

main.o: main.c
	gcc -c main.c

reader: reader.o
	gcc -o reader reader.o
reader.o: reader.c
	gcc -c reader.c

writer: writer.o
	gcc -o writer writer.o

writer.o: writer.c
	gcc -c writer.c

writer1: writer1.o writer1.c
	gcc writer1.c -o writer1 -lpthread

writer2: writer2.o writer2.c
	gcc writer2.c -o writer2 -lpthread
	
pipeline: pipeline.o pipeline.c
	gcc pipeline.c	-o pipeline
	
pthread: pthread.o pthread.c
	gcc -o pthread pthread.c -lpthread
	
multithread: multithread.o multithread.c
	gcc -o multithread multithread.c -lpthread

