#include <stdio.h>
#include <stdlib.h>

int compare(const char*, const char*);
const char* find(const char*, char);
const char* firstSubstring(const char*, const char*);

int compare(const char* s1, const char* s2) {
	while (*s1 && *s2 && *s1 == *s2) {
		s1++; s2++;
	}
	return (*s1 - *s2 > 0) ? *s1 - *s2 : *s2 - *s1;
}

const char* find(const char* string, char c) {
	while (*string && *string != c) {
		string++;
	}
	return (*string) ? string : 0;
}

const char* firstSubstring(const char* text, const char* pattern) {
	int found = 0;
	while (*text && !found) {
		const char* s = pattern;
		int i = 0;
		while (*s && *text && *s == text[i]) {
			i++; s++;
		}
		if (!*s) {
			found = 1;
		} else {
			text++;
		}
	}
	return (found) ? text : 0;
}

int main() {
	printf("Test compare 1: %d\n", compare("test", "test1"));
	printf("Test compare 2: %d\n", compare("test1", "test"));
	printf("Test compare 3: %d\n", compare("test", "test"));
	
	printf("Test find 1: %c\n", *find("test", 'e'));
	printf("Test find 2: %p\n", find("test", 'o'));
	
	printf("Test firstSubstring 1: %c\n", *firstSubstring("longtext", "ngt"));
	printf("Test firstSubstring 1: %p\n", firstSubstring("longtext", "ngtx"));
	return 0;
}
