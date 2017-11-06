#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node* children;
    int children_number;
};

struct node* new_node(int info) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node -> info = info;
    node -> children = (struct node*) malloc(sizeof(struct node[10]));
    node -> children_number = 0;
}

void add_child (struct node* parent, struct node* child) {
    parent -> children[parent -> children_number++] = *child;
}

struct node* get_child_by_info(struct node* root, int info) {
    struct node* result = NULL;
    for (int i = 0; root && i < root -> children_number && !result; i++) {
        if (root -> children[i].info % 10 == info) {
            result = &root -> children[i];
        }
    }
    return result;
}

int insert(struct node** root, int info) {
    if (!*root && !info) {
        *root = new_node(info);
        return 0;
    }
    if (!*root && info) {
        return -1; // no root and value != 0
    }

    // get every digit of the number
    int digits = 0, n = info;
    do {
        digits++;
    } while (n /= 10);
    char number[digits]; n = info;
    for (int i = digits - 1; i >= 0; i--) {
        number[i] = n % 10;
        n /= 10;
    }

    struct node *node = *root, *prev = NULL;
    int d = 0;
    while (node && d < digits) {
        prev = node;
        node = get_child_by_info(node, number[d]);
        d++;
    }
    printf("%d ", d);
    if (d + 1 <= digits) { // missing nodes
        return -1;
    }

    if (node) { // found a node with the same info
        return -1;
    }
    
    add_child(prev, new_node(info));
    return 0;
}

int main() {
    struct node* root = NULL;
    printf("Adding 5: %d\n", insert(&root, 5));
    printf("Adding 0 %d\n", insert(&root, 0));
    printf("Adding 5: %d\n", insert(&root, 5));
    printf("Adding 1: %d\n", insert(&root, 1));
    printf("Adding 2: %d\n", insert(&root, 2));
    printf("Adding 12: %d\n", insert(&root, 12));
    printf("Adding 16: %d\n", insert(&root, 16));
    printf("Adding 13: %d\n", insert(&root, 13));
    printf("Adding 135: %d\n", insert(&root, 135));
    printf("Adding 243: %d\n", insert(&root, 243));
    printf("Adding 599: %d\n", insert(&root, 599));
    printf("Adding 16: %d\n", insert(&root, 16));
}