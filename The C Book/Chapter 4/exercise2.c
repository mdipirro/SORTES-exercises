#include <stdio.h>
#include <stdlib.h>

void output(char);

void output (char c) {
	static unsigned int lineNumber = 1;
	static unsigned int column = 1;
	
	if (c == '\n') {
		lineNumber++;
	} else {
		column++;
	}
	printf("%c", c);
}
