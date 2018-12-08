#include <curses.h>

int werase(WINDOW *win)
{
	size_t len = win->x + win->y;
	size_t i = 0;
	int ret = 0;
	if (!(win))
		ret = 1;
	for ( ; i < len ; ++i) 
		win->buf[i] = ' '; 
	return ret;
}
