#include <stdio.h>

int main(void)
{
	FILE *fd = fopen("blankfile", "w+");
	size_t i = 0;
	while (i++< 100)
		fputc('x', fd);
	return 0;
}
