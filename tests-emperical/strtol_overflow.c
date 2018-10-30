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
	
	
	act = strtol(s, NULL, 10);
	if (errno == ERANGE)
		fprintf(stderr, "strtol correctly set ERANGE for %s\n", s);
	else
		fprintf(stderr, "strtol did not set ERANGE for %s\n", s);
	if (act == LONG_MAX)
		fprintf(stderr, "strtol correctly set %s to LONG_MAX\n", s);
	else
		fprintf(stderr, "strtol did not set %s to LONG_MAX\n", s);
	return 0;
}
