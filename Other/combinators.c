/**
 * Write a program implementing the functional combinators `map` and `filter` for lists
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    void* info;
    struct node* next;
};

struct node* new_node(void* info, struct node* next) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node -> info = info;
    node -> next = next;
}

struct node* map(const struct node* list, void* (*f)(void* element)) {
    if (!list) {
        return NULL;
    }
    return new_node((*f)(list -> info), map(list -> next, f));
}

struct node* filter(const struct node* list, int (*p)(void* element)) {
    if (!list) {
        return NULL;
    }
    if ((*p)(list -> info)) {
        return new_node(list -> info, filter(list -> next, p));
    }
    return filter(list -> next, p);
}

struct node* create_test_list() {
    int *first = (int*) malloc(sizeof(int)),
        *second = (int*) malloc(sizeof(int)),
        *third = (int*) malloc(sizeof(int)),
        *fourth = (int*) malloc(sizeof(int)),
        *fifth = (int*) malloc(sizeof(int));
    *first = 10; *second = 20; *third = 30;
    *fourth = 40; *fifth = 97;
    struct node *node1 = new_node(first, NULL),
                *node2 = new_node(second, node1),
                *node3 = new_node(third, node2),
                *node4 = new_node(fourth, node3),
                *head = new_node(fifth, node4);
    return head;
}

void* sum10(void* element) {
    int* new_element = (int*) malloc(sizeof(int));
    *new_element = *(int*)element + 10;
    return (void*)new_element;
}

void* mult2(void* element) {
    int* new_element = (int*) malloc(sizeof(int));
    *new_element = *(int*)element * 2;
    return (void*)new_element;
}

int gt35(void* element) {
    return *(int*)element > 35;
}

int equal_to_a(void* element) {
    return *(char*)element == 'a';
}

void print_as_int(const struct node* const list) {
    if (!list) {
        printf("\n");
    } else {
        printf("%d ", *(int*)list -> info);
        print_as_int(list -> next);
    }
}

int main() {
    struct node* list = create_test_list();
    print_as_int(list);
    print_as_int(map(list, &sum10));
    print_as_int(map(list, &mult2));
    print_as_int(filter(list, &gt35));
    print_as_int(filter(list, &equal_to_a));
    return 0;
}