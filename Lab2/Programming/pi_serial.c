#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int totalPointsInsideACircle = 0;

void PointsInsideACircle(int nPoints) {
	int seed = rand();
	srand(time(NULL));
	for(int  i =0; i < nPoints; i++){    
		double x = 1.0 * rand_r(&seed) / (RAND_MAX / 2) - 1;
		double y = 1.0 * rand_r(&seed) / (RAND_MAX / 2) - 1;
		if((x*x) + (y*y) <= 1){
		    totalPointsInsideACircle++;
		}
	}
}

int main(int argc, char* argv[]){
	// Start calculating time of a program
	struct timeval start, end;
  	gettimeofday(&start, NULL);
  	
	if (argc != 2) {
		printf("Missing nPoint !\n");
		return -1;
	}
		
	int nPoints = atoi(argv[1]);
	// Generate and calculate total points inside a circle
	PointsInsideACircle(nPoints);

	// Calculate pi value
	double pi = 4*((double)(totalPointsInsideACircle)/(double)nPoints);
	printf("pi: %f\n", pi);

	// End of calculating time
	gettimeofday(&end, NULL);
	
	// Calculate time spent	
	double time_spent = end.tv_sec + end.tv_usec / 1e6 - start.tv_sec - start.tv_usec / 1e6;
	printf("The elapsed time is %f seconds\n", time_spent);
	
	return 0;
}
