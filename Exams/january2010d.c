#include <stdio.h>
#include <stdlib.h>

#define DST_SIZE 5

size_t strlcpy(char *dst, const char *src, size_t dstsize) {
    size_t length = 0;
    while (dstsize - 1 && *src) {
        *dst++ = *src++;
        length++;
        dstsize--;
    }
    *dst = '\0';
    while (*src++) {
        length++;
    }
    return length;
}

char* strtok_r(char *s1, const char *s2, char **lasts) {
    if (*s2) { // if s2 actually contains something
        if (!*s1) {
            if (*lasts == s1 + 1 && **lasts) { // lasts points to the beginning of the following token
                s1++;
            } else if (!**lasts) { // lasts point to a null char
                return NULL;
            }
        }
        int found = 0;
        char *p = s1;
        while (*s1 && !found) {
            const char *q = s2;
            while (*q && !found) { // compare separators and current char
                found = *s1 == *q;
                q++;
            }
            s1++;
        }
        *lasts = s1; // lasts is now either a null char or the separator
        if (*s1 || found) { // end of s1 with a valid separator 
            s1--; // points back to the separator
            *s1 = '\0';
        }
        return p;
    } 
    return NULL;
}

int main() {
    char *src = "HelloWorld!", dst[DST_SIZE];
    int length = strlcpy(dst, src, DST_SIZE);
    printf("src = %s\tdst = %s\nsrc's length: %d\n", src, dst, length);

    char *sep1 = "-.", *sep2 = "/", string[10] = "ab.cd-f/g\0", *last = NULL;
    printf("Should be \"ab\": %s\n", strtok_r(&string[0], sep1, &last));
    printf("Should be \"cd\": %s\n", strtok_r(&string[2], sep1, &last));
    printf("Should be \"f\": %s\n", strtok_r(&string[5], sep2, &last));
    printf("Should be \"g\": %s\n", strtok_r(&string[7], sep2, &last));
    printf("Should be NULL: %p\n", strtok_r(&string[9], sep2, &last));
    return 0;
}