#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#define SHM_KEY 0x12345678
#define SNAME "/s22emnames"
struct shared_data{
int counter ;
int writerID ;
};
int main( int argc , char *argv [ ] ) {
	int shmid ;
	struct shared_data *data ;
	sem_t *sem = sem_open(SNAME, O_CREAT,0644) ;
	sem_init (sem, 0 , 1) ;
	shmid = shmget (SHM_KEY, 1000 , 0644 | IPC_CREAT) ;
	if (shmid < 0) {
		perror ("Shared␣memory") ;
		return 1;
	}else {
		printf ("shared␣memory: ␣%d\n" , shmid) ;
	}
	if (sem == SEM_FAILED){
	printf ("Sem␣ f a i l ed \n") ;
	return -1;
	}
	data = ( struct shared_data *)shmat(shmid , 0 ,0) ;
	if(data == ( struct shared_data *)-1) {
		perror ("shmat") ;
		exit (1) ;
	}
	data->counter=0;
	data->writerID=1;
	for ( int i=0; i < 20; i++){
		printf ("Read␣from␣Writer␣ID: ␣%d␣with␣counter : ␣%d\n" , data->writerID , data->counter ) ;
		data->writerID = 1;
		int line = 0;
		int i = 0;
		char str[50], temp[50];
		FILE* file = fopen("movie-100k_1.txt","r");
		while(fscanf(file, "%s,", str) != EOF) {
			sem_wait(sem);
			i = 0;
			line++;
			while (i < 2) { // find rating score in line
				i++;
				fscanf(file, "%s,", str);
			}
			fscanf(file, "%s,", temp); // skip for next line
			
			int number = str[0] - 48;
			data->counter = number;
			printf("Child read: %d\n", data->counter);
			sem_post(sem);
		}
		fclose(file);
		sleep (1) ;
		sem_post(sem);
	}

	if (shmdt(data ) == -1) {
	perror ("shmdt") ;
	return 1;
	}
	if ( shmctl (shmid , IPC_RMID, 0) == -1) {
	perror ("shmctl") ;
	return 1;
	}
	// Remove the named semaphore
	if ( sem_unlink(SNAME) < 0) perror ("sem_unlink(3)␣ f a i l ed ") ;
	return 0;
}
