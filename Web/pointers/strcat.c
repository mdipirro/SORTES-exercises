#include <stdio.h>
#include <stdlib.h>

/**
 * This exercise is taken from http://www.learntosolveit.com/cprogramming/Ex_5.3_strcat.html
 */

void my_strcat(char* s, char* t) {
    while (*s) {s++;}
    while (*t) {
        *s = *t;
        s++;
        t++;
    }
}

int main() {
    char s[10] = "Hello", *t = "World";
    printf("BEFORE s = %s\tt = %s\n", s, t);
    my_strcat(s, t);
    printf("AFTER s = %s\tt = %s\n", s, t);
}