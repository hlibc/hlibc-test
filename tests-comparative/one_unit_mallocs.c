#include <stdio.h>
#include <stdlib.h>

typedef struct object {
	char s[1];
} object;

int main(void)
{
	char *s;
	s = malloc(1);
	s[0] = '4';
	printf("%c\n", s[0]);
	object *o;
	o = malloc(sizeof(*o));
	o->s[0] = '8';
	printf("%c\n", o->s[0]);
	return 0;
}
