#include <stdio.h>
#include <stdlib.h>

struct node {
    size_t size;
    short is_allocated;
    struct node *prev, *next;
    void* begin;
};

static void *workarea;
static size_t spot = 1024;
static struct node* chunks;

void* my_malloc(size_t size) {
    if (size + sizeof(struct node) < spot) {
        short found = 0;
        while (chunks && !found) {
            if (!chunks -> is_allocated && chunks -> size >= size) { // found an eligible chunk
                found = 1;
                spot -= size;
                
            }
        }
    } else {
        exit(1); // size is bigger than the available spot
    }
}

int main() {
    workarea = malloc(1024);
    chunks = (struct node*) workarea;
    chunks -> size = spot - sizeof(struct node);
    chunks -> is_allocated = 0;
    chunks -> prev = chunks -> next = NULL;
    chunks -> begin = chunks + sizeof(struct node) - sizeof(void*);
    printf("%p\n", &chunks -> size);
    printf("%p\n", &chunks -> prev);
    printf("%p\n", &chunks -> next);
    printf("%p\n", chunks -> begin);
    return 0;
}