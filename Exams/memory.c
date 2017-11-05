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

void insert_respecting_address(struct node** list, struct node* chunk) {
    struct node* node = *list;
    if (node) {
        while (node -> begin < chunk -> begin) {
            node = node -> next;
        }
        chunk -> next = node;
        if (node -> prev) {
            node -> prev -> next = chunk;
        } else {
            *list = chunk;
        }
    }
}

void reduce_free_chunk(struct node* chunk, size_t size) {
    // TODO chunk == unallocated
    if (size == chunk -> size) { // exact fit
        if (chunk == unallocated) {
            unallocated = chunk -> next; // update unallocated's head
        } else {
            chunk -> prev -> next = chunk -> next; // extract the chunk
        }
        // insert the allocated chunk in the propoer list
        insert_respecting_addresses(&allocated, chunk); 
    } else {
        // manage the case without exact fit
    }
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