#include <stdio.h>
#include <time.h>

int main(void)
{
	struct tm t = { 0 };
	char *buf;
	buf = asctime(&t);
	printf("%s", buf);
	return 0;
}
