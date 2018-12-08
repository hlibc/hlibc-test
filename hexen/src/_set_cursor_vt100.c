#include <curses.h>

void _setcursor(size_t x, size_t y)
{
	/* 
		x = LINES global number of lines on terminal
		y = COLS  global number of columns on terminal
	*/
        char str[1024] = { 0 };
        size_t len = 0;
        len = sprintf(str, "\033[%zu;%zuH", x, y);
        write(stdscr->fd, str, len);
}

