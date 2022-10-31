#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_ITEMS 5
#define THREADS 1 // 1 producer and 1 consumer
#define LOOPS 2*MAX_ITEMS // variable
// Init buffer
int buffer[MAX_ITEMS] ;
int fill = 0 ;
int use = 0 ;
/*TODO: Fill in the synchronization stuff */
void put ( int value ) ; // put data i n t o b u f f e r
int get() ; // g e t data from b u f f e r

// semaphore
sem_t	semEmpty;
sem_t	semFull;
// mutex
pthread_mutex_t mutex;
void *producer ( void *arg ) {
	int i ;
	int tid = *((int*)arg);
	
	for ( i = 0 ; i < LOOPS; i++) {
		
		sem_wait(&semEmpty);		
		pthread_mutex_lock(&mutex);
		// TODO: F i l l in t h e s y n c h r o n i z a t i o n s t u f f 
		
		put (i) ; // l i n e P2
		printf( "Producer %d put data %d\n" , tid , i ) ;
		sleep(1) ;
		// TODO: F i l l in t h e s y n c h r o n i z a t i o n s t u f f
		pthread_mutex_unlock(&mutex);
		sem_post(&semFull);
		
	}
	sem_post(&semFull);
	pthread_exit(NULL) ;
}
void *consumer ( void *arg ) {
	int i , tmp = 0 ;
	int tid = *((int*)arg);
	
	while ( tmp != - 1) {
		
		sem_wait(&semFull);
		pthread_mutex_lock(&mutex);
		// TODO: Fill in the synchronization stUƒƒ 
		tmp = get() ; // l i n e C2
		printf( "Consumer %d get data %d\n" , tid , tmp ) ;
		sleep(1) ;
		// TODO: Fill in the synchronization stUƒƒ 
		pthread_mutex_unlock(&mutex);
		sem_post(&semEmpty);
		
	}
	
	pthread_exit(NULL) ;
}
int main(int argc, char **argv) {
	int i, j;
	int tid [THREADS];
	pthread_t producers [THREADS];
	pthread_t consumers [THREADS];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&semEmpty, 0, 2);
	sem_init(&semFull, 0, 0);
	
	// TODO: Fill in the synchronization stUƒƒ 
	
	for (i = 0; i < THREADS; i++) {
		tid[i] = i;
		pthread_create (&producers[i], NULL, producer, &tid[i]);
		pthread_create (&consumers[i], NULL, consumer, &tid[i]);
	}
	for (i= 0; i < THREADS; i++) {
		pthread_join(producers[i], NULL);
		pthread_join(consumers[i], NULL);
	}
	sem_destroy(&semEmpty);
	sem_destroy(&semFull);
	return 0;
}

void put(int value) {
	buffer[fill] = value;
	fill = (fill + 1) % MAX_ITEMS;
}

int get() {
	int tmp = buffer[use];
	use = (use + 1) % MAX_ITEMS;
	return tmp;
}
