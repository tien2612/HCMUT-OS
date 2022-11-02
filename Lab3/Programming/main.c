#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "seqlock.h"

#define NUM_THREADS 	100

static int protect_variable = 0;
pthread_seqlock_t seqlock;

void* writer_func() {

	printf("Writer is waiting\n");
	printf("Total number of readers are comming %d\n", seqlock.commingRead);
	pthread_seqlock_wrlock(&seqlock);

	printf("Writer is increasing value: %d\n", ++protect_variable);

	pthread_seqlock_wrunlock(&seqlock);
	printf("\n");
	pthread_exit(EXIT_SUCCESS);
}

void* reader_func() {

	printf("Reader wants to read !!\n");
	printf("Total number of readers are comming %d\n", seqlock.commingRead);
	pthread_seqlock_rdlock(&seqlock);
	printf("Reader is reading: Protect variable: %d\n", protect_variable);

	pthread_seqlock_rdunlock(&seqlock);
	printf("\n");

    	pthread_exit(EXIT_SUCCESS);
}

int main() {

	pthread_seqlock_init(&seqlock);
	pthread_t tid[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++) {
		if (i % 2) pthread_create(&tid[i], NULL, writer_func, NULL);
		pthread_create(&tid[i], NULL, reader_func, NULL);
	}
		
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(tid[i],NULL);
	}
	
	
    	printf("Done !! \n");
	pthread_seqlock_destroy(&seqlock);	

	return 0;
}
