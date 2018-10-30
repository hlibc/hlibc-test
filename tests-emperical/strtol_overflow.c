#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	long i = LONG_MAX;
	long act = 0;
	char s[1000] = { 0 };
	sprintf(s, "%ld1", i);
	
	printf("%s", s);
	act = strtol(s, NULL, 10);
	if (errno == ERANGE)
		fprintf(stderr, "ERANGE was set\n");
	else
		fprintf(stderr, "ERANGE was not set\n");
	return 0;
}
