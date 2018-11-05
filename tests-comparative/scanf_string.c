#include <stdio.h>

int main(void)
{
	FILE *o = fopen("Makefile", "r");
	if (o == NULL) {
		fprintf(stderr, "'Makefile' not found for scanf_string\n");
		return 1;
	}
	for(;fscanf(o, "%s", s) != EOF) {
		printf("%s\n", s);
	}
	return 0;
}

