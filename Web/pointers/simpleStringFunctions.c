#include <stdlib.h>
#include <stdio.h>

/**
 * This exercise is taken from http://www.learntosolveit.com/cprogramming/Ex_5.5_strncpy.html
 */ 

void mystrncpy(char *,char *,int);
void mystrncat(char *, char *, char *, int);
int mystrncmp(char *, char *, int);

void mystrncat(char *s, char *t, char *dest, int n) {
    while (*s && n) {
        *dest++ = *s++;
        n--;
    }
    while (*t && n) {
        *dest++ = *t++;
        n--;
    }
    *dest = '\0';
}

void mystrncpy(char* s,char* t, int n) {
    while (*t && *s && n) {
        *s++ = *t++;
        n--;
    }
}

int mystrncmp(char *s, char *t, int n) {
    int equal = 1;
    while (*s && *t && n && equal) {
        equal = *s == *t;
        s++; t++; n--;
    }
    return equal;
}

int main() {
    char s1[6] = "Hello\0", s2[6] = "Hello\0", *t = "World", dest[10];
    printf("s1 equals s2: %d\n", mystrncmp(s1, s2, 5));
    mystrncpy(s1, t, 3);
    printf("Copying the first 3 chars of t on s1: %s\n", s1);
    mystrncpy(s1, t, 5);
    printf("Copying the first 5 chars of t on s1: %s\n", s1);
    mystrncat(s2, s1, dest, 8);
    printf("Concatenating s1 and s2 for 8 chars: %s\n", dest);
    return 0;
}