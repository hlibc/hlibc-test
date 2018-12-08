#include <curses.h>

int move (size_t x, size_t y)
{ 
	return wmove(stdscr, x, y);
}
