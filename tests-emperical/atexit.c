#include <stdio.h>
#include <stdlib.h>

void f(void)
{
	fprintf(stderr, "The atexit handlers fired off\n");
	fprintf(stderr, "Exit handle 1\n");
}
void g(void)
{
        fprintf(stderr, "The atexit handlers fired off\n");
	fprintf(stderr, "Exit handle 2\n");
}
void h(void)
{
        fprintf(stderr, "The atexit handlers fired off\n");
	fprintf(stderr, "Exit handle 3\n");
}


int main(void)
{
	atexit(f);
	atexit(g);
	atexit(h);
	fprintf(stderr, "The program is above the atexit handler in main\n");
	fprintf(stderr, "There should be a 3 2 1 countdown\n");
	
	return 0;
}
