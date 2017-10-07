#include <stdio.h>
#include <stdlib.h>

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

int main() {
	printf("Type some characters and you will see the corresponding integer.\n");
	printf("The number you typed is %d.", intFromChars());
	return 0;
}
