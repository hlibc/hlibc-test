#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *o = fopen("data.txt", "r");
	char s[1024] = { 0 };
	int t = 0;
	int v = 0;
	if (o == NULL) {
		fprintf(stderr, "'Makefile' not found for %s\n", argv[0]);
		return 1;
	}
	for(;fscanf(o, "%d%d", &t, &v) != EOF;) {
		printf("%d%d\n", t, v);
	}
	return 0;
}

