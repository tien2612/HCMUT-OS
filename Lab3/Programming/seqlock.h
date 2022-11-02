/*
 * seqlock.h
 *
 *  Created on: Oct 30, 2022
 *      Author: Nguyen Phuc Tien - 2014725
 */

#ifndef INC_SEQLOCK_H_
#define INC_SEQLOCK_H_

#include "stdio.h"
#include "pthread.h"


typedef struct {
	int counter;	
	int commingRead;
} pthread_seqlock_t;

int pthread_seqlock_init(pthread_seqlock_t *seqlock);
int pthread_seqlock_destroy(pthread_seqlock_t *seqlock);
int pthread_seqlock_rdlock(pthread_seqlock_t *seqlock);
int pthread_seqlock_rdunlock(pthread_seqlock_t *seqlock);
int pthread_seqlock_wrlock(pthread_seqlock_t *seqlock);
int pthread_seqlock_wrunlock(pthread_seqlock_t *seqlock);

int isWriting(pthread_seqlock_t *seqlock);
#endif /* INC_SEQLOCK_H_ */
