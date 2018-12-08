#include <curses.h>

int erase(void)
{
	if (!(werase(stdscr)))
		return 1;
	return 0;
}
