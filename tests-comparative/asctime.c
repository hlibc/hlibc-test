#include <stdio.h>
#include <time.h>

int main(void)
{
	struct tm t = { 0 };
	char *buf;
	buf = asctime(&t);
	//printf("%s\n", buf);
	return 0;
}
