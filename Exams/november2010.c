#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct data {
    int info;
};

struct elem {
    struct data data;
    struct elem* next;
};

struct node {
    struct data data;
    struct node* next;
    struct node* spoke;
};

/**
 * Error codes:
 * -) -1 -> empty list
 * -) -2 -> not enough nodes in the list
 */ 
int list_to_wheel(int n, void** list) {
    if (!list) {
        return -1;
    }
    struct node* pointers[n];
    int i = 0;
    struct elem* elem = *((struct elem**) list);
    while (elem) {
        struct node* node = (struct node*) malloc(sizeof(struct node));
        pointers[i] = node;
        node -> data = elem -> data;
        if (i) {
            pointers[i - 1] -> next = node;
        }
        elem = elem -> next;
        i++;
    }
    double limit = pow(2, n);
    if (i < limit) {
        return -2; 
    }
    for (int i = 0; i < limit; i++) {
        pointers[i] -> spoke = pointers[(int)fmod(i + pow(2, n - 1), limit)];
    }
    *list = pointers[0];
    return 0;
}

int main() {
    struct elem *node1 = (struct elem*) malloc(sizeof(struct elem)),
                *node2 = (struct elem*) malloc(sizeof(struct elem)),
                *node3 = (struct elem*) malloc(sizeof(struct elem)),
                *node4 = (struct elem*) malloc(sizeof(struct elem));
    struct data data;
    data.info = 5; node1 -> data = data; node1 -> next = node2;
    data.info = 10; node2 -> data = data; node2 -> next = node3;
    data.info = 7; node3 -> data = data; node3 -> next = node4;
    data.info = 3; node4 -> data = data; node4 -> next = NULL;

    struct elem* list = node1;
    while (list) {
        printf("%d ", list -> data.info);
        list = list -> next;
    }
    printf("\n");

    list = node1;
    list_to_wheel(2, (void**)&list);
    struct node* wheel = (struct node*) list;
    int i = 0;
    while (i < 4) {
        printf("%d %d\n", wheel -> data.info, wheel -> spoke -> data.info);
        wheel = wheel -> next;
        i++;
    }
    printf("\n");
    return 0;
}