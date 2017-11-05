#include <stdio.h>
#include <stdlib.h>

enum bool {FALSE, TRUE};

struct my_data {
    void* data;
};

struct f_elem {
    struct my_data* info;
    struct f_elem* next;
};

struct f_list {
    struct f_elem* head;
    enum bool (*predicate)(struct my_data);
};

struct node {
    struct my_data* info;
    struct node* next;
};

struct node* new_node(struct my_data* data, struct node* next) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node -> info = data;
    node -> next = next;
    return node;
}

struct f_elem* new_f_elem(struct my_data* data) {
    struct f_elem* node = (struct f_elem*) malloc(sizeof(struct f_elem));
    node -> info = data;
    node -> next = NULL;
    return node;
}

int f_list_init(enum bool (*predicate)(struct my_data data), struct node* l_list,
                struct f_list** f_list) {
    *f_list = (struct f_list*) malloc(sizeof(struct f_list));
    (*f_list) -> predicate = predicate;
    if (l_list) { // at least one element
        int length = 1;
        (*f_list) -> head = new_f_elem(l_list -> info);
        struct f_elem* prev = (*f_list) -> head;
        l_list = l_list -> next;
        struct f_elem* node = NULL;
        while (l_list) {
            node = new_f_elem(l_list -> info);
            prev -> next = node;
            prev = prev -> next;
            l_list = l_list -> next;
            length++;
        }
        return length;
    }
    (*f_list) -> head = NULL;
    return 0; // empty linked list
}

int f_list_filter(struct f_list* list) {
    if (!list -> head) {
        return 0;
    }
    int elements = 0;
    struct f_elem *node = list -> head, *prev = NULL;
    while (node) {
        if (!(*list -> predicate)(*node -> info)) {
            struct f_elem* to_be_removed = node;
            if (node == list -> head) { // change the head
                list -> head = node -> next;
            } else { // node points after the head
                prev -> next = node -> next;
            }
            node = node -> next;
            free(to_be_removed);
        } else {
            elements++;
            prev = node;
            node = node -> next;
            printf("%p\n", prev -> info);
        }
    }
    return elements;
}

enum bool gt120(struct my_data data) {
    return (*(int*)data.data) > 120;
}

int main() {
    int *head_info = (int*) malloc(sizeof(int)); *head_info = 10;
    char *first_info = (char*) malloc(sizeof(char)); *first_info = 'A';
    char *second_info = (char*) malloc(sizeof(char[6])); 
    second_info[0] = 'H'; second_info[1] = 'e';
    second_info[2] = 'l'; second_info[3] = 'l';
    second_info[4] = 'o'; second_info[5] = '\0';
    double *third_info = (double*) malloc(sizeof(double)); *third_info = 150.1;
    struct my_data  *p1 = (struct my_data*) malloc(sizeof(struct my_data)),
                    *p2 = (struct my_data*) malloc(sizeof(struct my_data)),
                    *p3 = (struct my_data*) malloc(sizeof(struct my_data)),
                    *p4 = (struct my_data*) malloc(sizeof(struct my_data));
    p1 -> data = head_info; p2 -> data = first_info;
    p3 -> data = second_info; p4 -> data = third_info;
    struct node* list = new_node(p1, new_node(p2, new_node(p3, new_node(p4, NULL))));
    struct f_list* f_list = NULL;
    printf("BEFORE the filtering: %d\n", f_list_init(&gt120, list, &f_list));
    printf("AFTER the filtering: %d\n", f_list_filter(f_list));
    printf("Should have kept: %p %p\n", p3, p4);
}