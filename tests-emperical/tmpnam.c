#include <stdio.h>

int main(void)
{
	char *pathname = "./currentpath/";
	char *ptr;


	//ptr = tmpnam(pathname);
	ptr = tmpnam(NULL);
	printf("%s\n", ptr);
	return 0;
}

