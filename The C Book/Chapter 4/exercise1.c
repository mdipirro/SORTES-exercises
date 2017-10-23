#include <stdio.h>

int abs_val(int);

/**
 * Return the absolute value of a given number.
 * @param number The number
 * @return |number|
 */ 
int abs_val(int number) {
	return (number < 0) ? -number : number;
}

int main() {
	int test1 = -5, test2 = 5, test3 = 0;
	printf("Test 1: original number = %d; abs_val = %d\n", test1, abs_val(test1));
	printf("Test 2: original number = %d; abs_val = %d\n", test2, abs_val(test2));
	printf("Test 3: original number = %d; abs_val = %d\n", test3, abs_val(test3));
	return 0;
}
