#include <stdio.h>
#include <stdlib.h>

#define MAXDIGITS 100

enum bool {FALSE, TRUE};

size_t strlcpy(char *dst, const char *src, size_t dstsize) {
    char* p = dst;
    size_t length = 0;
    while (*src && dstsize > 1) { // leave spot for the termination
        *p++ = *src++;
        length++;
        dstsize--;
    }
    *p = '\0';
    while (*src) {
        length++;
        src++;
    }
    return length;
}

char *strtok_r(char *s1, const char *s2, char **lasts) {
    if (!*s1) {
        if (s1 == *lasts) { // end of the string
            return NULL; 
        } else { // something more to read
            s1 = *lasts;
        }
    }
    char* token = s1; // set the beginning od the token
    enum bool stop = FALSE; // TRUE iff a separator is found
    while (*s1 && stop == FALSE) {
        const char *p = s2;
        while (*p) { // look for a separator matching the current char
            if (*p == *s1) {
                stop = TRUE;
            }
            p++;
        }
        if (!stop) { // go ahead iff the current char is not a separator
            s1++;
        }
    }
    if (!*s1) { // end of the string
        *lasts = s1; // terminate
        return (token == s1) ? NULL : token;
    } else { // separator found
        *s1 = '\0';
        *lasts = s1 + 1;
        return token;
    }
}

char* i2a(int value, int base) {
    enum bool negative = FALSE;
    if (value < 0) {
        if (base == 10) {
            negative = TRUE;
        }
        value *= -1;
    }
    int n = value, i = 0;
    char digits[MAXDIGITS];
    do {
        int rem = n % base;
        digits[i++] = (rem < 10) ? rem + '0' : 'A' + (rem - 10);
        n /= base;
    } while (n);
    char* number = (char*) malloc(sizeof(char) * i + negative);
    i--; 
    int start = 0, length = i + 1 + negative;
    if (negative) {
        number[0] = '-';
        start = 1;
    }
    for (int j = start; j < length; j++) {
        number[j] = digits[i];
        i--;
    }
    number[length] = '\0';
    return number;
}

int main() {
    char *src = "HelloWorld!", dst[5];
    int length = strlcpy(dst, src, 5);
    printf("src = %s\tdst = %s\nsrc's length: %d\n", src, dst, length);

    printf("\n\n\n");
    char *sep1 = "-.", *sep2 = "/", string[10] = "ab.cd-f/g\0", *last = NULL;
    printf("Should be \"ab\": %s\n", strtok_r(&string[0], sep1, &last));
    printf("Should be \"cd\": %s\n", strtok_r(&string[2], sep1, &last));
    printf("Should be \"f\": %s\n", strtok_r(&string[5], sep2, &last));
    printf("Should be \"g\": %s\n", strtok_r(&string[7], sep2, &last));
    printf("Should be NULL: %p\n", strtok_r(&string[9], sep2, &last));

    printf("\n\n\n");
    printf("30 base 16 = %s (should be 1E)\n", i2a(30, 16));
    printf("50 base 25 = %s (should be 20)\n", i2a(50, 25));
    printf("-20 base 10 = %s (should be -20)\n", i2a(-20, 10));
    printf("-20 base 2 = %s (should be 10100)\n", i2a(-20, 2));
    return 0;
}