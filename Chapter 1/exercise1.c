#include <stdio.h>

void showMessage();

int main() {
	int count = 0;
	while (count < 10) {
		showMessage();
		count++;
	}
	return 0;
}

/**
 * Show a predefined message: "Hello"
 */ 
void showMessage() {
	printf("Hello\n");
}
