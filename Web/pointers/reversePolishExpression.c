/**
 * This exercise is taken from http://www.learntosolveit.com/cprogramming/Ex_5.10_exprcmd.html
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    double info;
    struct node* next;
};

struct node* new_node(double info, struct node* next) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node -> info = info;
    node -> next = next;
    return node;
}

void push(struct node** stack, double info) {
    if (!*stack) {
        *stack = new_node(info, NULL);
    } else {
        struct node* top = new_node(info, *stack);
        *stack = top;
    }
}

double pop(struct node** stack) {
    if (!stack) {
        exit(1);
    } else {
        double info = (*stack) -> info;
        struct node* node = *stack;
        *stack = (*stack) -> next;
        free(node);
        return info;
    }
}

double compute(double op1, double op2, char operator) {
    switch (operator) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 /op2;
    }      
}

double evaluate(const char* const expr) {
    struct node *operands = NULL;
    const char* p = expr;
    double number = 0, foundNumber = 0;
    while (*p) {
        switch (*p) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                foundNumber = 1;
                number = number * 10 + (*p - 48);
                break;
            case ' ':
                if (foundNumber) {
                    push(&operands, number);
                    foundNumber = 0;
                    number = 0;
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                push(&operands, compute(pop(&operands), pop(&operands), *p));
                break;
        }
        p++;
    }
    return pop(&operands);
}

int main() {
    printf("2 * (3 + 4) = %e\n", evaluate("2 3 4 + *"));
    printf("5 + (10 * 2) = %e\n", evaluate("5 10 2 * +"));
    printf("((10 * 2) + (4 - 5)) / 2 = %e\n", evaluate("10 2 * 4 5 - + 2 /"));
    printf("(7 / 3) / ((1 - 4) * 2) + 1 = %e\n", evaluate("7 3 / 1 4 - 2 * / 1 +"));
    return 0;
}