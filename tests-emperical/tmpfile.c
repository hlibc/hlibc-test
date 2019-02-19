#include <stdio.h>

int main(void)
{
	FILE *fp = NULL;
	fp = tmpfile();
	fprintf(fp, "This is a tmpfile test\n", 1);
	return 0;
}

