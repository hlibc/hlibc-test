#include <curses.h>

void _line_refresh(WINDOW *win)
{
        size_t i, j, k;
        char lines[4096];
	memset(lines, 0, 4096);

        for (i=0, j=1, k=1;i < (size_t)(win->rp - win->buf) ; ++i)
        {
                /* a character is dirty mark the current line for redrawing */
                if (win->last[i] != win->buf[i] )
                        lines[k] = 1;

                if (j == win->x )
                {
                        j = 1;
                        ++k;
			lines[k] = 0;
                }
                else
                        ++j;
        }
        /* iterate through all lines */
        for (i=0,j=1; i<(size_t)(win->rp - win->buf);i+=(win->x), ++j)
        {
                /* A line was dirty, position the cursor and redraw it */
                if (lines[j])
                {
                        _setcursor(j, 0);
                        write(win->fd, win->buf + i, win->x);
                        memcpy(win->last + i, win->buf + i, win->x);
                }
        }
}

