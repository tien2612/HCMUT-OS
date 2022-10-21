#include <stdio.h>
#include "factorial.h"
#include "readline.h"

#define MAX_CHARACTER 50

int main(int argc, char *argv[])
{
	// if (argc < 2) return -1;
	char line[MAX_CHARACTER];
	while (1) {
		int i = 0;
		while (i < MAX_CHARACTER) {
		    char input = getchar();
		    line[i] = input;
		    if(line[i] == '\n' || line[i] == EOF) break;
		    i++;
		}
		if (read_line(line) == 0) printf("%d\n", -1);
		else {
		    int number = 0;
		    
		    for (int i = 0; line[i] != '\n'; i++) {
			int charToNumber = line[i] - 48;
			number*= 10;
			number += charToNumber;
		    }
		    printf("%d\n", factorial(number));
		}
	}
	return 0;
}
