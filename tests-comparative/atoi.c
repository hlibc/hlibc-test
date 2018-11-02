#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(void)
{
	char string[1024];
	sprintf(string, "%d", INT_MAX);
	int d = atoi(string);
	printf("INT_MAX = %d\n", d);
	sprintf(string, "%d", INT_MIN);
	d = atoll(string);
	printf("INT_MIN = %d\n", d);
	return 0;
}
