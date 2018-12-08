#include <curses.h>

int wclear(WINDOW *win)
{
	int ret = 0;
	if (!(werase(win)))
		ret = 1;
	clearok(win, 1);
	return ret;
}

