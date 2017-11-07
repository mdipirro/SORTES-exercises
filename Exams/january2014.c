#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node* next;
    long integers[2];
    char* string;
};

int list_length(const struct node* list) {
    int l = 0;
    while (list) {
        list = list -> next;
        l++;
    }
    return l;
}

int string_length(const char* string) {
    int l = 0;
    while (*string) {
        string++;
        l++;
    }
    return l;
}

int copy(struct node** source, void** dest) {
    if (!source || !*source || !dest) {
        return -1;
    }
    *dest = malloc(sizeof(struct node) * list_length(*source));
    struct node *node = *source, *serial = (struct node*) *dest, *prev = NULL;
    while (node) {
        // copy the integers table
        serial -> integers[0] = node -> integers[0];
        serial -> integers[1] = node -> integers[1];
        // copy the string
        serial -> string = (char*) malloc(sizeof(char) * string_length(node -> string));
        char *s1 = node -> string, *s2 = serial -> string;
        while(*s1) {
            *s2++ = *s1++;
        }
        // update prev's next
        if (prev) {
            prev -> next = serial;
        }
        prev = serial;
        serial += sizeof(struct node);
        node = node -> next;
    }
    prev -> next = NULL;
    return 0;
}

int myserial(char todo, struct node** called_list, void** called_serial) {
    if (todo != 's' && todo != 'd') {
        return -1;
    }
    return (todo == 's') ? copy(called_list, called_serial) : copy((struct node**) called_serial, (void**) called_list);
}

int main() {
    char *s1 = "Hello", *s2 = "World";
    int a = 5, b = 10, c = 11;
    struct node *node1 = (struct node*) malloc(sizeof(struct node)),
                *node2 = (struct node*) malloc(sizeof(struct node));
    node1 -> integers[0] = a; node1 -> integers[1] = b;
    node1 -> string = s1; node1 -> next = node2;
    node2 -> integers[0] = c; node2 -> integers[1] = a;
    node2 -> string = s2; node2 -> next = NULL;
    void *serial = NULL; struct node *x = node1;
    while (x) {
        printf("%ld %ld %s -> ", x -> integers[0], x -> integers[1], x -> string);
        x = x -> next;
    }
    printf("NULL\n");
    myserial('s', &node1, &serial);
    x = serial;
    while (x) {
        printf("%ld %ld %s -> ", x -> integers[0], x -> integers[1], x -> string);
        x = x -> next;
    }
    printf("NULL\n");
    struct node *deserial = NULL;
    myserial('d', &deserial, &serial);
    x = deserial;
    while (x) {
        printf("%ld %ld %s -> ", x -> integers[0], x -> integers[1], x -> string);
        x = x -> next;
    }
    printf("NULL\n");
    return 0;
}