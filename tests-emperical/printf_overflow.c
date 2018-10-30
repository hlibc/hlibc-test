#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	size_t i = INT_MAX;
	i++;
	char *s = malloc(i);
	if (!(s))
	{
		fprintf(stderr, "unable to allocate enough memory\n");
		return 0;
	}
	memset(s, 'A', i -1);
	s[i] = 0;
	printf("%s", s, 1);
	if (errno == EOVERFLOW)
		printf("printf overflow was caught\n");
	else
		printf("printf overflow was not caught\n");
	return 0;
}
