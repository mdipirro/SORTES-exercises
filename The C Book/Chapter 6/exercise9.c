#include <stdio.h>
#include <stdlib.h>

struct doubly_linked_list {
    int info;
    struct doubly_linked_list* prev;
    struct doubly_linked_list* next;
};

int empty(const struct doubly_linked_list* const);
void add(struct doubly_linked_list**, int, int);
void remove_el(struct doubly_linked_list**, int);
void print(struct doubly_linked_list* const);
int length(struct doubly_linked_list* const);

/**
 * Return 1 iff the list is empty
 * @param list a pointer to the first element of the list
 * @return 1 iff the list is empty
 */ 
int empty(const struct doubly_linked_list* const list) {
    return !length((struct doubly_linked_list* const)list);
}

/**
 * Add an element in the list in the specified position. If pos >= length(*list) then the element
 * is added at the end of the list.
 * @param list A pointer pointing to the pointer to the first element of the list
 * @param element The int to be added
 * @param pos The position at which to add the element
 */ 
void add(struct doubly_linked_list** list, int element, int pos) {
    if (!*list) {
        *list = malloc(sizeof(struct doubly_linked_list));
        (*list) -> info = element;
        (*list) -> next = NULL;
        (*list) -> prev = NULL;
    } else {
        struct doubly_linked_list *prev = NULL, *x = *list;
        while (x && pos) {
            prev = x;
            x = x -> next;
        }
        struct doubly_linked_list* node = malloc(sizeof(struct doubly_linked_list));
        node -> info = element;
        node -> prev = prev;
        node -> next = x;
        if (prev) {
            prev -> next = node;
        }
        if (x) {
            x -> prev = node;
        }
    }
}

/**
 * Remove the elementon the list in the specified position. If pos >= than length(*list) then
 * nothing happens.
 * @param list A pointer pointing to the pointer to the first element of the list
 * @param pos The position at which to add the element
 */ 
void remove_el(struct doubly_linked_list** list, int pos) {
    if (list && *list) {
        struct doubly_linked_list* x = *list;
        if (!pos) {
            *list = (*list) -> next;
            (*list) -> prev = NULL;
            free(x);
        } else {
            while (x && pos) {
                x = x -> next;
                pos--;
            }
            if (!pos && x) {
                if (x -> prev) {
                    x -> prev -> next = x -> next;
                }
                if (x -> next) {
                    x -> next -> prev = x -> prev;
                }
                free(x);
            }
        }
    }
}

/**
 * Print the list.
 * @param list A pointer pointing to the first element of the list.
 */ 
void print(struct doubly_linked_list* const list) {
    struct doubly_linked_list* x = list;
    while (x) {
        printf("%d -> ", x -> info);
        x = x -> next;
    }
    printf("NULL\n");
}

/**
 * Compute the length of the list.
 * @param list A pointer pointing to the first element of the list.
 * @return The list's length.
 */ 
int length(struct doubly_linked_list* const list) {
    int l = 0;
    struct doubly_linked_list* x = list;
    while (x) {
        l++;
        x = x -> next;
    }
    return l;
}

int main(void) {
    struct doubly_linked_list* list = NULL;
    printf("---------AFTER CREATION---------\n");
    print(list);
    printf("Empty list: %d\n", empty(list));
    printf("List's length: %d\n", length(list));
    remove_el(&list, 0);
    remove_el(&list, 5);
    for(int i = 0; i < 10; i++) {
        add(&list, i, i);
    }
    printf("---------AFTER ADDs---------\n");
    print(list);
    printf("Empty list: %d\n", empty(list));
    printf("List's length: %d\n", length(list));
    remove_el(&list, 0);
    remove_el(&list, 5);
    remove_el(&list, 8);
    remove_el(&list, 7);
    printf("---------AFTER REMOVALs---------\n");
    print(list);
    printf("Empty list: %d\n", empty(list));
    printf("List's length: %d\n", length(list));
    return 0;
}