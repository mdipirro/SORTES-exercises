#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int serial_number;
    struct tnode *children;
    int children_number;
};

struct lnode* new_lnode(int serial, struct lnode* next) {
    struct lnode* node = (struct lnode*) malloc(sizeof(struct lnode));
    node -> serial_number = serial;
    node -> next = next;
}

struct tnode* new_tnode(int serial) {
    struct tnode* node = (struct tnode*) malloc(sizeof(struct tnode));
    node -> serial_number = serial;
    node -> children = (struct tnode*) malloc(sizeof(struct tnode[10]));
    node -> children_number = 0;
}

struct tnode* get_child_by_number(struct tnode* node, int number) {
    struct tnode* result = NULL;
    int i = 0;
    while (!result && i < node -> children_number) {
        if (node -> children[i].serial_number % 10 == number) {
            result = &node -> children[i];
        }
        i++;
    }
    return result;
}

void add_child(struct tnode* node, struct tnode* child) {
    node -> children[node -> children_number++] = *child;
}

void int2string(int number, char* string, int length) {
    for (int i = length -1; i >= 0; i--) {
        string[i] = number % 10;
        number /= 10;
    }
}

// PRE 0 has already been added -> root points to a valid node
int insert(struct tnode* root, int value) {
    struct tnode* prev = NULL;
    int d = 0, copy = value, i = 0, status = 2; // 2 means scanning;

    do {d++;}while(copy /= 10);
    char digits[d];
    int2string(value, digits, d);

    while (status == 2 && i < d) {
        prev = root;
        root = get_child_by_number(root, digits[i]);
        //printf("%d ", )
        // check the new pointer
        if (!root) {
            if (i + 2 < d) { // +2 because: +1 -> i starts from 0; +1 -> one digit to add
                status = -1; // more levels are needed
            } else {
                status = 0;
                add_child(prev, new_tnode(value));
            }
        }
        i++;
    }
    return (status != 2) ? status : -2;
}

int main() {
    struct tnode* root = new_tnode(0);
    printf("Adding 5: %d\n", insert(root, 5));
    printf("Adding 1: %d\n", insert(root, 1));
    printf("Adding 2: %d\n", insert(root, 2));
    printf("Adding 12: %d\n", insert(root, 12));
    printf("Adding 16: %d\n", insert(root, 16));
    printf("Adding 13: %d\n", insert(root, 13));
    printf("Adding 135: %d\n", insert(root, 135));
    printf("Adding 243: %d\n", insert(root, 243));
    printf("Adding 16: %d\n", insert(root, 16));
}