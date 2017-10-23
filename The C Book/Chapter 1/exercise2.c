#include <stdio.h>
#include <stdlib.h>

int isPrime (int);

/**
 * Check whether a number is prime
 * @param number The number
 * @return 1 iff number is prime
 */ 
int isPrime (int number) {
	int divisor = number / 2, notPrime = 0;
	while(divisor > 1) {
		notPrime = (number % divisor == 0);
		divisor = (notPrime) ? 0 : divisor - 1;
	}
	return !notPrime;
}

int main() {
	int thisNumber = 3;
	while(thisNumber < 10000) {
		if (isPrime(thisNumber) && isPrime(thisNumber + 2)) {
			printf("(%d, %d) is a prime pair\n", thisNumber, thisNumber + 2);
		}
		thisNumber = thisNumber + 2;
	}
	return 0;
}
