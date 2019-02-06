#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char buf[1024];
	char *p = buf;
	p = getcwd(p, 1024);
	printf("%s\n", p);
	return 0;
}
