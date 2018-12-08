#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <curses.h>
#include <stdbool.h>

/*
	See LICENSE file for copyright and license details. 
*/

/* structs */
typedef struct Line{
	char *c;
	size_t len;
	size_t vlen;
	size_t mul;
	bool dirty;
	struct Line *next;
	struct Line *prev;
} Line;

typedef struct {
	Line *l;
	size_t o;
} filepos;

/* Globals */
Line *fstline;
Line *lstline;
Line *scrline;
filepos fsel;
filepos fcur;
int winchg = 0;
int tabstop = 8;

/* macros */
#define	LINSIZ 128
#define DELIM 0
#define TRUE 1
#define FALSE 0

/* function prototypes */
size_t edgetch(char *);
void *ecalloc(size_t, size_t);
void *erealloc(void *, size_t);
void f_delete(void);
void f_insert(char *);
void i_calcvlen(Line * l);
bool i_deltext(filepos, filepos);
bool i_writefile(char *);
void i_die(const char *str, int);
void i_edit(char *);
void i_readfile(char *);
void i_setup(void);
void i_sortpos(filepos *, filepos *);
void i_update(void);
filepos i_addtext(char *, filepos);
filepos m_nextchar(filepos);
filepos m_prevchar(filepos);
filepos m_nextline(filepos);
filepos m_prevline(filepos);
int getdimensions(void);
static void sigwinch(int);
int vlencnt(int, int);
int vlinecnt(Line *);

int main(int argc, char *argv[])
{ 
	if ( argc < 2 )
		i_die("Requires a file to edit\n", 1);

	setlocale(LC_ALL, ""); 
	initscr();
	signal(SIGWINCH, sigwinch);
	i_setup(); 
	i_readfile(argv[1]);
	i_edit(argv[1]);
	i_die("", 0);
	return 0;
} 

void *ecalloc(size_t nmemb, size_t size)
{
	void *ret; 
	if(!(ret = calloc(nmemb, size)))
		i_die("Can't calloc.\n", 1);
	return ret;
}

void *erealloc(void *ptr, size_t size)
{
	void *ret; 
	if (!(ret = realloc(ptr, size)))
		i_die("Can't realloc.\n", 1); 
	return ret;
}

void f_delete(void)
{ 
	filepos pos0 = fcur;
	filepos pos1 = m_prevchar(fcur);
	
	i_sortpos(&pos0, &pos1);
	
	if(i_deltext(pos0, pos1)) 
		fcur = pos0;
	else
		fcur = fsel = pos0;
}

void f_insert(char *cb)
{
	filepos newcur;

	newcur = i_addtext(cb, fcur);
	
	if(fcur.l != newcur.l)
		fsel = newcur;

	fcur = fsel = newcur; 
}

/* Add text at pos, return the position after the inserted text */
filepos i_addtext(char *buf, filepos pos)
{
	Line *l = pos.l, *lnew = NULL; 
	size_t o = pos.o, i = 0, il = 0;
	filepos f;
	char c;
	
	for(c = buf[0]; c != DELIM; c = buf[++i])
	{ 
		if(c == '\n' || c == '\r')
		{
			lnew = ecalloc(1, sizeof(Line));
			lnew->c = ecalloc(1, LINSIZ);
			lnew->dirty = l->dirty = TRUE;
			lnew->len = lnew->vlen = 0;
			lnew->mul = 1;
			lnew->next = l->next;
			lnew->prev = l;
			if(l->next)
				l->next->prev = lnew;
			else
				lstline = lnew;
			l->next = lnew;
			l = lnew;
			/* \n in the middle of a line */ 
			if(o + il < l->prev->len)
			{
				f.l = l;
				f.o = 0;
				i_addtext(&(l->prev->c[o + il]), f);
				l->prev->len = o + il;
				l->prev->c[o + il] = DELIM;
			}
			i_calcvlen(l->prev);
			o = il = 0; 
		} else
		{
			/* Regular char */
			if(2 + (l->len) >= LINSIZ * (l->mul))
				l->c = erealloc(l->c, LINSIZ * (++(l->mul)));
			memmove(l->c + il + o + 1, l->c + il + o, (1 + l->len - (il + o)));
			l->c[il + o] = c;
			l->dirty = TRUE;
			if(il + o >= (l->len)++)
				l->c[il + o + 1] = DELIM;
			il++;
		}
	}
	i_calcvlen(l);
	f.l = l;
	f.o = il + o; 
	return f;
}

/* Update the vlen value of a Line */
void i_calcvlen(Line * l)
{
	size_t i; 
	l->vlen = 0;
	for(i = 0; i < l->len; i++)
		l->vlen += vlencnt(l->c[i], l->vlen);
} 

void i_die(const char *str, int exitnumber)
{
	write(2, str, strlen(str)); 
	exit(exitnumber);
}

