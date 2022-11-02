#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

#define MAX_LOG_LENGTH 	10
#define MAX_BUFFER_SLOT	5

char **logbuf;

pthread_mutex_t mutex;
int current_index = 0;  // current index of logbuf

// generate random string to passing as an argument (new_data) to wrlog
char *randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";        
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {            
            for (int n = 0;n < length;n++) {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

int wrlog ( /*char** logbuf ,*/ char* new_data );
int flushlog ( /*char** logbuf*/ );

int main () {
    srand(time(NULL));
    pthread_mutex_init(&mutex,NULL);    
    
    logbuf = (char**)malloc(MAX_BUFFER_SLOT * sizeof(char)*MAX_LOG_LENGTH);

    // append 10 * MAX_BUFFER_SLOT = 50 log with random max string length is MAX_LOG_LENGTH
    for (int i = 0; i < 10 * MAX_BUFFER_SLOT; i++)
        wrlog( randstring(rand() % MAX_LOG_LENGTH) ) ;

    printf("Last flushlog(), the new log becomes an empty log.\n");
    flushlog();
    printf("Check if we can use flushlog() to an empty log !!\n");
    pthread_mutex_destroy(&mutex);
    //pthread_cond_destroy(&limit);
    free(logbuf);
    return 0;
}

int wrlog(char *new_data) {
	if (current_index == MAX_BUFFER_SLOT) {
        pthread_mutex_lock(&mutex);
        flushlog();
    }
    printf("wrlog(): %s\n", new_data);
    logbuf[current_index] = new_data;
    current_index++;
    return 1;
}

// int flushlog(int log[MAX_BUFFER_SLOT]);
int flushlog(/*char** logbuf*/){
    for (int i = 0 ;i < current_index; i++){
        printf("flushlog() slot %d: %s\n", i, logbuf[i]);
        logbuf[i] = "";
    }
    int tmp = current_index;
    current_index = 0;
    if (tmp == MAX_BUFFER_SLOT){
        for (int i = 0 ;i < tmp;i++){
            pthread_mutex_unlock(&mutex);
        }
    }
    return 0;
}
