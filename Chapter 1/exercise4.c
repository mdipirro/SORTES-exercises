#include <stdio.h>
#include <stdlib.h>
#define ARSIZE 10

int populateArray(int*);
void sortArray(int*, int);

/**
 * Read maximum ARSIZE characters from standard input and put then into
 * an array given as a parameter. 
 * @param array The array 
 * @return Array's length
 */
int populateArray(int* array) {
	char ch = getchar();
	int i = 0;
	while (ch != '\n' && i < ARSIZE) {
		array[i++] = ch - 48;
		ch = getchar();
	}
	return i;
}

/**
 * Sort an array with a gien actual length
 * @param array The array
 * @param length The array's length
 */ 
void sortArray(int* array, int length) {
	int k1 = 0;
	while(k1 < length){
		int k2 = k1 + 1;
		while(k2 <= length){
			if(array[k1] > array[k2]){
				int temp = array[k1];
				array[k1] = array[k2];
				array[k2] = temp;
			}
			k2++;
		}
		k1++;
	}
}

int main() {
	int array[ARSIZE];
	int length = populateArray(array);
	sortArray(array,length);
	printf("The sorted array is as follows: [ ");
	for (int i = 0; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("]");
	return 0;
}
