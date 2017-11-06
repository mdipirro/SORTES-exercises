#include <stdlib.h>
#include <stdio.h>

struct elem {
    char* string;
    struct elem* next;
};

char* get_string_from_list(struct elem* list, int n) {
    if (n < 0 || !list) {
        return (char*)"-1";
    }
    while (list && n) {
        list = list -> next;
        n--;
    }
    if (!list) {
        return (char*)-1;
    }
    int length = 0;
    char *s = list -> string;
    while (*s++) {length++;}
    char *copy = (char*)malloc(sizeof(char) * length);
    s = list -> string;
    for (int i = 0; i < length; i++) {
        copy[i] = list -> string[i];
    }
    return copy;
}

int insert_string_in_list(struct elem* list, char* string, int n) {
    while (list && n) {
        list = list -> next;
        n--;
    }
    if (!list) {
        return -1;
    }
    list -> string = string;
    return 0;
}

int main() {
    struct elem *node1 = (struct elem*) malloc(sizeof(struct elem)),
                *node2 = (struct elem*) malloc(sizeof(struct elem)),
                *node3 = (struct elem*) malloc(sizeof(struct elem)),
                *node4 = (struct elem*) malloc(sizeof(struct elem));
    node1 -> string = "Hello"; node2 -> string = "World";
    node3 -> string = "Hello2"; node4 -> string = "World2"; 
    node1 -> next = node2; node2 -> next = node3;
    node3 -> next = node4; node4 -> next = NULL;
    struct elem* list = node1;
    int i = 0;
    while (list) {
        printf("%s\n", get_string_from_list(node1, i++));
        list = list -> next;
    }

    char *s1 = "test", *s2 = "test2";
    insert_string_in_list(node1, s1, 1);
    insert_string_in_list(node1, s2, 3);
    i = 0; list = node1;
    while (list) {
        printf("%s\n", get_string_from_list(node1, i++));
        list = list -> next;
    }

    return 0;
}