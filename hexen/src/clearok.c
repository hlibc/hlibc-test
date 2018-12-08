#include <curses.h>

int clearok(WINDOW *win, bool bf)
{
	win->clearok = bf;
	return 1;
}
