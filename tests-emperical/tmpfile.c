#include <stdio.h>

int main(void)
{
	FILE *fp = NULL;
	fp = tmpfile();
	//fp = fopen("dog", "w+");

	fprintf(fp, "This is a tmpfile test\n", 1);

	
	return 0;
}

