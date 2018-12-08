#include "fcntl.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <terminal/ansi.h>

/* globals */
extern int LINES;
extern int COLS;

/* limits */
#define CURSES_MAX 10
#define CURSES_BUFSIZ 512

/* data types */
typedef char chtype;

typedef struct{ 
	int fd;
	char *rp; 
        char *buf;
	char *last;
	size_t len;
	size_t x;	/* total x coord */
	size_t y;	/* total y coord */
	size_t px;	/* x coord for cursor */
	size_t py;	/* y coord for cursor */
	bool clearok;	/* clear WINDOW during the next refresh */
} WINDOW;

extern WINDOW _IO_canon[CURSES_MAX]; 

/* global structures */
struct ansiglb{
        size_t row;     /* global rows    */
        size_t col;     /* global columns */
        size_t t;       /* total windows  */
        size_t c;       /* current window */
	char *t_eraseall;	/* terminal capability */
	char *t_insertreset;	/* terminal capability */
	char *t_gohome;		/* terminal capability */
	char *t_clrcur2bot;	/* terminal capability */
	char *t_clrtoeol;	/* terminal capability */
} ansiglb;

/* macros */
#define stdscr  (&_IO_canon[0])
#define curscr  (&_IO_canon[CURSES_MAX])

/** functions **/

/* cursor moving */
int wmove(WINDOW *, size_t, size_t);
int move(size_t, size_t);
/* initialize */
WINDOW *initscr(void);
/* character io */
int addch(chtype);
int waddch(WINDOW *, const chtype);
/* echo */
int noecho(void);
int echo(void);
/* internal */
int _termcatch(int, int);
void _setcursor(size_t, size_t);
int _getdimension(void);
void _vt100(void);
void _vt52(void);
void _line_refresh(WINDOW *);
void _simple_refresh(WINDOW *);
void _clear_ok_real(WINDOW *);
/* refresh */
int refresh(void);
int wrefresh(WINDOW *win);
/* erase */
int erase(void);
int werase(WINDOW *);
int clear(void);
int wclear(WINDOW *);
int clrtobot(void);
int wclrtobot(WINDOW *);
int clrtoeol(void);
int wclrtoeol(WINDOW *);
/* clearok */
int clearok(WINDOW *, bool);
/* getch */
int getch(void);
int wgetch(WINDOW *);




