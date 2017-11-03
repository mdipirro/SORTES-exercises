#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

void print(const int* const);
void sort_asc(int* const);
void sort_desc(int* const);

/**
 * Sort in-place an array using the ascending order.
 * @param array A pointer to an array of 10 elements.
 */
void sort_asc(int* const array) {
    for (int i = 0; i < LENGTH; i++) {
        for (int j = i + 1; j < LENGTH; j++ ){
            if (array[i] > array[j]) {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
}

/**
 * Sort in-place an array using the descending order.
 * @param array A pointer to an array of 10 elements.
 */ 
void sort_desc(int* const array) {
    for (int i = 0; i < LENGTH; i++) {
        for (int j = i + 1; j < LENGTH; j++ ){
            if (array[i] < array[j]) {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
}

/**
 * Print the element of the array in normal order. 
 * @param array A pointer to an array with 10 elements.
 */ 
void print(const int* const array) {
    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", array[i]);
    }
}

int main() {
    int array[LENGTH];
    for (int i = 0; i < LENGTH; i++) {
        printf("\nEnter the element number %d: ", i + 1);
        scanf("%d", &array[i]);
    }
    sort_asc(array);
    printf("Array sorted in ascending order: ");
    print(array);
    printf("\nArray sorted in descending order: ");
    sort_desc(array);
    print(array);
    printf("\n");
    return 0;
}