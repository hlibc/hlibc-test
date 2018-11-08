#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[10])
{
	size_t i = INT_MAX;
	if (argc > 1)
		i += strtol(argv[1], NULL, 10);
	char *s = malloc(i);
	char *t = malloc(i);	
	if (!(s) || !(t))
	{
		fprintf(stderr, "unable to allocate enough memory\n");
		return 0;
	}
	memset(s, 'A', i -1);
	s[i - 1] = 0;
	snprintf(t, i, "%s", s, 1);
	if (errno == EOVERFLOW)
		fprintf(stderr, "printf overflow was caught\n");
	else
		fprintf(stderr, "printf overflow was not caught\n");
	size_t len = strlen(t);
	printf("%zu is len of string\n", len);
	if (len >= INT_MAX)
		fprintf(stderr, "len >= INT_MAX)\n");
	if (len >= INT_MAX -1)
		fprintf(stderr, "len >= INT_MAX -1\n");
	fprintf(stdout, "%d <-- actual INT_MAX\n", INT_MAX);
	return 0;
}
