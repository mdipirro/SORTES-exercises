#include <stdio.h>
#include <stdlib.h>

/**
 * This program implements the exercise "Finding max" in "generalExercisesAboutPointers.md".
 */ 

const int* const find_max(const int* const, int);

/**
 * Find the maximum element of an array of int. `length` can be any integral value. 
 * If `length` <= 0, the function return a null pointer. Otherwise it returns a pointer
 * to the maximum element of the array.
 * @param array A pointer to an array of int.
 * @length `array`'s length
 * @return A pointer to the maximum element of the array.
 */ 
const int* const find_max(const int* const array, int length) {
    if (length <= 0) {
        return NULL;
    }
    const int* max = array;
    for (int i = 1; i < length; i++) {
        if (array[i] > *max) {
            max = (array + sizeof(int) * i);
        }
    }
    return max;
}

int main() {
    int length = 0;
    printf("Enter the number of data values: ");
    scanf("%d", &length);
    int array[length];
    for (int i = 0; i < length; i++) {
        printf("\nEnter the element number %d: ", i + 1);
        scanf("%d", &array[i]);
    }
    printf("\nThe maximum element is: %d\n", *find_max(array, length));
    return 0;
}