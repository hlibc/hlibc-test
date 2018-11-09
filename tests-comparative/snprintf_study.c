#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	char s[128];
	char *t = "Hello world";
	int size = 5;
	int lenret = snprintf(s, size, "%s", t);
	size_t len = strlen(s);
	printf("argument to snprintf was %d\n", size);
	printf("snprintf returned %d\n", lenret);
	
	printf("the string length was %zu\n", len);
	printf("new string is:\n");
	printf("%s\n", s);
	printf("old string was:\n");
	printf("%s\n", t);
	printf("length of old string was %zu\n", strlen(t));
	return 0;
}

