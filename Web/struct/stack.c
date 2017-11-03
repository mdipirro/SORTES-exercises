#include <stdlib.h>
#include <stdio.h>

struct stack_record {
    int info;
    struct stack_record* next;
};

int get_element_by_filter(const struct stack_record* const stack, int (*cmp_function)(int, int))  {
    int result = stack -> info;
    const struct stack_record* x = stack -> next;
    while (x) {
        if ((*cmp_function)(x -> info, result)) {
            result = x -> info;
        }
        x = x -> next;
    }
    return result;
}

int gt(int a, int b) {
    return a > b;
}

int lt(int a, int b) {
    return a < b;
}

/**
 * Add an element at the top of the stack.
 * @param stack A pointer to the memeory location containing a pointer to the first element
 * of the stack
 * @param element The element to be added
 */
void push(struct stack_record** stack, int element) {
    struct stack_record* new_head = (struct stack_record*) malloc(sizeof(struct stack_record));
    new_head -> info = element;
    if (!(*stack)) {
        new_head -> next = NULL;
    } else {
        new_head -> next = *stack;
    }
    *stack = new_head;
}

/**
 * Pop the first element of the stack. Throw an exception if the stack is empty.
 * @param stack A pointer to the memeory location containing a pointer to the first element
 * of the stack
 * @return The popped element
 */ 
int pop(struct stack_record** stack) {
    int element = (*stack) -> info;
    struct stack_record* to_be_popped = *stack;
    *stack = (*stack) -> next;
    free(to_be_popped);
    return element;
}

/** Compute the size of a stack.
 * @param stack A pointer to the top of the stack
 * @return Stack's size
 */ 
int size(const struct stack_record* const stack) {
    if (!stack) {
        return 0;
    }
    return 1 + size(stack -> next);
}

/**
 * Return a pointer to the minimum element of the stack.
 * @param stack A pointer to the top of the stack
 * @return A pointer to the minimum element of the stack
 */ 
int min(const struct stack_record* const stack) {
    return get_element_by_filter(stack, &lt);
}

/**
 * Return a pointer to the maximum element of the stack.
 * @param stack A pointer to the top of the stack
 * @return A pointer to the maximum element of the stack
 */ 
int max(const struct stack_record* const stack) {
    return get_element_by_filter(stack, &gt);
}

/**
 * Return 1 iff `element` is contained in `stack`
 * @param stack A pointer to the top of the stack
 * @param element The element to be found
 * @return 1 iff `element` is contained in `stack`, 0 otherwise
 */ 
int find(const struct stack_record* const stack, int element) {
    const struct stack_record* x = stack;
    int found = 0;
    while (x && !found) {
        found = (x -> info == element);
        x = x -> next;
    }
    return found;
}

/**
 * Print the stack
 * @param stack A pointer to the top of the stack
 */
void print(const struct stack_record* const stack) {
    if (!stack) {
        printf("\n");
    } else {
        printf("%d ", stack -> info);
        print(stack -> next);
    }
}

int main() {
    struct stack_record* stack = NULL;
    printf("Stack's size (should be 0): %d\n", size(stack));
    push(&stack, 5); push(&stack, 7); push(&stack, 10);
    printf("Stack's size (should be 3): %d\n", size(stack));
    print(stack); // 10 7 5
    printf("Minimum element (should be 5): %d\n", min(stack));
    printf("Maximum element (should be 10): %d\n", max(stack));
    printf("7's depth (should be 1): %d\n", find(stack, 7));
    pop(&stack); pop(&stack);
    print(stack); // 5
    pop(&stack);
    printf("Stack's size (should be 0): %d\n", size(stack));
    printf("Stack's top (should be nil): %p\n", stack);
    return 0;
}