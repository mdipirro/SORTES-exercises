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
    enum bool (*predicate) (struct my_data data);
};

struct f_list* f_list_init(enum bool (*predicate) (struct my_data data));
enum bool f_list_insert(struct f_list*, struct my_data);

struct f_list* f_list_init(enum bool (*predicate) (struct my_data data)) {
    struct f_list* list = (struct f_list*) malloc(sizeof(struct f_list));
    list -> head = NULL;
    list -> predicate = predicate;
}

enum bool f_list_insert(struct f_list* list, struct my_data data) {
    if (!(*list -> predicate)(data)) {
        return FALSE;
    }
    struct f_elem* node = (struct f_elem*) malloc(sizeof(struct f_elem));
    node -> info = (struct my_data*) malloc(sizeof(struct my_data));
    *(node -> info) = data;
    node -> next = NULL;
    if (!list -> head) {
        list -> head = node;
    } else {
        struct f_elem* x = list -> head;
        while (x -> next) {
            x = x -> next;
        }
        x -> next = node;
    }
    return TRUE;
}

int main() {

    return 0;
}