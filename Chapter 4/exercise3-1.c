#include <stdio.h>
#include <stdlib.h>

int currLine();
int currCol();
void output(char);

int main(){
	printf("Line %d\n", curr_line());
	printf("Column %d\n", curr_col());
	output('a');
	printf("Column %d\n", curr_col());
	output('\n');
	printf("Line %d\n", curr_line());
	printf("Column %d\n", curr_col());
	return 0;
}
