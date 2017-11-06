#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 1

enum bool {FALSE, TRUE};
static int time = 0;

struct structA {
    int a;
    char b;
    enum bool (*fun)(int time);
};

struct structB {
    struct structB* next;
    struct structA a;
    int resolution_time;
};

struct function {
    void *address;
    char *name;
};

enum bool fun1(int time) {
    return time;
}

struct function table[TABLE_SIZE] = {&fun1, "fun1"};

void mydebug(struct structA* a, struct structB** b) {
    //hrtime_t time = gethrtime();
    if (a) {
        if ((*(a -> fun))(time++)) {
            struct structB *head = (struct structB*) malloc(sizeof(struct structB));
            head -> resolution_time = time;
            head -> next = *b;
            head -> a = *a;
            *b = head;
        }
    }
}

void myprint(struct structB** list) {
    struct structB* x = NULL;
    if (list) {
        struct structB* node = *list;
        while (node) {
            int found = 0;
            int i = 0;
            while (i < TABLE_SIZE && !found) {
                found = table[i].address == node -> a.fun;
                i++;
            }
            printf("Integer: %d\tChar: %c\tFunction name: %s\n", node -> a.a, node -> a.b, table[i - 1].name);
            x = node;
            node = node -> next;
            free(x);
        }
    }
}

int main() {
    struct structA a;
    a.a = 10; a.b = 'A'; a.fun = &fun1;
    struct structB *b = NULL;
    mydebug(&a, &b);
    mydebug(&a, &b);
    mydebug(&a, &b);
    myprint(&b);
}