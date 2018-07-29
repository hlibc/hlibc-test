#include <stdio.h>
#include <stdlib.h>

void f(void)
{
	fprintf(stderr, "The atexit handlers fired off\n");
}

int main(void)
{
	atexit(f);
	fprintf(stderr, "The program is above the atexit handler in main\n");
	return 0;
}
