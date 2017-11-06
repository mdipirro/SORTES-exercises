#include <stdio.h>
#include <stdlib.h>

#define TOTAL_SIZE 1024

struct node {
    size_t size;
    struct node *prev, *next;
};

static void *workarea;
static int spot;
static struct node* unallocated;
static struct node* allocated;

void allocate_respecting_addresses(struct node* chunk) {
    struct node *node = allocated, *prev = NULL;
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
                allocated = chunk;
            }
            node -> prev = chunk;
        } else {
            prev -> next = chunk;
            chunk -> prev = prev;
        }
    } else { // empty list
        allocated = chunk; // new head
    }
}

int reduce_free_chunk(struct node* chunk, size_t size) {
    if (size == chunk -> size) { // exact fit
        if (spot - chunk -> size < 0) {
            return 1; // no more space
        }
        if (chunk == unallocated) {
            unallocated = chunk -> next; // update unallocated's head
        } else {
            chunk -> prev -> next = chunk -> next; // extract the chunk
        }
        // insert the allocated chunk in the proper list
        allocate_respecting_addresses(chunk); 
    } else {
        if (spot - chunk -> size - sizeof(struct node) < 0) {
            return 1; // no more space
        }
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
        allocate_respecting_addresses(chunk); 
    }
    return 0;
}

void* my_malloc(size_t size) {
    short found = 0, status = 1;
    struct node* chunk = unallocated;
    while (chunk && !found) {
        found = chunk -> size >= size; // found an eligible chunk
        if (!found) {
            chunk = chunk -> next;
        }
    }
    if (found) {
        status = reduce_free_chunk(chunk, size);
    }
    return (chunk && !status) ? chunk + sizeof(struct node) : NULL;
}

void free_respecting_addresses(struct node* chunk) {
    struct node *node = unallocated, *prev = NULL;
    short left_merged = 0;
    if (node) {
        while (node && node < chunk) {
            prev = node;
            node = node -> next;
        }
        if (node) {
            chunk -> prev = node -> prev; // link the prev
            
            // check for mergeability
            if (chunk + sizeof(struct node) + chunk -> size == node) { 
                spot += sizeof(struct node);
                // chunk and node next to each other
                chunk -> size += node -> size + sizeof(struct node);
                chunk -> next = node -> next;
                if (node -> next) { // successor in the list
                    node -> next -> prev = chunk;
                }
            } else if (prev + sizeof(struct node) + prev -> size == chunk) {
                spot += sizeof(struct node);
                // chunk and prev next to each other
                prev -> size += chunk -> size + sizeof(struct node);
                left_merged = 1;
            } else { // chunk and node not mergeable
                chunk -> next = node;
                node -> prev = chunk;
            }

            if (!left_merged) {
                // manage the prev
                if (prev) { // insert chunk
                    prev -> next = chunk;
                } else { // update head
                    unallocated = chunk;
                }
            }
        } else {
            if (prev + sizeof(struct node) + prev -> size == chunk) {
                // chunk and prev next to each other
                prev -> size += chunk -> size + sizeof(struct node);
            } else {
                prev -> next = chunk;
                chunk -> prev = prev;
            }
        }
    } else { // empty list
        unallocated = chunk; // new head
        chunk -> prev = NULL;
        chunk -> next = NULL;
    }
}

int find_free_chunk(struct node* chunk) {
    if (!unallocated) {
        return 0;
    }
    struct node* node = unallocated;
    short found = 0;
    while (node && !found) {
        found = node == chunk;
        node = node -> next;
    }
    return found;
}

void free(void* ptr) {
    struct node* chunk = ((struct node*)ptr - sizeof(struct node)); // get the corresponding chunk
    if (find_free_chunk(chunk)) {
        spot += chunk -> size;
        // extract chunk from allocated list
        if (!chunk -> prev) {
            allocated = chunk -> next; // update allocated's head
        } else {
            chunk -> prev -> next = chunk -> next; // link prev with next
        }
        if (chunk -> next) {
            chunk -> next -> prev = chunk -> prev; // link next with prev
        } // otherwise do nothing
        free_respecting_addresses(chunk);
    }    
}

int main() {
    workarea = malloc(1024);
    spot = TOTAL_SIZE;
    unallocated = (struct node*) workarea;
    unallocated -> size = spot - sizeof(struct node);
    unallocated -> prev = unallocated -> next = NULL;
    allocated = NULL;

    printf("BEGINNING:\n");
    printf("workarea = %p\tunallocated = %p\tallocated = %p\n", workarea, unallocated, allocated);
    
    printf("\nAllocate 100 bytes:\n"); int* p = my_malloc(100); *p = 10;
    printf("User pointer should be %p: %p\n", allocated + sizeof(struct node), p);
    printf("User provided value should be 10: %d\n", *p);
    printf("Allocated size should be 100: %ld\n", ((struct node*)p - sizeof(struct node)) -> size);
    printf("workarea = %p\tunallocated = %p\tallocated = %p\n", workarea, unallocated, allocated);

    printf("\nAllocate 1200 bytes:\n");
    printf("User pointer should be NIL: %p\n", my_malloc(1200));

    printf("\nAllocate 50 bytes:\n"); char* q = my_malloc(50); *q = 'A';
    printf("User pointer should be %p: %p\n", 
        allocated + sizeof(struct node) * 2 + 100, q);
    printf("User provided value should be A: %c\n", *(char*)(allocated -> next + 24));
    printf("Allocated size should be 50: %ld\n", ((struct node*)q - sizeof(struct node)) -> size);
    printf("workarea = %p\tunallocated = %p\tallocated = %p\n", workarea, unallocated, allocated);

    free(q);
    printf("\nFree q:\n");
    printf("allocated -> next should be NIL: %p\n", allocated -> next);
    printf("unallocated -> next should be NIL: %p\n", unallocated -> next);
    printf("unallocated should be %p: %p\n", (struct node*)q - sizeof(struct node), unallocated);
    printf("Chunk's size should be %ld: %ld\n", 
        TOTAL_SIZE - sizeof(struct node) * 2 - allocated -> size, unallocated -> size
    );

    return 0;
}