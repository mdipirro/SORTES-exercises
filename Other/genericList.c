/**
 * Implement a generic list where elements may be of any type. The program should include
 * functions for printing, adding and deleting. The program should also include functions
 * for statistical purposes, such as how many elements of a each type there are.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    void* info;
    char* info_type;
    struct node* next;
};

struct type {
    char* type_name;
    int occ;
};

struct node* init_empty() {
    struct node* head = (struct node*) malloc(sizeof(struct node));
    head -> info = NULL;
    head -> info_type = NULL;
    head -> next = NULL;
    return head;
}

struct node* init(void* info, char* info_type) {
    struct node* head = init_empty();
    head -> info = info;
    head -> info_type = (char*) malloc(strlen(info_type));
    char* tmp = head -> info_type;
    while (*info_type) {
        *tmp++ = *info_type++;
    }
    return head;
}

void add_rec(struct node* const list, void* info, char* info_type, int position) {
    // PRE: non-empty list
    if (!(position - 1) || !list -> next) {
        struct node* node = init(info, info_type);
        node -> next = list -> next;
        list -> next = node;
    } else {
        add_rec(list -> next, info, info_type, position - 1);
    }
}

void add(struct node** const list, void* info, char* info_type, int position) {
    if (!position) {
        struct node* node = init(info, info_type);
        node -> next = *list;
        *list = node;
    } else {
        add_rec(*list, info, info_type, position);
    }
}

void delete_rec(struct node* const list, int pos) {
    if (list) {
        if (! (pos - 1)) {
            if (list -> next) {
                struct node* to_be_deleted = list -> next;
                list -> next = to_be_deleted -> next;
                free(to_be_deleted);
            }
        } else {
            delete_rec(list -> next, pos - 1);
        }
    }
}

void delete(struct node** const list, int pos) {
    if (!pos) {
        struct node* head = *list;
        *list = head -> next;
        free(head);
    } else {
        delete_rec(*list, pos);
    }
}

struct type* init_type(const char* type_name) {
    struct type* type = (struct type*) malloc(sizeof(struct type));
    type -> type_name = (char*) malloc(strlen(type_name));
    char* name = type -> type_name;
    while (*type_name) {
        *name++ = *type_name++;
    }
    type -> occ = 1;
}

void update_stats(struct node* stats, const char* type_name) {
    if (!strcmp(((struct type*) stats -> info) -> type_name, type_name)) {
        ((struct type*) stats -> info) -> occ++;
    } else if (stats -> next) {
        update_stats(stats -> next, type_name);
    } else {
        struct node* node = init(init_type(type_name), "type_metadata");
        stats -> next = node;
    }
}

struct node* stats_rec(const struct node* const list, struct node* stats) {
    if (!list) {return stats;}
    update_stats(stats, list -> info_type);
    return stats_rec(list -> next, stats);
}

const struct node* stats(const struct node* const list) {
    if (!list) {return NULL;}
    int *p = (int*) malloc(sizeof(int)); *p = 10;
    struct node* stats_list = init(init_type(list -> info_type), "type_metadata");
    return stats_rec(list -> next, stats_list);
}

int main() {
    struct node* list = init_empty();
    printf("The head should be empty: %p\n", list -> info);
    free(list);
    int *head_info = (int*) malloc(sizeof(int)); *head_info = 10;
    char *first_info = (char*) malloc(sizeof(char)); *first_info = 'A';
    char *second_info = (char*) malloc(sizeof(char[6])); 
    second_info[0] = 'H'; second_info[1] = 'e';
    second_info[2] = 'l'; second_info[3] = 'l';
    second_info[4] = 'o'; second_info[5] = '\0';
    double *third_info = (double*) malloc(sizeof(double)); *third_info = 3.1;
    list = init(head_info, "int");
    printf("The head should be non-empty: %d\n", *(int*)list -> info);
    printf("The head should have type \"int\": %s\n", (char*)list -> info_type);
    add(&list, first_info, "char", 2);
    add(&list, second_info, "string", 0);
    add(&list, third_info, "double", 1); add(&list, third_info, "double", 10);
    printf("AFTER ADDITION\n");
    printf("The first element should be \"Hello\": %s\n", (char*)list -> info);
    printf("The second element should be 3.1: %e\n", *(double*)list -> next -> info);
    printf("The third element should be 10: %d\n", *(int*)list -> next -> next -> info);
    printf("The fourth element should be 'A': %c\n", *(char*)list -> next -> next -> next -> info);

    printf("STATS\n");
    const struct node* stats_list = stats(list);
    while (stats_list) {
        struct type* metadata = (struct type*)stats_list -> info;
        printf("%s %d\n", metadata -> type_name, metadata -> occ);
        stats_list = stats_list -> next;
    }

    delete(&list, 0); delete(&list, 1);
    printf("AFTER DELETION\n");
    printf("The first element should be 3.1: %e\n", *(double*)list -> info);
    printf("The second element should be 'A': %c\n", *(char*)list -> next -> info);
    return 0;
}