#include <stdio.h>

void dummyPrint();

void dummyPrint() {
	static unsigned int n = 100;
	
	if (n >= 1) {
		printf("%d\n", n);
		n--;
		dummyPrint();
	}
}


int main() {
	dummyPrint();
	return 0;
}
