#include <curses.h>

int clear(void)
{
	if (!(wclear(stdscr)))
		return 1;
	return 0;
}

