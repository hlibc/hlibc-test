#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(void)
{
	char string[1024];
	sprintf(string, "%lld", LLONG_MAX);
	long long d = atoll(string);
	printf("LLONG_MAX = %lld\n", d);
	sprintf(string, "%lld", LLONG_MIN);
	d = atoll(string);
	printf("LLONG_MIN = %lld\n", d);
	return 0;
}
