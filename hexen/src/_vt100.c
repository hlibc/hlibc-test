#include <curses.h>

void _vt100(void)
{
        ansiglb.t_insertreset = T_INSERTRESET;
        ansiglb.t_clrcur2bot = T_CLRCUR2BOT;
        ansiglb.t_clrtoeol = T_CLRCUR2END;
        ansiglb.t_eraseall = T_ERASEALL;
}
