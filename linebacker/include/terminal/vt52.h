

/* vt52 Compatible Mode */

#define T_CURSUP1ROW	"\033A"	/* A Cursor up one row */

#define T_CURSDN1ROW    "\033B"	/* B Cursor down one row */

#define T_CURS4D1COL    "\033C"	/* C Cursor forward one col */

#define T_CURSBK1COL    "\033D"	/* D Cursor back one col */

#define T_GOHOME	"\033H"	/* H Go home to row 1 x col 1 */

#define T_CLRCUR2BOT	"\033J"	/* J Clear to end of screen */

#define T_REVLINEFD	"\033I" /* reverse line feed */

#define T_SELASCII	"\033G" /* select ascii */

#define T_SELGRAPH	"\033F" /* select special graphics char set */

#define T_ALTKEYPAD	"\033=" /* alternate keypad mode */

#define T_LEAVEKPMD	"\033>" /* exit alternate keypad mode */

#define T_ANSIMODE	"\033<" /* ansi mode */

#define T_IDENTIFY	"\033Z" /* Identify */

#define T_CLRCUR2END    "\033K"	/* K Clear to end of line */


/* 
	TODO: cursor address 	ESC Y l c 
	"\0334412" ?
	
*/ 