/* Delete text between pos0 and pos1, which MUST be in order, fcur integrity
   is NOT assured after deletion, fsel integrity is returned as a bool */
bool i_deltext(filepos pos0, filepos pos1)
{
	Line *ldel = NULL; 
	bool integrity = TRUE; 

	if(pos0.l == fsel.l)
		integrity = (fsel.o <= pos0.o || (pos0.l == pos1.l
			&& fsel.o > pos1.o));
	if(pos0.l == pos1.l)
	{ 
		memmove(pos0.l->c + pos0.o, pos0.l->c + pos1.o,
			(pos0.l->len - pos1.o));
		pos0.l->dirty = TRUE;
		pos0.l->len -= (pos1.o - pos0.o);
		pos0.l->c[pos0.l->len] = DELIM;
		i_calcvlen(pos0.l); 
	} else
	{
		pos0.l->len = pos0.o;
		pos0.l->c[pos0.l->len] = DELIM;
		pos0.l->dirty = TRUE;
		while(pos1.l != ldel)
		{
			if(pos1.l == pos0.l->next)
				i_addtext(&(pos0.l->next->c[pos1.o]), pos0);
			if(pos0.l->next->next)
				pos0.l->next->next->prev = pos0.l;
			ldel = pos0.l->next;
			pos0.l->next = pos0.l->next->next;
			if(scrline == ldel)
				scrline = ldel->prev;
			if(lstline == ldel)
				lstline = ldel->prev;
			if(fsel.l == ldel)
				integrity = FALSE;
			free(ldel->c);
			free(ldel);
		}
	}
	return integrity;
}

void i_edit(char *fname)
{ 
	while ( 1 )
	{ 
		if ( winchg == 1 )
		{ 
			initscr(); 
			winchg = 0; 
		}
		i_update(); 
		edgetch(fname);
	}
} 

void i_readfile(char *fname)
{
	int fd;
	ssize_t n;
	static char buf[BUFSIZ + 1];

	if((fd = open(fname, O_RDONLY)) == -1)
		i_die("unable to open file\n", 1);

	while((n = read(fd, buf, BUFSIZ)) > 0)
	{
		buf[n] = DELIM;
		fcur = i_addtext(buf, fcur);
	}
	fcur.l = fstline;
	fcur.o = 0;
	fsel = fcur; 
} 

void i_setup(void) 
{
	Line *l = NULL;
	l = ecalloc(1, sizeof(Line));
	l->c = ecalloc(1, LINSIZ);
	l->dirty = FALSE;
	l->len = l->vlen = 0;
	l->mul = 1;
	l->next = NULL;
	l->prev = NULL; 
	fstline = lstline = scrline = fcur.l = l;
	fcur.o = 0;
	fsel = fcur;
} 

/* Exchange pos0 and pos1 if not in order */
void i_sortpos(filepos * pos0, filepos * pos1)
{
	filepos p;
	for(p.l = fstline; p.l; p.l = p.l->next)
	{
		if(p.l == pos0->l || p.l == pos1->l)
		{
			if((p.l == pos0->l && (p.l == pos1->l && pos1->o < pos0->o)) || (p.l == pos1->l && p.l != pos0->l))
				p = *pos0, *pos0 = *pos1, *pos1 = p;
			break;
		}
	}
}

/* Repaint screen */ 
void i_update(void)
{
	int iline;
	int irow;
	int ixrow;
	int ivchar;
	int i;
	int vlines;
	int cursor_r = 0, cursor_c = 0;
	size_t ichar; 
	Line *l;
	size_t z = 0;
	
	/* Check offset */
	for(l = fstline, iline = 1; l && scrline->prev && l != scrline; iline++, l = l->next)
	{
		if(l == fcur.l)
		{ 
			for (i=0;l != scrline;)
			{
				if(vlinecnt(scrline) > 1)
				{
					i = -1;
					break;
				}
				i++;
				scrline = scrline->prev;
			}
			if(i < 0 || i > LINES)
				scrline = l;
			break;
		} 
	}
	for(i = irow = 1, l = scrline; l; l = l->next, irow += vlines)
	{ 
		vlines = vlinecnt(l);
		if(fcur.l == l)
		{ 
			while(irow + vlines > LINES && scrline->next)
			{
				irow -= vlinecnt(scrline);
				i += vlinecnt(scrline); 
				scrline = scrline->next;
				iline++;
			}
			break;
		}
	} 
	
	/*  update screen */
	for(irow = 1 , l = scrline; irow < LINES; irow += vlines, iline++) 
	{
		vlines = vlinecnt(l);
		if(fcur.l == l)
		{
			cursor_c = 0;
			cursor_r = irow;
			for(ichar = 0; ichar < fcur.o; ichar++)
				cursor_c += vlencnt(fcur.l->c[ichar], cursor_c);
			while(cursor_c >= COLS)
			{
				cursor_c -= COLS;
				cursor_r++;
			}
		} 
		if(l)
			l->dirty = FALSE; 
		for(ixrow = ichar = ivchar = 0; ixrow < vlines && (irow + ixrow) < LINES; ixrow++)
		{ 
			/* it's a bit of a delicate balance in here making gcurses work correctly
				and behave like ncurses. If you enable the refresh it will fail.
				Conversely if you disable the move() then ncurses will fail.
			*/
			move((irow + ixrow ), (ivchar % COLS));
			//refresh(); 
			while(ivchar < (1 + ixrow) * COLS) 
			{
				if(l && ichar < l->len)
				{ 
					if(l->c[ichar] == '\t')
					{ 
						z  = vlencnt('\t', ivchar); 
						for (; z ; z--)
							addch(' ');
					}
					else 
					{
						addch(l->c[ichar]);
					}
					ivchar += vlencnt(l->c[ichar], ivchar);
					ichar++;
				} else
				{ 
					addch(' ');
					++ivchar;
					++ichar; 
				} 
			} 
		} 
		if(l)
			l = l->next; 
	}

	move(cursor_r, cursor_c);
	refresh();
} 

