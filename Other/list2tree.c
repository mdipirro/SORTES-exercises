/**
 * 1) Implement a function which converts a list in a balanced tree
 * 2) Implement a function which converts a tree in a list
 */

#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int info;
    struct tnode *left, *right;
};

struct lnode {
    int info;
    struct lnode* next;
};

struct lnode* new_lnode(int info, struct lnode* next) {
    struct lnode* node = (struct lnode*) malloc(sizeof(struct lnode));
    node -> info = info;
    node -> next = next;
}

struct tnode* new_tnode(int info, struct tnode* left, struct tnode* right) {
    struct tnode* node = (struct tnode*) malloc(sizeof(struct tnode));
    node -> info = info;
    node -> left = left;
    node -> right = right;
}

int leaves(const struct tnode* const root) {
    if (!root) {
        return 0;
    }
    if (!root -> left) {
        return 1 + leaves(root -> right);
    } else if (!root -> right) {
        return 1 + leaves(root -> left);
    } else {
        return leaves(root -> left) + leaves(root -> right);
    }
}

struct lnode* tree2list(const struct tnode* const root) {
    if (!root) {
        return NULL;
    } 
    // Follow in-order
    struct lnode *list = new_lnode(root -> info, tree2list(root -> left));
    struct lnode *move = list;
    while(move -> next) {
        move = move -> next;
    }
    move -> next = tree2list(root -> right);
    return list;
}

void balanced_insert(struct tnode** root, int info) {
    if (!*root) {
        *root = new_tnode(info, NULL, NULL);
    } else {
        int l_leaves = leaves((*root) -> left), r_leaves = leaves((*root) -> right);
        if (l_leaves > r_leaves) {
            balanced_insert(&(*root) -> right, info);
        } else {
            balanced_insert(&(*root) -> left, info);
        }
    }
}

void list2tree_rec(const struct lnode* const list, struct tnode* root) {
    if (list) {
        balanced_insert(&root, list -> info);
        list2tree_rec(list -> next, root);
    }
}

struct tnode* list2tree(const struct lnode* const list) {
    if (!list) {
        return NULL;
    } 
    struct tnode* root = new_tnode(list -> info, NULL, NULL);
    list2tree_rec(list -> next, root);
    return root;
}

struct tnode* create_test_tree() {
    struct tnode    *leaf1 = new_tnode(10, NULL, NULL),
                    *leaf2 = new_tnode(20, NULL, NULL),
                    *leaf3 = new_tnode(30, NULL, NULL),
                    *leaf4 = new_tnode(40, NULL, NULL),
                    *inter1 = new_tnode(50, leaf1, leaf2),
                    *inter2 = new_tnode(60, leaf3, leaf4),
                    *root = new_tnode(70, inter1, inter2);
    return root;
}

struct lnode* create_test_list() {
    struct lnode    *node1 = new_lnode(10, NULL),
                    *node2 = new_lnode(20, node1),
                    *node3 = new_lnode(30, node2),
                    *node4 = new_lnode(40, node3),
                    *head = new_lnode(50, node4);
    return head;
}

void print_list(const struct lnode* const list) {
    if (!list) {
        printf("\n");
    } else {
        printf("%d ", list -> info);
        print_list(list -> next);
    }
}

void print_tree(const struct tnode* const root) {
    if (!root) {
        printf("_");
    } else {
        printf("%d (", root -> info);
        print_tree(root -> left);
        printf(", ");
        print_tree(root -> right);
        printf(")");
    }
}

int main() {
    const struct tnode* const root = create_test_tree();
    struct lnode* list_from_tree = tree2list(root);
    print_list(list_from_tree);
    const struct lnode* const list = create_test_list();
    struct tnode* tree_from_list = list2tree(list);
    print_list(list);
    print_tree(tree_from_list);
    printf("\n");
    return 0;
}