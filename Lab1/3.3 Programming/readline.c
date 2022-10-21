#include "readline.h"

int read_line(char *str) {
    for (int i = 0; str[i] != '\n'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            continue;
        }
        else return 0;
    }
    return 1;
}
