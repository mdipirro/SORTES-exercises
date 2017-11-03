#include <stdio.h>
#include <stdlib.h>

#define LENGTH 5

/**
 * This program implements the exercise "Printing values" in "generalExercisesAboutPointers.md".
 */ 

void print(const int* const);
void print_reverse(const int* const);

/**
 * Print the element of the array in normal order. 
 * This function implements the first part of the exercise.
 * @param array A pointer to an array with 5 elements.
 */ 
void print(const int* const array) {
    printf("\nArray values in normal order: ");
    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", array[i]);
    }
}

/**
 * Print the element of the array in reverse order. 
 * This function implements the second part of the exercise.
 * @param array A pointer to an array with 5 elements.
 */
void print_reverse(const int* const array) {
    printf("\nArray values in reverse order: ");
    for (int i = LENGTH - 1; i >= 0; i--) {
        printf("%d ", array[i]);
    }
}

int main() {
    int array[LENGTH];
    for (int i = 0; i < LENGTH; i++) {
        printf("\nEnter the element number %d: ", i + 1);
        scanf("%d", &array[i]);
    }
    print(array);
    print_reverse(array);
    printf("\n");
    return 0;
}