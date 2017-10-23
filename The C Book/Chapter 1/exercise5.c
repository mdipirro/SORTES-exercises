#include <stdio.h>
#include <stdlib.h>
#define ARSIZE 16

int int2bin(int, char*);
int int2hex(int, char*);
int intFromChars();

/**
 * Read characters from standard input and return an integer correspnding
 * to the read characters.
 * @return An integer corresponding to the typed in characters
 */ 
int intFromChars() {
	char ch = getchar();
	int number = 0;
	while (ch != '\n') {
		number = number * 10 + (ch - 48);
		ch = getchar();
	}
	return number;
}

/**
 * Given a decimal number, cast it to its binary representation.
 * @param dec The number
 * @param binArray The array which will contain the binary representation
 * @return binArray's length
 */ 
int int2bin(int dec, char* binArray) {
	int i = ARSIZE - 1, number = dec;
	while (number) {
		binArray[i--] = number % 2 + 48;
		number /= 2;
	}
	i++;
	int j = 0;
	for (; i < ARSIZE; i++, j++) {
		binArray[j] = binArray[i];
	}
	return j;
}

/**
 * Given a decimal number, cast it to its hex representation.
 * @param dec The number
 * @param hex The array which will contain the hex representation
 * @return hex's length
 */ 
int int2hex(int dec, char* hex) {
	int i = ARSIZE - 1, number = dec;
	while (number) {
		hex[i--] = number % 16;
		number /= 16;
	}
	i++;
	int j = 0;
	for (; i < ARSIZE; i++, j++) {
		hex[j] = hex[i] + ((hex[i] < 10) ? 48 : 'A' - 10);
	}
	return j;
}
int main() {
	int dec = intFromChars();
	char bin[ARSIZE], hex[ARSIZE];
	printf("Decimal number: %d\n", dec);
	int binLength = int2bin(dec, bin);
	printf("Binary number: ");
	for (int i = 0; i < binLength; i++) {
		printf("%c", bin[i]);
	}
	int hexLength = int2hex(dec, hex);
	printf("\nHex number: ");
	for (int i = 0; i < hexLength; i++) {
		printf("%c", hex[i]);
	}
	return 0;
}
