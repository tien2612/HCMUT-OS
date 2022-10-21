#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

static int pipefd1[2], pipefd2[2] ;

char writingToParent[30] = "Hi Parent! I'm child!";
char writingToChild[30] = "Hi Child! I'm parent!";
char readingFromChild[30];
char readingFromParent[30];

void INIT(void){
	if (pipe (pipefd1) < 0 || pipe (pipefd2) < 0){
		perror("pipe") ;
		exit(EXIT_FAILURE) ;
	}
}

void WRITE_TO_PARENT() {
	write(pipefd1[1], &writingToParent, sizeof(writingToParent));
	printf ("Child send message to parent!\n") ;
}	

void READ_FROM_PARENT() {
	read(pipefd2[0], &readingFromParent, sizeof(readingFromParent));
	printf ("Child receive message from parent: %s\n", readingFromParent) ;
}

void WRITE_TO_CHILD() {
	write(pipefd2[1], &writingToChild, sizeof(writingToChild));
	printf ("Parent send message to child!\n") ;
}

void READ_FROM_CHILD() {
	read(pipefd1[0], &readingFromChild, sizeof(readingFromChild));
	printf ("Parent receive message from child: %s\n\n", readingFromChild) ;
}

int main(int argc , char* argv[]) {
	INIT() ;
	pid_t pid ;
	pid = fork ( ) ;
	// set a timer , process will end after 1 second .
	alarm(10) ;
	if (pid == 0){
		close(pipefd2[1]);
		close(pipefd1[0]);
		while(1){
			sleep (rand() % 2 + 1);
			READ_FROM_PARENT();
			WRITE_TO_PARENT();
		}
	} else {
		close(pipefd2[0]);
		close(pipefd1[1]);
		while(1){
			sleep (rand() % 2 + 1);
			WRITE_TO_CHILD();
			READ_FROM_CHILD();
		}
	}
	return 0;
}
