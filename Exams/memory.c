#include <stdio.h>
#include <stdlib.h>

struct node {
    size_t size;
    struct node *prev, *next;
    void* begin;
};

static void *workarea;
static size_t spot = 1024;
static struct node* unallocated;
static struct node* allocated;

void reduce_free_chunk(struct node* chunk, size_t size) {
    // remember to update allocated if the chunk is the first
}

void* my_malloc(size_t size) {
    if (size + sizeof(struct node) < spot) {
        short found = 0;
        struct chunk = unallocated;
        while (chunk && !found) {
            if (!chunk -> is_allocated && chunk -> size >= size) { // found an eligible chunk
                found = 1;
                spot -= size;
                reduce_free_chunk(chunk, size);
            }
            chunk = chunk -> next;
        }
    } else {
        exit(1); // size is bigger than the available spot
    }
}

int main() {
    workarea = malloc(1024);
    unallocated = (struct node*) workarea;
    unallocated -> size = spot - sizeof(struct node);
    unallocated -> prev = unallocated -> next = NULL;
    unallocated -> begin = unallocated + sizeof(struct node) - sizeof(void*);
    printf("%p\n", &unallocated -> size);
    printf("%p\n", &unallocated -> prev);
    printf("%p\n", &unallocated -> next);
    printf("%p\n", unallocated -> begin);
    return 0;
}