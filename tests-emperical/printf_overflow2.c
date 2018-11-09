#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	size_t i = INT_MAX;
	i += 2;
	char *s = malloc(i);
	if (!(s)) {
		fprintf(stderr, "unable to allocate enough memory\n");
		return 0;
	}
	memset(s, 'A', i - 1);
	s[i - 1] = 0;
	int len = 0;
	len = printf("%s", s, 1);
	if (errno == EOVERFLOW)
		fprintf(stderr, "printf overflow was caught\n");
	else
		fprintf(stderr, "printf overflow was not caught\n");
	fprintf(stderr, "%zu ret len\n", len);
	return 0;
}
