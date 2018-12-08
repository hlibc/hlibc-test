#include <curses.h>

int wclrtobot(WINDOW *win)
{
	char buf[32];
	size_t len;
	len = sprintf(buf, "%s", ansiglb.t_clrcur2bot);
	write(win->fd, buf, len);
	return 1;
}