bool i_writefile(char *fname)
{
	int fd = 1; 
	bool wok = TRUE;
	Line *l; 

	if(fname != NULL
		&& (fd = open(fname, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH |
			S_IWOTH)) == -1) {
		/* error */ 
		return FALSE;
	} 
	for(l = fstline; wok && l; l = l->next)
	{
		if(write(fd, l->c, l->len) == -1 || (l->next && write(fd, "\n", 1) == -1))
			wok = FALSE;
	} 
	close(fd);
	return wok;
}

filepos m_bol(filepos pos)
{
	pos.o = 0;
	return pos;
}

filepos m_nextchar(filepos pos)
{
	if(pos.o < pos.l->len)
	{
		pos.o++; 
	} else if(pos.l->next)
	{
		pos.l = pos.l->next;
		pos.o = 0;
	}
	return pos;
} 

filepos m_prevchar(filepos pos)
{
	if(pos.o > 0)
	{
		pos.o--; 
	} else if(pos.l->prev)
	{
		pos.l = pos.l->prev;
		pos.o = pos.l->len;
	}
	return pos;
} 

filepos m_nextline(filepos pos)
{
	size_t ivchar, ichar; 
	for(ivchar = ichar = 0; ichar < pos.o; ichar++)
		ivchar += vlencnt(pos.l->c[ichar], ivchar); 
	if(pos.l->next)
	{ 
		for(pos.l = pos.l->next, pos.o = ichar = 0; ichar < ivchar && pos.o < pos.l->len; pos.o++)
			ichar += vlencnt(pos.l->c[pos.o], ichar); 
	} else
	{
		pos.o = pos.l->len;
	}
	return pos;
}

filepos m_prevline(filepos pos)
{
	size_t ivchar, ichar; 
	for(ivchar = ichar = 0; ichar < pos.o; ichar++)
		ivchar += vlencnt(pos.l->c[ichar], (ivchar % (COLS - 1))); 
	if(pos.l->prev)
	{ 
		for(pos.l = pos.l->prev, pos.o = ichar = 0; ichar < ivchar && pos.o < pos.l->len; pos.o++)
			ichar += vlencnt(pos.l->c[pos.o], ichar); 
	} else
	{
		pos.o = 0;
	}
	return pos;
} 

size_t edgetch(char *fname)
{
	static size_t len = 0; 
	char cb[7] = {0} ;
	  
	char ch = getch(); 

	switch (ch)
	{ 
		case 033:
			ch = getch(); 
			switch (ch)
			{
				case '[': 
					ch = getch(); 
					switch (ch)
					{ 
						case 'A': /* arrow up */ 
							fcur = m_prevline(fcur); 
							break;
						case 'B': /* arrow down */ 
							fcur = m_nextline(fcur); 
							break;
						case 'C': /* right arrow */ 
							fcur = m_nextchar(fcur); 
							break;
						case 'D': /* left arrow */ 
							fcur = m_prevchar(fcur); 
							break;
					}
			}
			return len;
		case 0177:
			f_delete();
			break;
		case 030:
			i_writefile(fname);
			break;
		case 016:
			i_die("", 0);
			break; 
		default:
			cb[0] = (char) ch;
			f_insert(cb);
			break;
	}
	return len;
}
	
static void sigwinch(int sig)
{
	if (sig)
		winchg = 1;
}

int vlencnt(int ch, int col)
{
	if ( ch == '\t' )
		return tabstop - (col % tabstop);
	return 1;
}

int vlinecnt(Line *l)
{
	if ( l )
		return ( 1 + ( l->vlen / COLS));
	return 1;
} 

