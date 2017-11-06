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

/**
 * Add a new chunk in the `allocated` list. The insertion respects
 * the address ordering.
 * @param chunk The chunk to insert
 */ 
void allocate_respecting_addresses(struct node* chunk) {
    struct node *node = allocated, *prev = NULL;
    if (node) {
        while (node && node < chunk) { // look for the chunk immediately after the parameter
            prev = node;
            node = node -> next;
        }
        if (node) { // chunk has to be inserted before the end
            chunk -> next = node;
            chunk -> prev = node -> prev;
            if (node -> prev) { // insert chunk
                node -> prev -> next = chunk;
            } else { // update head
                allocated = chunk;
            }
            node -> prev = chunk;
        } else { // chunk has to be inserted at the end
            prev -> next = chunk;
            chunk -> prev = prev;
        }
    } else { // empty list
        allocated = chunk; // new head
    }
}

/**
 * Take an eligible free chunk and make it busy according to the
 * memory request (meaning the entire chunk can be made busy or 
 * only a part of that).
 * @param chunk The chunk to be made busy
 * @param size The requested memory for allocation
 * @return 0 If everything went good, 1 otherwise
 */ 
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

/**
 * Allocate size bytes.
 * @param size The memory to allocate.
 * @return A pointer to the allocated memory
 */ 
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

/**
 * Insert a chunk in `unallocated` respecting the address ordering.
 * Merge if necessary.
 * @param chunk The chunk to be inserted in unallocated
 */ 
void free_respecting_addresses(struct node* chunk) {
    struct node *node = unallocated, *prev = NULL;
    short left_merged = 0, right_merged = 0;
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
                right_merged = 1;
            } 
            if (prev && prev + sizeof(struct node) + prev -> size == chunk) {
                spot += sizeof(struct node);
                // chunk and prev next to each other
                prev -> size += chunk -> size + sizeof(struct node);
                prev -> next = NULL;
                chunk -> next = NULL;
                chunk -> prev = NULL;
                left_merged = 1;
            } 

            if (!left_merged && !right_merged) { // chunk and node not mergeable
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
                chunk -> next = NULL;
                chunk -> prev = NULL;
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

/**
 * Find a busy chunk in the allocated list.
 * @param A pointer to the chunk to be found.
 * @return 0 if chunk not found, 1 otherwise
 */ 
int find_busy_chunk(struct node* chunk) {
    if (!unallocated) {
        return 0;
    }
    struct node* node = allocated;
    short found = 0;
    while (node && !found) {
        found = node == chunk;
        node = node -> next;
    }
    return found;
}

/**
 * Free a memory area allocated with my_malloc
 * @param ptr A pointer to the memory area to free
 */ 
void my_free(void* ptr) {
    struct node* chunk = ((struct node*)ptr - sizeof(struct node)); // get the corresponding chunk
    if (find_busy_chunk(chunk)) {
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

    printf("\nAllocate 75 bytes:\n"); double* s = my_malloc(75); *s = 3.1;
    printf("User pointer should be %p: %p\n", 
        allocated + sizeof(struct node) * 3 + 100 + 50, s);
    printf("User provided value should be 3.1: %e\n", *(double*)(allocated -> next -> next + 24));
    printf("Allocated size should be 75: %ld\n", ((struct node*)s - sizeof(struct node)) -> size);
    printf("workarea = %p\tunallocated = %p\tallocated = %p\n", workarea, unallocated, allocated);

    struct node* tmp = unallocated;
    my_free(q);
    printf("\nFree q:\n");
    printf("allocated -> next should be %p: %p\n", ((struct node*)s - sizeof(struct node)), allocated -> next);
    printf("unallocated -> next should be %p: %p\n", tmp, unallocated -> next);
    printf("unallocated should be %p: %p\n", (struct node*)q - sizeof(struct node), unallocated);
    printf("Chunk's size should be 50: %ld\n", unallocated -> size);

    my_free(s);
    printf("\nFree s:\n");
    printf("allocated -> next should be NIL: %p\n", allocated -> next);
    printf("unallocated -> next should be NIL: %p\n", unallocated -> next);
    printf("unallocated should be %p: %p\n", (struct node*)q - sizeof(struct node), unallocated);
    printf("Chunk's size should be %ld: %ld\n", 
        TOTAL_SIZE - sizeof(struct node) * 2 - allocated -> size, unallocated -> size
    );

    return 0;
}