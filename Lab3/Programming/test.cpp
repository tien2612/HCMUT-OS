#include<stdio.h>
#include <iostream>
using namespace std;
int wrlog(char** logbuf, char *new_data) {
        *logbuf = new_data;
        cout << **logbuf;
        return 1;
}
int main(){
    char a = 4;
    char b[] = "b123ig";
    char c[] = "ca123ke";
    
    char *word = &a;
    
    char **word_ptr = &word;
    wrlog(word_ptr, word);
    // for (int i = 0; i < 3; i++) {
    //      char randomletter = 'A' + (random() % 10);
    //     // cout << randomletter << endl;
    //     cout << **word_ptr << " " << *word_ptr << '\n';
    //     word_ptr++;
    // }
    return 0;
}
