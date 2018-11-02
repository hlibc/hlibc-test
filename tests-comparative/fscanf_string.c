#include <stdio.h>

int main(void)
{
	FILE *o = fopen("Makefile", "r");
	char array[1024] = { 0 };
	char *s = array;
	
	char array2[1024] = { 0 };
	char *s2 = array2;
	fscanf(o, "%s%s", s, s2);
	printf("%s%s", s, s2);
	return 0;
}
