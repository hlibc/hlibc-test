#include <curses.h>

int wmove(WINDOW *win, size_t x, size_t y)
{ 
	win->px = x;
	win->py = y;
	return 1;
}
