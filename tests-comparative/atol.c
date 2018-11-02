#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(void)
{
	char string[1024];
	sprintf(string, "%ld", LONG_MAX);
	long d = atol(string);
	printf("LONG_MAX = %ld\n", d);
	sprintf(string, "%ld", LONG_MIN);
	d = atol(string);
	printf("LONG_MIN = %ld\n", d);
	return 0;
}
