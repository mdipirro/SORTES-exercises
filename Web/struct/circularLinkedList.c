#include <stdio.h>
#include <stdlib.h>

struct cll {
    int item;
    struct cll* next;
};

const struct cll* get_item_by_filter(const struct cll* const, int (*cmp_function)(int, int));
int gt(int, int);
int lt(int, int);
struct cll* last(struct cll* const);
int length(const struct cll* const);

void display_menu();
void add(struct cll**, int, int);
void delete(struct cll**, int);
const struct cll* min(const struct cll* const);
const struct cll* max(const struct cll* const);
int find(const struct cll* const, int);
void print(const struct cll* const);

/** Return a pointer to an element of the list matching a specific filter imposed by a compare function.
 * @param list The circular linked list
 * @param cmp_function Compare function
 * @return A pointer to an `list`'s element matching a specific filter imposed by `cmp_function`.
 */ 
const struct cll* get_item_by_filter(const struct cll* const list, int (*cmp_function)(int, int)) {
    if (!list) {
        return NULL;
    }
    const struct cll *elem = list -> next, *result = list;
    while (elem != list) {
        if ((*cmp_function)(elem -> item, result -> item)) {
            result = elem;
        }
        elem = elem -> next;
    }
    return result;
}

int gt(int a, int b) {
    return a > b;
}

int lt(int a, int b) {
    return a < b;
}

/**
 * Get the last element of the list.
 * @param list The circular linked list
 * @return A pointer pointing to the last element of the list (the one pointing to the first)
 */ 
struct cll* last(struct cll* const list) {
    if (!list) {
        return NULL;
    }
    struct cll* elem = list;
    while (elem -> next != list) {
        elem = elem -> next;
    }
    return elem;
}

/**
 * Compute the length of a circular linked list.
 * @param list The list.
 * @return `list`'s length
 */ 
int length(const struct cll* const list) {
    if (!list) {
        return 0;
    }
    int length = 1;
    const struct cll* elem = list -> next;
    while (elem != list) {
        length++;
        elem = elem -> next;
    }
    return length;
}

/**
 * Display the main menu.
 */ 
void display_menu() {
    printf("\n==========================================\n");
    printf("===Circular Linked List Operations Menu===\n");
    printf("==========================================\n");
    printf("1) Add a new item\n");
    printf("2) Delete an item\n");
    printf("3) Find min item\n");
    printf("4) Find max item\n");
    printf("5) Find an item\n");
    printf("6) Print all items\n");
    printf("\nEnter your choice: ");
}

/**
 * Add a new item to the list, at the specified position. Since the list is circular,
 * the actual inserting position is mod(pos, length(list)).
 * @param list The circular linked list
 * @param info The new item
 * @param pos The position
 */ 
void add(struct cll** list, int info, int pos) {
    if (!(*list)) {
        (*list) = (struct cll*) malloc(sizeof(struct cll));
        (*list) -> item = info;
        (*list) -> next = *list;
    } else {
        struct cll* elem = *list;
        struct cll* prev = last(*list);
        int p = pos;
        while (pos) {
            pos--;
            elem = elem -> next;
            prev = prev -> next;
        }
        struct cll* new_item = (struct cll*)malloc(sizeof(struct cll));
        new_item -> item = info;
        new_item -> next = elem;
        prev -> next = new_item;
        if (!p) {
            (*list) = new_item;
        }
    }
}

/**
 * Delete an element at the specified position.Since the list is circular,
 * the actual deleting position is mod(pos, length(list)).
 * @param list The circular linked list
 * @param pos The position
 */ 
void delete(struct cll** list, int pos) {
    if (*list) {
        int l = length(*list);
        if (l == 1) {
            free(*list);
            *list = NULL;
        } else {
            pos = pos % l;
            int p = pos;
            struct cll* elem = *list;
            struct cll* prev = last(*list);
            while (pos) {
                pos--;
                elem = elem -> next;
                prev = prev -> next;
            }
            prev -> next = elem -> next;
            free(elem);
            if (!p) {
                *list = prev -> next;
            }
        }
    }
}

