#include <stdio.h>

int currLine();
int currCol();
void output(char);

static unsigned int lineNumber = 1;
static unsigned int column = 1;

void output (char c) {
	if (c == '\n') {
		lineNumber++;
	} else {
		column++;
	}
	printf("%c", c);
}

int currLine() {
	return lineNumber;
}

int currCol() {
	return column;
}
