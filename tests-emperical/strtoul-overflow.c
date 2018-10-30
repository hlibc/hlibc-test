#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	unsigned long i = ULONG_MAX;
	unsigned long act = 0;
	char s[1000] = { 0 };
	sprintf(s, "%lu1", i);
	act = strtoul(s, NULL, 10);
	if (errno == ERANGE)
		fprintf(stderr, "strtoul correctly set ERANGE for %s\n", s);
	else
		fprintf(stderr, "strtoul did not set ERANGE for %s\n", s);
	if (act == ULONG_MAX)
		fprintf(stderr, "strtoul correctly set %s to ULONG_MAX\n", s);
	else
		fprintf(stderr, "strtoul did not set %s to ULONG_MAX\n", s);

	errno = 0;
	unsigned long long i2 = ULLONG_MAX;
	unsigned long long act2 = 0;
	char s2[1000] = { 0 };
	sprintf(s2, "%llu1", i2);
	act2 = strtoul(s2, NULL, 10);
	if (errno == ERANGE)
		fprintf(stderr, "strtoll correctly set ERANGE for %s\n", s2);
	else
		fprintf(stderr, "strtoll did not set ERANGE for %s\n", s2);
	if (act == ULLONG_MAX)
		fprintf(stderr, "strtoll correctly set %s to ULLONG_MAX\n", s2);
	else
		fprintf(stderr, "strtoll did not set %s to ULLONG_MAX\n", s2);
	errno = 0;
	return 0;
}
