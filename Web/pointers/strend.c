#include <stdio.h>
#include <stdlib.h>

/**
 * This exercise is taken from http://www.learntosolveit.com/cprogramming/Ex_5.4_strend.html
 */

int strend(char* s, char* t) {
    char *before_t = t - 1, *before_s = s - 1;
    while(*s) {s++;}
    s--;
    while (*t) {t++;}
    t--;
    while ((t != before_t) && (s != before_s) && (*t == *s)) {
        t--; s--;
    }
    return t == before_t;
}

int main() {
    char *s = "Hello", *t1 = "lo", *t2 = "Hello", *t3 = "World";
    printf("%s occurs at the end of %s? %d\n", t1, s, strend(s, t1));
    printf("%s occurs at the end of %s? %d\n", t2, s, strend(s, t2));
    printf("%s occurs at the end of %s? %d\n", t3, s, strend(s, t3));
}