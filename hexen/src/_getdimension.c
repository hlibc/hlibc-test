#include <curses.h>

int _getdimension(void)
{
        struct winsize w;
        if ((ioctl(0, TIOCGWINSZ, &w)) == -1)
                return 0;
        COLS = ansiglb.col = w.ws_col;
        LINES = ansiglb.row = w.ws_row;
        return 1;
}