/**
 * Find the maximum element of the list.
 * @param list The circular linked list
 * @return A pointer to the maximum element in the list.
 */ 
const struct cll* max(const struct cll* const list) {
    return get_item_by_filter(list, &gt);
}

/**
 * Find the minimum element of the list.
 * @param list The circular linked list
 * @return A pointer to the minimum element in the list.
 */ 
const struct cll* min(const struct cll* const list) {
    return get_item_by_filter(list, &lt);
}

/**
 * Find the position of a given item.
 * @param list The circular linked list
 * @param item The item to be found
 * @return The position of the item, if any, -1 otherwise
 */ 
int find(const struct cll* const list, int item) {
    if (!list) {
        return -1;
    }
    if (list -> item == item) {
        return 0;
    }
    const struct cll* elem = list -> next;
    int found = 0, pos = 0;
    while (elem != list && !found) {
        if (elem -> item == item) {
            found = 1;
        } else {
            elem = elem -> next;
            pos++;
        }
    }
    return (found) ? pos + 1 : -1;
}

/** Print the circular linked list. The function prints every item, from the first to the last. The last shown 
 * item is to be considered as the last item in the list, linked with the first.
 * @param list The circular linked list
 */
void print(const struct cll* const list) {
    if (list) {
        printf("%d ", list -> item);
        const struct cll* elem = list -> next;
        while (elem != list) {
            printf("%d ", elem -> item);
            elem = elem -> next;
        }
    } else {
        printf("Empty list");
    }
}

int main() {
    int choice;
    struct cll* list = NULL;

    print(list);
    printf("\n");
    printf("List's length (should be 0): %d\n", length(list));
    add(&list, 5, 1); add(&list, 2, 5);
    add(&list, 3, 0); add(&list, 4, 0);
    add(&list, 9, 4); add(&list, 8, 6);
    print(list); // Should be 4 8 3 5 2 9
    printf("\n");
    printf("Look for 5's position (should be 3): %d\n", find(list, 5));
    printf("Look for 9's position (should be 5): %d\n", find(list, 9));
    printf("Look for 2's position (should be 4): %d\n", find(list, 2));
    printf("Minimum item (should be 2): %d\n", min(list) -> item);
    printf("Maximum item (should be 9): %d\n", max(list) -> item);
    printf("Last element (should be 9: %d\n", last(list) -> item);
    printf("List's length (should be 6): %d\n", length(list));
    delete(&list, 0); delete(&list, 4);
    print(list); printf("\n"); // Should be 8 3 5 2
    delete(&list, 1); delete(&list, 1);
    print(list); printf("\n"); // Should be 8 2
    delete(&list, 1); delete(&list, 0);
    print(list); printf("\n"); // Should be empty
    /*do {
        display_menu();
        scanf("%d", &choice);
        int item, pos;
        const struct cll* elem;
        switch (choice) {
            case 1: 
                printf("\nEnter the position you want to add the new item at: ");
                scanf("%d", &pos);
                printf("\nEnter the new item: ");
                scanf("%d", &item);
                add(&list, item, pos);
                break;
            case 2:
                printf("\nEnter the position you want to delete the item at: ");
                scanf("%d", &pos);
                delete(&list, pos);
                break;
            case 3:
                elem = min(list);
                if (elem) {
                    printf("\nThe minimum item is: %d", elem -> item);
                } else {
                    printf("Empty list");
                }
                break;
            case 4:
                elem = max(list);
                if (elem) {
                    printf("\nThe maximum item is: %d", elem -> item);
                } else {
                    printf("Empty list");
                }
                break;
            case 5:
                printf("Enter the item you want to look for: ");
                scanf("%d", &item);
                printf("The first occurrence of %d is at position: %d", item, find(list, item));
                break;
            case 6:
                print(list);
                break;
        }
    } while(choice);*/
    return 0;
}