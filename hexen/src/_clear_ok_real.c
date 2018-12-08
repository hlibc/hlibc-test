#include <curses.h>

void _clear_ok_real(WINDOW *win)
{
        char buf[32];
        size_t len = 0;
        if (win->clearok == 1)
        {
                _setcursor(0, 1);
                len = sprintf(buf, "%s", ansiglb.t_eraseall);
                write(win->fd, buf, len);
		win->clearok = 0;
        }
}

