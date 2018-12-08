#include <curses.h>

int wgetch(WINDOW *win)
{
	char x;
	win = win; /* curses only has one input stream */
	read(0, &x, 1);
	return x;
}
