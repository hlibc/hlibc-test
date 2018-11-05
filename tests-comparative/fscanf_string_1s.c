#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *o = fopen("Makefile", "r");
	char s[1024] = { 0 };
	if (o == NULL) {
		fprintf(stderr, "'Makefile' not found for %s\n", argv[0]);
		return 1;
	}
	for(;fscanf(o, "%s", s) != EOF;) {
		printf("%s\n", s);
	}
	return 0;
}

