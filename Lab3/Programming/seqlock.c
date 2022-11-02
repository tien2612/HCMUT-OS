#include "seqlock.h"
#include "time.h"
#include <stdlib.h>
//pthread_seqlock_t seqlock;

pthread_spinlock_t spinLock;
pthread_mutex_t    mutex;
int pshared = 0;

int pthread_seqlock_init(pthread_seqlock_t *seqlock) {
	 seqlock->counter = 0; // odd value
	 seqlock->commingRead = 0;
	 return 1;
}

int pthread_seqlock_destroy(pthread_seqlock_t *seqlock) {
	seqlock = NULL;
	
	return 1;
}

int isWriting(pthread_seqlock_t *seqlock) {
	return (seqlock->counter % 2 == 1);
}

int pthread_seqlock_wrlock(pthread_seqlock_t *seqlock) {
	pthread_spin_init(&spinLock, pshared);
    pthread_mutex_init(&mutex, NULL);
	// if new reader is comming to read, writer needs to wait until readers done.
	while (seqlock->commingRead) {
		return pthread_seqlock_wrlock(seqlock);
	}
    if (seqlock->counter == 0 || seqlock->counter % 2 == 1) {
        pthread_mutex_lock(&mutex);
        seqlock->counter++; // increase counter by one to an odd value;
        pthread_spin_lock(&spinLock);
        pthread_mutex_unlock(&mutex);
    } else if (seqlock->counter % 2 == 1) {
        seqlock->counter++; // increase counter by one to an odd value;
        pthread_spin_lock(&spinLock);
    }

	return 1;
}

int pthread_seqlock_wrunlock(pthread_seqlock_t *seqlock) {
	pthread_spin_init(&spinLock, pshared);
	seqlock->counter = 2; // set counter to an even value to allow reader can access
	pthread_spin_unlock(&spinLock);
	
	return 1;
}

int pthread_seqlock_rdlock(pthread_seqlock_t *seqlock) {
    pthread_mutex_init(&mutex, NULL);
	seqlock->commingRead++;
	if (seqlock->counter == 0) {
        pthread_mutex_lock(&mutex);
		while (isWriting(seqlock));
    } else if (seqlock->counter % 2 == 0)
        while (isWriting(seqlock));

    pthread_mutex_unlock(&mutex);
	return 1;
}

int pthread_seqlock_rdunlock(pthread_seqlock_t *seqlock) {
	seqlock->commingRead--;
	
	return 1;
	
}
