/**
 * Implement an int bynary search tree struct with the following operations:
 * - constructor for a root with an info attached
 * - insert
 * - find (both returning a bool or a pointer to the element)
 * - print in in-order
 * - completely deallocate the memory occupied by the tree
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *left, *right;
};

struct node* init(int info) {
    struct node* root = (struct node*) malloc(sizeof(struct node));
    root -> info = info;
    root -> left = NULL;
    root -> right = NULL;
    return root;
}

void insert(struct node* const root, int info) {
    if (root) {
        if (root -> info != info) {
            if (root -> info > info) {
                if (!root -> left) {
                    struct node* node = init(info);
                    root -> left = node;
                } else {
                    insert(root -> left, info);
                }
            } else {
                if (!root -> right) {
                    struct node* node = init(info);
                    root -> right = node;
                } else {
                    insert(root -> right, info);
                }
            }
        }
    }
}

const struct node* const get_pointer_to_element(const struct node* const root, int element) {
    if (!root) {
        return 0;
    }
    if (root -> info == element) {
        return root;
    }
    
    if (root -> info > element) {
        get_pointer_to_element(root -> left, element);
    } else {
        get_pointer_to_element(root -> right, element);
    }
}

int find(const struct node* const root, int element) {
    return !!get_pointer_to_element(root, element);
}

void rec_free(struct node* const root) {
    if (root) {
        rec_free(root -> left);
        rec_free(root -> right);
        free(root);
    }
}

void deallocate(struct node** const root) {
    rec_free(*root);
    *root = NULL;
}

void print(const struct node* const root) {
    if (!root) {
        printf("_");
    } else {
        printf("%d (", root -> info);
        print(root -> left);
        printf(", ");
        print(root -> right);
        printf(")");
    }
}

int main() {
    struct node* root = init(10);
    printf("Non-empty root: %d\n", root -> info);
    insert(root, 15); insert(root, 5); insert(root, 20); insert(root, 12);
    printf("Should insert 15 to the right: %d\n", root -> right -> info);
    printf("Should insert 5 to the left: %d\n", root -> left -> info);
    printf("Should insert 20 to the right of 15: %d\n", root -> right -> right -> info);
    printf("Should insert 12 to the left of 15: %d\n", root -> right -> left -> info);
    printf("Should not contain 13: %d\n", find(root, 13));
    printf("Should not contain 13: %p\n", get_pointer_to_element(root, 13));
    printf("Should contain 12: %d\n", find(root, 12));
    printf("Should contain 12: %d\n", get_pointer_to_element(root, 12) -> info);
    print(root); printf("\n");
    deallocate(&root);
    printf("root should be nil: %p\n", root);
    return 0;
}