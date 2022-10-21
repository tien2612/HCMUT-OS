#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>           
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_SEMS "/sem_shared_memory"

typedef struct {
	int shared_var; // Shared variable
	int flag; 	// Flag to know that done reading a file
	long int line;	// Total line of a line
	sem_t sem1;
	sem_t sem2;
    
} Sems;


int main() {
	
	// Opening the shared memory 
    	int fd_shm = shm_open(SHM_SEMS, O_RDWR | O_CREAT | O_EXCL,  S_IRUSR | S_IWUSR);

	ftruncate(fd_shm, sizeof(Sems));

	Sems *sems = mmap(NULL, sizeof(Sems), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);

	sem_init(&sems->sem1, 1, 0);
	sem_init(&sems->sem2, 1, 0);

	FILE* file;
	for (int i = 0; i < 2; i++) { // Create 2 childs
		pid_t pid = fork();
		// Reset value for reading next file text
		float avg_rating = 0;
		sems->line = 0;
		sems->flag = 0;
		
		if (!i) file = fopen("movie-100k_1.txt", "r");
		else file = fopen("movie-100k_2.txt", "r");
		
		if (pid == -1) {
			perror("forK");
			exit(1);
		}
		if (pid == 0) { // Child process
			int i = 0;
			char str[50], temp[50];
			if(file == NULL) {
				printf("File can't be opened !");
				return -1;
			} 
			while(fscanf(file, "%s,", str) != EOF) {
				i = 0;
				sems->line++;
				while (i < 2) { 		// Find rating score in line
					i++;
					fscanf(file, "%s,", str);
				}
				fscanf(file, "%s,", temp); 	// Skip for next line
				
				int number = str[0] - 48;
				sems->shared_var = number;
				
				sem_post(&sems->sem1); 	// Allow father to calculate
				sem_wait(&sems->sem2); 	// Wait for father done
			}
			sem_post(&sems->sem1);
			sems->flag = 1; // Done reading file
			if (i) munmap(sems, sizeof(Sems));
		} 
		else { // Father
			while(1) {
				sem_wait(&sems->sem1); 	// Wait for child reading rating score
				if (sems->flag == 1) break;
				avg_rating += sems->shared_var;
				sem_post(&sems->sem2); 	// Allow child to continue reading
			}
			printf("Average rating from file %d is: %f \n", i + 1, avg_rating / sems->line); // Calculate average rating
			if (i == 1) { 	// Done reading two files text
				// Destroys the sems
				sem_destroy(&sems->sem1);
				sem_destroy(&sems->sem2);
				// Unmapping the sems 
				munmap(sems, sizeof(Sems));

				// Destroying the shared memory
				shm_unlink(SHM_SEMS);
			}
		}
		
	}
	return 0;
}
