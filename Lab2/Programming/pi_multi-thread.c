#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define NUM_THREADS 100
typedef struct {
	int id;
	int nPoints;
	int totalPointsInsideACircle;
} thread_struct;

void* PointsInsideACircle(void *k) {
	thread_struct *thread_data_array = (thread_struct*)k;
	int seed = rand();
	srand(time(NULL));
	
	for(int  i =0; i < thread_data_array->nPoints; i++){    
		double x = 1.0 * rand_r(&seed) / (RAND_MAX / 2) - 1;
		double y = 1.0 * rand_r(&seed) / (RAND_MAX / 2) - 1;
		if((x*x) + (y*y) <= 1){
		    thread_data_array->totalPointsInsideACircle++;
		}
	}
	pthread_exit(EXIT_SUCCESS);
}
int main(int argc, char* argv[]){
	// Start calculating time of a program
	struct timeval start, end;
  	gettimeofday(&start, NULL);
  	
	if (argc != 2) {
		printf("Missing nPoint !\n");
		return -1;
	}
	
	pthread_t tid[NUM_THREADS];
	thread_struct thread_data_array[NUM_THREADS];
	
	int nPoints = atoi(argv[1]);
	
	// Create threads and start to calculate total points in a circle of each thread
	for (int i = 0; i < NUM_THREADS; i++) {
		thread_data_array[i].id = i;
		thread_data_array[i].nPoints = nPoints / NUM_THREADS;
		thread_data_array[i].totalPointsInsideACircle = 0;
		pthread_create(&tid[i], NULL, PointsInsideACircle, &thread_data_array[i]);
	}
	
	// Combine total points from each thread
	int totalPointsInsideACircle = 0;
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(tid[i],NULL);
		totalPointsInsideACircle += thread_data_array[i].totalPointsInsideACircle;
	}
	// Calculate pi value
	double pi = 4*((double)(totalPointsInsideACircle)/(double)nPoints);
	printf("pi: %f\n", pi);

	// End of calculating time
	gettimeofday(&end, NULL);
	
	// Calculate time spent	
	double time_spent = end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6;
	printf("The elapsed time is %f seconds\n", time_spent);
	pthread_exit(EXIT_SUCCESS);
	return 0;
}
