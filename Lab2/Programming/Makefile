all: problem1 pi_multi-thread pi_serial problem3

problem1: problem1.o problem1.c
	gcc -o problem1 problem1.c -pthread -lrt
	
pi_multi-thread: pi_multi-thread.o pi_multi-thread.c
	gcc -o pi_multi-thread pi_multi-thread.c -pthread

pi_serial: pi_serial.o pi_serial.c
	gcc -o pi_serial pi_serial.c

problem3: problem3.c
	gcc -o problem3 problem3.c
	
clean:
	rm -f *.o
