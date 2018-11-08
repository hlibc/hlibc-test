#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	size_t i = INT_MAX;
	++i;
	char *s = malloc(i);
	if (!(s))
	{
		fprintf(stderr, "unable to allocate enough memory\n");
		return 1;
	}
	memset(s, 'A', i -1);
	s[i -1] = 0;
	long long len = printf("%s", s, 1);
	
	if (errno == EOVERFLOW)
		fprintf(stderr, "printf set EOVERFLOW\n");
	else
		fprintf(stderr, "printf did not set EOVERFLOW\n");

	fprintf(stderr, "printf returned %lld\n", len);
	return 0;
}
