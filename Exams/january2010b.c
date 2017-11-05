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

enum bool gt50(struct my_data data) {
    return (*(int*)data.data > 50) ? TRUE : FALSE;
}

enum bool only_lowercase_chars(struct my_data data) {
    char c = *(char*)data.data;
    return (c >= 97 && c <= 122) ? TRUE : FALSE;
}

void print(struct f_elem* list) {
    if (!list) {
        printf("\n");
    } else {
        printf("%d ", *(int*)list -> info -> data);
        print(list -> next);
    }
}

int main() {
    struct f_list* list = f_list_init(&gt50);
    int *info = (int*)malloc(sizeof(int)), *info2 = (int*)malloc(sizeof(int));
    *info = 10;
    struct my_data data; data.data = info;
    printf("Trying to insert 10: %d\n", f_list_insert(list, data));
    *info = 30; printf("Trying to insert 30: %d\n", f_list_insert(list, data));
    *info = 50; printf("Trying to insert 50: %d\n", f_list_insert(list, data));
    *info = 70; printf("Trying to insert 70: %d\n", f_list_insert(list, data));
    data.data = info2;
    *info2 = 1000; printf("Trying to insert 1000: %d\n", f_list_insert(list, data));
    print(list -> head);
    
    struct f_list* list1 = f_list_init(&only_lowercase_chars);
    char *info3 = (char*)malloc(sizeof(char)), *info4 = (char*)malloc(sizeof(char));
    *info3 = 90; data.data = info3;
    printf("Trying to insert 90: %d\n", f_list_insert(list1, data));
    *info3 = 130; printf("Trying to insert 130: %d\n", f_list_insert(list1, data));
    *info3 = 'g'; printf("Trying to insert g: %d\n", f_list_insert(list1, data));
    data.data = info4;
    *info4 = 'z'; printf("Trying to insert z: %d\n", f_list_insert(list1, data));
    print(list1 -> head);
    return 0;
}