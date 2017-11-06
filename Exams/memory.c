#include <stdio.h>
#include <stdlib.h>

#define TOTAL_SIZE 1024

struct node {
    size_t size;
    struct node *prev, *next;
};

static void *workarea;
static struct node* unallocated;
static struct node* allocated;

void insert_respecting_addresses(struct node** list, struct node* chunk) {
    struct node *node = *list, *prev = NULL;
    if (node) {
        while (node && node < chunk) {
            prev = node;
            node = node -> next;
        }
        if (node) {
            chunk -> next = node;
            chunk -> prev = node -> prev;
            if (node -> prev) { // insert chunk
                node -> prev -> next = chunk;
            } else { // update head
                *list = chunk;
            }
            node -> prev = chunk;
        } else {
            prev -> next = chunk;
            chunk -> prev = prev;
        }
    } else { // empty list
        *list = chunk; // new head
    }
}

void reduce_free_chunk(struct node* chunk, size_t size) {
    if (size == chunk -> size) { // exact fit
        if (chunk == unallocated) {
            unallocated = chunk -> next; // update unallocated's head
        } else {
            chunk -> prev -> next = chunk -> next; // extract the chunk
        }
        // insert the allocated chunk in the proper list
        insert_respecting_addresses(&allocated, chunk); 
    } else {
        // begin of the next free chunk
        struct node* free = (struct node*) chunk + sizeof(struct node) + size;
        // update the new size subtracting the new metadata's size
        free -> size = chunk -> size - size - sizeof(struct node);
        // link the new free chunk with the unallocated list
        free -> prev = chunk -> prev;
        free -> next = chunk -> next;
        if (chunk -> prev) {
            chunk -> prev -> next = free;
        } else {
            unallocated = free;
        }
        if (chunk -> next) {
            chunk -> next -> prev = free;
        }
        // reduce chunk's size and manage its pointers
        chunk -> size = size;
        insert_respecting_addresses(&allocated, chunk); 
    }
}

void* my_malloc(size_t size) {
    short found = 0;
    struct node* chunk = unallocated;
    while (chunk && !found) {
        found = chunk -> size >= size; // found an eligible chunk
        if (!found) {
            chunk = chunk -> next;
        }
    }
    if (found) {
        reduce_free_chunk(chunk, size);
    }
    return (chunk) ? chunk + sizeof(struct node) : NULL;
}

void free(void* ptr) {
    //spot 
}

int main() {
    workarea = malloc(1024);
    unallocated = (struct node*) workarea;
    unallocated -> size = TOTAL_SIZE - sizeof(struct node);
    unallocated -> prev = unallocated -> next = NULL;
    allocated = NULL;

    printf("BEGINNING:\n");
    printf("workarea = %p\tunallocated = %p\tallocated = %p\n", workarea, unallocated, allocated);
    
    printf("\nAllocate 100 bytes:\n"); int* p = my_malloc(100); *p = 10;
    printf("User pointer should be %p: %p\n", allocated + sizeof(struct node), p);
    printf("User provided value should be 10: %d\n", *p);
    printf("workarea = %p\tunallocated = %p\tallocated = %p\n", workarea, unallocated, allocated);

    printf("\nAllocate 1200 bytes:\n");
    printf("User pointer should be NIL: %p\n", my_malloc(1200));

    printf("\nAllocate 50 bytes:\n"); char* q = my_malloc(50); *q = 'A';
    printf("User pointer should be %p: %p\n", 
        allocated + sizeof(struct node) * 2 + 100, q);
    printf("User provided value should be A: %c\n", *q);
    printf("workarea = %p\tunallocated = %p\tallocated = %p\n", workarea, unallocated, allocated);



    /*printf("%p\n", &unallocated -> size);
    printf("%p\n", &unallocated -> prev);
    printf("%p\n", &unallocated -> next);
    //printf("%p\n", unallocated -> begin);*/
    return 0;
}