#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define tnum 		100		// Number of threads
#define seedarrnum 	1000000	// limit max arrsz can be generated
int seednum = 5000;			// limit max number can be generated

int *buf;				// global array to store random number
int sumbuff = 0;			// total sum of array 'buf'
	
typedef struct {
	int start;
	int end;
} _range;

int* generate_array_data(int *buf, int arraysize, int seednum) {
	for (int i = 0; i < arraysize; i++) {
		buf[i] = rand() % seednum;
		//printf("buf %d %d\n",i, buf[i]);
	}
	return buf;
}

void* sum_worker(void *k) {
	_range *idx_range= (_range*)k;
	printf("In worker from %d to %d\n" , idx_range->start, idx_range->end) ;
	for(int  i = idx_range->start; i < idx_range->end; i++){    
		sumbuff += buf[i];
	}
	pthread_exit(EXIT_SUCCESS);
}
//
int main(int argc, char* argv[]){
	// Start calculating time of a program

	srand(time(NULL));
	pthread_t tid[tnum];
	_range idx_range[tnum];
	int arrsz = rand() % seedarrnum;
	
	int rem = 0;
	int step = 0;
	if (arrsz < tnum) {
		rem = tnum - arrsz; // Number of threads doesnt need to create
		step = 1;
	}
	else step = arrsz / tnum;
	
	// init array 'buf'
	buf = malloc(sizeof(_range) + arrsz * sizeof(int));
	buf = generate_array_data(buf, arrsz, seednum);
	
	// If the system generates fewer arrsz than the number of threads, so only 'arrsz' threads need to be created.
	// and step of each thread is 1
	// else we dont need to worry about it.
	int max_index;//
	if (rem != 0) {
		 max_index = arrsz;
	} else max_index = tnum;
	// Create threads and start to calculate total sum of each thread
	for (int i = 0; i < max_index; i++) {
		idx_range[i].start = step * i;
		idx_range[i].end = step * (i + 1);
		pthread_create(&tid[i], NULL, sum_worker, &idx_range[i]);
	}

	// Join all threads
	for (int i = 0; i < max_index; i++) {
		pthread_join(tid[i],NULL);
	}

	free(buf);
	printf("Total sum of buf is: %d\n", sumbuff);
	pthread_exit(EXIT_SUCCESS);
	return 0;
}
