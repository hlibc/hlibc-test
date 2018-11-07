#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *o = fopen("Makefile", "r");
	char s[1024] = { 0 };
	char t[1024] = { 0 };
	if (o == NULL) {
		fprintf(stderr, "'Makefile' not found for %s\n", argv[0]);
		return 1;
	}
	for(;fscanf(o, "%s%s", s, t) != EOF;) {
		printf("%s\n", s, t);
	}
	return 0;
}

