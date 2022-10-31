all:

shared_buffer_problem: shared_buffer_problem.c shared_buffer_problem.o
		gcc -o shared_buffer_problem shared_buffer_problem.c -pthread
		
shrmem_mutex: shared_buffer_problem.c shared_buffer_problem.o
		gcc -o shrmem_mutex shared_buffer_problem.c -pthread

pc: pc.c pc.o
	gcc -o pc pc.c -pthread
	
dinPhl: dinPhl.c dinPhl.o
	gcc -o din dinPhl.c -pthread
