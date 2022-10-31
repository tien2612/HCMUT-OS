#include <stdio.h>
#include <pthread.h>
int MAXCOUNT = 1e6 ;

static int count = 0 ;
pthread_mutex_t mutex;

void  *fcount (void *sid) {
	int i ;
	for ( i = 0 ; i < MAXCOUNT; i++) {
		pthread_mutex_lock(&mutex);
		count = count + 1 ;
		pthread_mutex_unlock(&mutex);
	}
	printf ( "Thread %s : holding %d \n" , ( char *) sid , count ) ;
}
int main() {
	
	pthread_mutex_init(&mutex, NULL);
	
	pthread_t thread1 , thread2 ;
	/* Create independent threads each of which will execute function */
	pthread_create( &thread1 , NULL, &fcount , "1" ) ;
	pthread_create( &thread2 , NULL, &fcount , "2" ) ;
	// Wait for thread1 finish
	pthread_join ( thread1 , NULL) ;
	// Wait for thread2 finish
	pthread_join ( thread2 , NULL) ;
	pthread_mutex_destroy(&mutex);
	return 0 ;
}
