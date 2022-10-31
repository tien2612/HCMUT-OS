#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_LOG_LENGTH 	10
#define MAX_BUFFER_SLOT	5

char **logbuf;

typedef struct {
	int current_index;
	int wait;
} Protect;

Protect protect;

void protect_init(Protect protect) {
	protect.current_index = 0;
	protect.wait = 5;
}

// int wrlog(char **logbuf, char *new_data);
int wrlog(int log[MAX_BUFFER_SLOT], int new_data) {
	log[protect.current_index] = new_data;
	protect.current_index++;
	return new_data;
}

// int flushlog(int log[MAX_BUFFER_SLOT]);
void flushlog(int log[MAX_BUFFER_SLOT]) {
	printf("flushlog()\n");
	for (int i = 0; i < MAX_BUFFER_SLOT; i++) {
		printf( "Slot %d: %d\n", i, log[i] );
	}
}
int main () {
	int log[MAX_BUFFER_SLOT] = {0};
	alarm(5);
	// protect_init(protect);

	srand(time(NULL));
	while(1) {
		if (protect.wait > 0)  {
			printf("wrlog(): %d\n", wrlog(log, rand() % 20));
			protect.wait--;
		} else {
			flushlog(log);
			protect.wait = 5;
			protect.current_index = 0;
		}
	}
	return 0;
}




