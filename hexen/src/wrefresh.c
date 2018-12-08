#include <curses.h>

int wrefresh(WINDOW *win)
{
	/* actually draw the character grid */ 
	_line_refresh(win);

	/* set the final user cursor position */
	_setcursor(win->px, win->py + 1); 

	/* reset the buffer pointer */
        win->rp = win->buf;

	return 0;
}
