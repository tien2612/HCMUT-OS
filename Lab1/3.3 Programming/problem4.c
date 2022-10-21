#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

struct Node {
    int data;          // Data 
    struct Node *next; // Address 
};


//struct list{
//	Node *head;
//}list_t;

int main() {
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));
	struct Node* ptr = head;
	int number;
	FILE* file = fopen("numbers.txt","r");
	
	int i = 0;
	if(file == NULL) {
	printf("file can't be opened !");
	return -1;
	}
	
	while (fscanf(file, "%d,", &number) != EOF) {
		struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
		newNode->data = number;
		newNode->next = NULL;

		ptr->next = newNode;
		ptr = ptr->next;
		i++;
	}

	ptr = head->next;

	pid_t pid = fork();
	if (pid == 0) { // child process
		number = 0;
		while(ptr != NULL) {
			if (ptr->data %3 == 0) {
				number++;	
			}
			ptr = ptr->next;
		}
		printf("%d\n", number);
	}

	else if (pid > 0) {
		number = 0;
		while(ptr != NULL) {
			if (ptr->data %2 == 0) {
				number++;
			}
			ptr = ptr->next;
		}
		printf("%d\n", number);
	}
	return 0;
}


