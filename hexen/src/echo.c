#include <curses.h>

int echo(void)
{
	_termcatch(~(ICANON & ECHO), 0);
	return 0;
}

