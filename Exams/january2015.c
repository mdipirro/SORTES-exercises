#include <stdio.h>
#include <stdlib.h>

#define MAXBUFFCALLS 10

enum bool {FALSE, TRUE};

struct counter {
    int calls;
    struct counter *next;
};

struct mybuf {
    // Some kind of info here
    enum bool free;
    struct counter* counter;
    struct mybuf *next, *prev;
};

struct counter* counters = NULL;

void new_head(struct mybuf **buffers) {
    // create a new counter
    struct counter *counter = (struct counter*) malloc(sizeof(struct counter));
    counter -> calls = 0;
    counter -> next = counters;

    // create a new buffer
    struct mybuf *buffer = (struct mybuf*) malloc(sizeof(struct mybuf));
    buffer -> counter = counter;
    buffer -> free = TRUE;
    buffer -> next = *buffers;
    buffer -> prev = NULL;

    counters = counter; // set a new head for counters list
    if (*buffers) {
        (*buffers) -> prev = buffer;
    }
    *buffers = buffer; // set a new head for buffers list
}

void manage_buf(struct mybuf** buffers) {
    if (*buffers) {
        struct mybuf *freebuf = NULL;
        struct mybuf *node = *buffers;
        while (node) {
            if (++node -> counter -> calls == MAXBUFFCALLS) {
                // free the buffer
                node -> free = TRUE;
                node -> counter -> calls = 0;
                if (!freebuf) {
                    freebuf = node;
                }
            } else if (node -> free && !freebuf) {
                freebuf = node;
            }
            node = node -> next;
        }

        if (freebuf) {
            if (freebuf != *buffers) {
                if (freebuf -> prev) {
                    freebuf -> prev -> next = freebuf -> next;
                }
                if (freebuf -> next) {
                    freebuf -> next -> prev = freebuf -> prev;
                }
                freebuf -> prev = NULL;
                freebuf -> next = *buffers;
                *buffers = freebuf;
            }
        } else {
            new_head(buffers);
        }
    } else {
        new_head(buffers);
    }
}

int main() {
    struct mybuf* buffers = NULL;
    manage_buf(&buffers);
    printf("First buffer: %p\n", buffers);
    buffers -> free = FALSE;
    manage_buf(&buffers);
    printf("Second buffer: %p %p\n", buffers, buffers -> next);
    return 0;
}