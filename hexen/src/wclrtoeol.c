#include <curses.h>

int wclrtoeol(WINDOW *win)
{
	char buf[32];
	size_t len;
	len = sprintf(buf, "%s", ansiglb.t_clrtoeol);
	write(win->fd, buf, len);
	return 1;
}

