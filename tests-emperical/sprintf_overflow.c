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
	char *t = malloc(i);	
	if (!(s))
	{
		fprintf(stderr, "unable to allocate enough memory\n");
		return 0;
	}
	memset(s, 'A', i -1);
	s[i] = 0;
	snprintf(t, i, "%s", s, 1);
	if (errno == EOVERFLOW)
		fprintf(stderr, "printf overflow was caught\n");
	else
		fprintf(stderr, "printf overflow was not caught\n");
	size_t len = strlen(t);
	printf("%zu\n", len);
	if (len >= INT_MAX)
		fprintf(stderr, "pow\n");
	if (len >= INT_MAX -1)
		fprintf(stderr, "pow truncated\n");
	fprintf(stdout, "%zu <-- actual INT_MAX\n", INT_MAX);
	return 0;
}
