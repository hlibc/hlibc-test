#include <curses.h> 

int _termcatch(int flags, int reset)
{
	static int set = 0;
	static struct termios term, oterm;
	
	/* catch the user's original terminal state _once_ */
	if ( set == 0 )
	{
		if ((tcgetattr(0, &oterm)) != 0 )
			return -1;
		memcpy(&term, &oterm, sizeof(term));
		set = 1;
	}
	/* Set the programmer's terminal attributes */
	if ( reset == 0 )
	{
		term.c_lflag &= (flags);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;

		if ((tcsetattr(0, TCSANOW, &term)) == 0 )
			return 0;
	/* Programmer access to reset user's terminal state */
	}else if ( reset == 1 )
		if ((tcsetattr(0, TCSANOW, &oterm)) == 0 )
			return 0;

	return -1;
	
}


