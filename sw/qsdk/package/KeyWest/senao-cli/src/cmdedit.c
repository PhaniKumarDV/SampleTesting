/* vi: set sw=4 ts=4: */
/*
 * Termios command line History and Editing.
 *
 * Copyright (c) 1986-2003 may safely be consumed by a BSD or GPL license.
 * Written by:   Vladimir Oleynik <dzo@simtreas.ru>
 *
 * Used ideas:
 *      Adam Rogoyski    <rogoyski@cs.utexas.edu>
 *      Dave Cinege      <dcinege@psychosis.com>
 *      Jakub Jelinek (c) 1995
 *      Erik Andersen    <andersen@codepoet.org> (Majorly adjusted for busybox)
 *
 * This code is 'as is' with no warranty.
 *
 *
 */

/*
   Usage and Known bugs:
   Terminal key codes are not extensive, and more will probably
   need to be added. This version was created on Debian GNU/Linux 2.x.
   Delete, Backspace, Home, End, and the arrow keys were tested
   to work in an Xterm and console. Ctrl-A also works as Home.
   Ctrl-E also works as End.

   Small bugs (simple effect):
   - not true viewing if terminal size (x*y symbols) less
     size (prompt + editor`s line + 2 symbols)
   - not true viewing if length prompt less terminal width
 */


#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <signal.h>
#include <limits.h>
#include <ostypes.h>
#include <cmdedit.h>


#ifdef CONFIG_LOCALE_SUPPORT
#define Isprint(c) isprint((c))
#else
#define Isprint(c) ( (c) >= ' ' && (c) != ((unsigned char)'\233') )
#endif

#define CONFIG_FEATURE_COMMAND_EDITING
#define CONFIG_FEATURE_NONPRINTABLE_INVERSE_PUT

#ifdef CONFIG_FEATURE_COMMAND_EDITING

/* Maximum length of the linked list for the command line history */
#ifndef CONFIG_FEATURE_COMMAND_HISTORY
#define MAX_HISTORY   15
#else
#define MAX_HISTORY   CONFIG_FEATURE_COMMAND_HISTORY
#endif

#if MAX_HISTORY < 1
#warning cmdedit: You set MAX_HISTORY < 1. The history algorithm switched off.
#else
static char *history[MAX_HISTORY+1]; /* history + current */
/* saved history lines */
static int n_history;
/* current pointer to history line */
static int cur_history;
#endif

#include <termios.h>
#define setTermSettings(fd,argp) tcsetattr(fd,TCSANOW,argp)
#define getTermSettings(fd,argp) tcgetattr(fd, argp);

/* Current termio and the previous termio before starting sh */
static struct termios initial_settings, new_settings;


static
volatile int cmdedit_termw = 80;        /* actual terminal width */
static
volatile int handlers_sets = 0; /* Set next bites: */

enum {
	SET_ATEXIT = 1,         /* when atexit() has been called
				   and get euid,uid,gid to fast compare */
	SET_WCHG_HANDLERS = 2,  /* winchg signal handler */
	SET_RESET_TERM = 4,     /* if the terminal needs to be reset upon exit */
};


static int cmdedit_x;           /* real x terminal position */
static int cmdedit_y;           /* pseudoreal y terminal position */
static int cmdedit_prmt_len;    /* lenght prompt without colores string */

static int cursor;              /* required global for signal handler */
static int len;                 /* --- "" - - "" - -"- --""-- --""--- */
static char *command_ps;        /* --- "" - - "" - -"- --""-- --""--- */
static
#ifndef CONFIG_FEATURE_SH_FANCY_PROMPT
	const
#endif
char *cmdedit_prompt;           /* --- "" - - "" - -"- --""-- --""--- */


#ifdef CONFIG_FEATURE_SH_FANCY_PROMPT
static char *hostname_buf;
static int num_ok_lines = 1;
#endif

static void cmdedit_setwidth(int w, int redraw_flg);

static void win_changed(int nsig)
{
	static __sighandler_t previous_SIGWINCH_handler;  /* for reset */

	/*   emulate      || signal call */
	if (nsig == -SIGWINCH || nsig == SIGWINCH) {
		int width = 0;
		get_terminal_width_height(0, &width, NULL);
		cmdedit_setwidth(width, nsig == SIGWINCH);
	}
	/* Unix not all standart in recall signal */

	if (nsig == -SIGWINCH)          /* save previous handler   */
		previous_SIGWINCH_handler = signal(SIGWINCH, win_changed);
	else if (nsig == SIGWINCH)      /* signaled called handler */
		signal(SIGWINCH, win_changed);  /* set for next call       */
	else                                            /* nsig == 0 */
		/* set previous handler    */
		signal(SIGWINCH, previous_SIGWINCH_handler);    /* reset    */
}

static void cmdedit_reset_term(void)
{
	if ((handlers_sets & SET_RESET_TERM) != 0) {
/* sparc and other have broken termios support: use old termio handling. */
		setTermSettings(STDIN_FILENO, (void *) &initial_settings);
		handlers_sets &= ~SET_RESET_TERM;
	}
	if ((handlers_sets & SET_WCHG_HANDLERS) != 0) {
		/* reset SIGWINCH handler to previous (default) */
		win_changed(0);
		handlers_sets &= ~SET_WCHG_HANDLERS;
	}
	fflush(stdout);
}


/* special for recount position for scroll and remove terminal margin effect */
static void cmdedit_set_out_char(int next_char)
{

	int c = (int)((unsigned char) command_ps[cursor]);

	if (c == 0)
		c = ' ';        /* destroy end char? */
#ifdef CONFIG_FEATURE_NONPRINTABLE_INVERSE_PUT
	if (!Isprint(c)) {      /* Inverse put non-printable characters */
		if (c >= 128)
			c -= 128;
		if (c < ' ')
			c += '@';
		if (c == 127)
			c = '?';
		printf("\033[7m%c\033[0m", c);
	} else
#endif
		putchar(c);
	if (++cmdedit_x >= cmdedit_termw) {
		/* terminal is scrolled down */
		cmdedit_y++;
		cmdedit_x = 0;

		if (!next_char)
			next_char = ' ';
		/* destroy "(auto)margin" */
		putchar(next_char);
		putchar('\b');
	}
	cursor++;
}

/* Move to end line. Bonus: rewrite line from cursor */
static void input_end(void)
{
	while (cursor < len)
		cmdedit_set_out_char(0);
}

/* Go to the next line */
static void goto_new_line(void)
{
	input_end();
	if (cmdedit_x)
		putchar('\n');
}


static inline void out1str(const char *s)
{
	if ( s )
		fputs(s, stdout);
}

static inline void beep(void)
{
	putchar('\007');
}

/* Move back one character */
/* special for slow terminal */
static void input_backward(int num)
{
	if (num > cursor)
		num = cursor;
	cursor -= num;          /* new cursor (in command, not terminal) */

	if (cmdedit_x >= num) {         /* no to up line */
		cmdedit_x -= num;
		if (num < 4)
			while (num-- > 0)
				putchar('\b');

		else
			printf("\033[%dD", num);
	} else {
		int count_y;

		if (cmdedit_x) {
			putchar('\r');          /* back to first terminal pos.  */
			num -= cmdedit_x;       /* set previous backward        */
		}
		count_y = 1 + num / cmdedit_termw;
		printf("\033[%dA", count_y);
		cmdedit_y -= count_y;
		/*  require  forward  after  uping   */
		cmdedit_x = cmdedit_termw * count_y - num;
		printf("\033[%dC", cmdedit_x);  /* set term cursor   */
	}
}

static void put_prompt(void)
{
	out1str(cmdedit_prompt);
	cmdedit_x = cmdedit_prmt_len;   /* count real x terminal position */
	cursor = 0;
	cmdedit_y = 0;                  /* new quasireal y */
}

#ifndef CONFIG_FEATURE_SH_FANCY_PROMPT
static void parse_prompt(const char *prmt_ptr)
{
	cmdedit_prompt = prmt_ptr;
	cmdedit_prmt_len = strlen(prmt_ptr);
	put_prompt();
}
#else
static void parse_prompt(const char *prmt_ptr)
{
	int prmt_len = 0;
	size_t cur_prmt_len = 0;
	char  flg_not_length = '[';
	char *prmt_mem_ptr = xcalloc(1, 1);
	char *pwd_buf = xgetcwd(0);
	char  buf2[PATH_MAX + 1];
	char  buf[2];
	char  c;
	char *pbuf;

	if (!pwd_buf) {
		pwd_buf=(char *)bb_msg_unknown;
	}

	while (*prmt_ptr) {
		pbuf    = buf;
		pbuf[1] = 0;
		c = *prmt_ptr++;
		if (c == '\\') {
			const char *cp = prmt_ptr;
			int l;

			c = bb_process_escape_sequence(&prmt_ptr);
			if(prmt_ptr==cp) {
			  if (*cp == 0)
				break;
			  c = *prmt_ptr++;
			  switch (c) {
			  case 'h':
				pbuf = hostname_buf;
				if (pbuf == 0) {
					pbuf = xcalloc(256, 1);
					if (gethostname(pbuf, 255) < 0) {
						strcpy(pbuf, "?");
					} else {
						char *s = strchr(pbuf, '.');

						if (s)
							*s = 0;
					}
					hostname_buf = pbuf;
				}
				break;
			  case '$':
				c = my_euid == 0 ? '#' : '$';
				break;
			  case 'W':
				pbuf = pwd_buf;
				cp = strrchr(pbuf,'/');
				if ( (cp != NULL) && (cp != pbuf) )
					pbuf += (cp-pbuf)+1;
				break;
			  case '!':
				snprintf(pbuf = buf2, sizeof(buf2), "%d", num_ok_lines);
				break;
			  case 'e': case 'E':     /* \e \E = \033 */
				c = '\033';
				break;
			  case 'x': case 'X':
				for (l = 0; l < 3;) {
					int h;
					buf2[l++] = *prmt_ptr;
					buf2[l] = 0;
					h = strtol(buf2, &pbuf, 16);
					if (h > UCHAR_MAX || (pbuf - buf2) < l) {
						l--;
						break;
					}
					prmt_ptr++;
				}
				buf2[l] = 0;
				c = (char)strtol(buf2, 0, 16);
				if(c==0)
					c = '?';
				pbuf = buf;
				break;
			  case '[': case ']':
				if (c == flg_not_length) {
					flg_not_length = flg_not_length == '[' ? ']' : '[';
					continue;
				}
				break;
			  }
			}
		}
		if(pbuf == buf)
			*pbuf = c;
		cur_prmt_len = strlen(pbuf);
		prmt_len += cur_prmt_len;
		if (flg_not_length != ']')
			cmdedit_prmt_len += cur_prmt_len;
		prmt_mem_ptr = strcat(xrealloc(prmt_mem_ptr, prmt_len+1), pbuf);
	}
	if(pwd_buf!=(char *)bb_msg_unknown)
		free(pwd_buf);
	cmdedit_prompt = prmt_mem_ptr;
	put_prompt();
}
#endif


/* draw prompt, editor line, and clear tail */
static void redraw(int y, int back_cursor)
{
	if (y > 0)                              /* up to start y */
		printf("\033[%dA", y);
	putchar('\r');
	put_prompt();
	input_end();                            /* rewrite */
	printf("\033[J");                       /* destroy tail after cursor */
	input_backward(back_cursor);
}

#ifdef CONFIG_FEATURE_COMMAND_EDITING_VI
#define DELBUFSIZ 128
static char *delbuf;  /* a (malloced) place to store deleted characters */
static char *delp;
static char newdelflag;      /* whether delbuf should be reused yet */
#endif

/* Delete the char in front of the cursor, optionally saving it
 * for later putback */
static void input_delete(int save)
{
	int j = cursor;

	if (j == len)
		return;

#ifdef CONFIG_FEATURE_COMMAND_EDITING_VI
	if (save) {
		if (newdelflag) {
			if (!delbuf)
				delbuf = malloc(DELBUFSIZ);
			/* safe if malloc fails */
			delp = delbuf;
			newdelflag = 0;
		}
		if (delbuf && (delp - delbuf < DELBUFSIZ))
			*delp++ = command_ps[j];
	}
#endif

	strcpy(command_ps + j, command_ps + j + 1);
	len--;
	input_end();                    /* rewrite new line */
	cmdedit_set_out_char(0);        /* destroy end char */
	input_backward(cursor - j);     /* back to old pos cursor */
}

#ifdef CONFIG_FEATURE_COMMAND_EDITING_VI
static void put(void)
{
	int ocursor, j = delp - delbuf;
	if (j == 0)
		return;
	ocursor = cursor;
	/* open hole and then fill it */
	memmove(command_ps + cursor + j, command_ps + cursor, len - cursor + 1);
	strncpy(command_ps + cursor, delbuf, j);
	len += j;
	input_end();                    /* rewrite new line */
	input_backward(cursor-ocursor-j+1); /* at end of new text */
}
#endif

/* Delete the char in back of the cursor */
static void input_backspace(void)
{
	if (cursor > 0) {
		input_backward(1);
		input_delete(0);
	}
}


/* Move forward one character */
static void input_forward(void)
{
	if (cursor < len)
		cmdedit_set_out_char(command_ps[cursor + 1]);
}

static void cmdedit_setwidth(int w, int redraw_flg)
{
	cmdedit_termw = cmdedit_prmt_len + 2;
	if (w <= cmdedit_termw) {
		cmdedit_termw = cmdedit_termw % w;
	}
	if (w > cmdedit_termw) {
		cmdedit_termw = w;

		if (redraw_flg) {
			/* new y for current cursor */
			int new_y = (cursor + cmdedit_prmt_len) / w;

			/* redraw */
			redraw((new_y >= cmdedit_y ? new_y : cmdedit_y), len - cursor);
			fflush(stdout);
		}
	}
}

static void cmdedit_init(void)
{
	cmdedit_prmt_len = 0;
	if ((handlers_sets & SET_WCHG_HANDLERS) == 0) {
		/* emulate usage handler to set handler and call yours work */
		win_changed(-SIGWINCH);
		handlers_sets |= SET_WCHG_HANDLERS;
	}

	if ((handlers_sets & SET_ATEXIT) == 0) {
		handlers_sets |= SET_ATEXIT;
		atexit(cmdedit_reset_term);     /* be sure to do this only once */
	}
}

#if MAX_HISTORY >= 1
static void get_previous_history(void)
{
	if(command_ps[0] != 0 || history[cur_history] == 0) {
		free(history[cur_history]);
		history[cur_history] = strdup(command_ps);
	}
	cur_history--;
}

static int get_next_history(void)
{
	int ch = cur_history;

	if (ch < n_history) {
		get_previous_history(); /* save the current history line */
		return (cur_history = ch+1);
	} else {
		beep();
		return 0;
	}
}

#ifdef CONFIG_FEATURE_COMMAND_SAVEHISTORY
void load_history ( const char *fromfile )
{
	FILE *fp;
	int hi;

	/* cleanup old */

	for(hi = n_history; hi > 0; ) {
		hi--;
		free ( history [hi] );
	}

	if (( fp = fopen ( fromfile, "r" ))) {

		for ( hi = 0; hi < MAX_HISTORY; ) {
			char * hl = bb_get_chomped_line_from_file(fp);
			int l;

			if(!hl)
				break;
			l = strlen(hl);
			if(l >= BUFSIZ)
				hl[BUFSIZ-1] = 0;
			if(l == 0 || hl[0] == ' ') {
				free(hl);
				continue;
			}
			history [hi++] = hl;
		}
		fclose ( fp );
	}
	cur_history = n_history = hi;
}

void save_history ( const char *tofile )
{
	FILE *fp = fopen ( tofile, "w" );

	if ( fp ) {
		int i;

		for ( i = 0; i < n_history; i++ ) {
			fprintf(fp, "%s\n", history [i]);
		}
		fclose ( fp );
	}
}
#endif

#endif

enum {
	ESC = 27,
	DEL = 127,
};


/*
 * This function is used to grab a character buffer
 * from the input file descriptor and allows you to
 * a string with full command editing (sort of like
 * a mini readline).
 *
 * The following standard commands are not implemented:
 * ESC-b -- Move back one word
 * ESC-f -- Move forward one word
 * ESC-d -- Delete back one word
 * ESC-h -- Delete forward one word
 * CTL-t -- Transpose two characters
 *
 * Minimalist vi-style command line editing available if configured.
 *  vi mode implemented 2005 by Paul Fox <pgf@foxharp.boston.ma.us>
 *
 */

#ifdef CONFIG_FEATURE_COMMAND_EDITING_VI
static int vi_mode;

void setvimode ( int viflag )
{
	vi_mode = viflag;
}

static void
vi_Word_motion(char *command, int eat)
{
	while (cursor < len && !isspace(command[cursor]))
		input_forward();
	if (eat) while (cursor < len && isspace(command[cursor]))
		input_forward();
}

static void
vi_word_motion(char *command, int eat)
{
	if (isalnum(command[cursor]) || command[cursor] == '_') {
		while (cursor < len &&
		    (isalnum(command[cursor+1]) ||
				command[cursor+1] == '_'))
			input_forward();
	} else if (ispunct(command[cursor])) {
		while (cursor < len &&
		    (ispunct(command[cursor+1])))
			input_forward();
	}

	if (cursor < len)
		input_forward();

	if (eat && cursor < len && isspace(command[cursor]))
		while (cursor < len && isspace(command[cursor]))
			input_forward();
}

static void
vi_End_motion(char *command)
{
	input_forward();
	while (cursor < len && isspace(command[cursor]))
		input_forward();
	while (cursor < len-1 && !isspace(command[cursor+1]))
		input_forward();
}

static void
vi_end_motion(char *command)
{
	if (cursor >= len-1)
		return;
	input_forward();
	while (cursor < len-1 && isspace(command[cursor]))
		input_forward();
	if (cursor >= len-1)
		return;
	if (isalnum(command[cursor]) || command[cursor] == '_') {
		while (cursor < len-1 &&
		    (isalnum(command[cursor+1]) ||
				command[cursor+1] == '_'))
			input_forward();
	} else if (ispunct(command[cursor])) {
		while (cursor < len-1 &&
		    (ispunct(command[cursor+1])))
			input_forward();
	}
}

static void
vi_Back_motion(char *command)
{
	while (cursor > 0 && isspace(command[cursor-1]))
		input_backward(1);
	while (cursor > 0 && !isspace(command[cursor-1]))
		input_backward(1);
}

static void
vi_back_motion(char *command)
{
	if (cursor <= 0)
		return;
	input_backward(1);
	while (cursor > 0 && isspace(command[cursor]))
		input_backward(1);
	if (cursor <= 0)
		return;
	if (isalnum(command[cursor]) || command[cursor] == '_') {
		while (cursor > 0 &&
		    (isalnum(command[cursor-1]) ||
				command[cursor-1] == '_'))
			input_backward(1);
	} else if (ispunct(command[cursor])) {
		while (cursor > 0 &&
		    (ispunct(command[cursor-1])))
			input_backward(1);
	}
}
#endif

/*
 * the emacs and vi modes share much of the code in the big
 * command loop.  commands entered when in vi's command mode (aka
 * "escape mode") get an extra bit added to distinguish them --
 * this keeps them from being self-inserted.  this clutters the
 * big switch a bit, but keeps all the code in one place.
 */

#define vbit 0x100

/* leave out the "vi-mode"-only case labels if vi editing isn't
 * configured. */
#define vi_case(caselabel) USE_FEATURE_COMMAND_EDITING(caselabel)

/* convert uppercase ascii to equivalent control char, for readability */
#define CNTRL(uc_char) ((uc_char) - 0x40)


int cmdedit_read_input(char *prompt, char command[BUFSIZ])
{
//printf("Called %s\n",__func__);
//printf("command=%s\n", command);
//printf("command=%x\n", command);
	int break_out = 0;
	int lastWasTab = FALSE;
	unsigned char c;
	unsigned int ic;
#ifdef CONFIG_FEATURE_COMMAND_EDITING_VI
	unsigned int prevc;
	int vi_cmdmode = 0;
#endif
	/* prepare before init handlers */
	cmdedit_y = 0;  /* quasireal y, not true work if line > xt*yt */
	len = 0;
	command_ps = command;

	getTermSettings(0, (void *) &initial_settings);
	memcpy(&new_settings, &initial_settings, sizeof(struct termios));
	new_settings.c_lflag &= ~ICANON;        /* unbuffered input */
	/* Turn off echoing and CTRL-C, so we can trap it */
	new_settings.c_lflag &= ~(ECHO | ECHONL | ISIG);
	/* Hmm, in linux c_cc[] not parsed if set ~ICANON */
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	/* Turn off CTRL-C, so we can trap it */
#       ifndef _POSIX_VDISABLE
#               define _POSIX_VDISABLE '\0'
#       endif
	new_settings.c_cc[VINTR] = _POSIX_VDISABLE;
	command[0] = 0;

	setTermSettings(0, (void *) &new_settings);
	handlers_sets |= SET_RESET_TERM;

	/* Now initialize things */
	cmdedit_init();
	/* Print out the command prompt */
	parse_prompt(prompt);

	while (1) {

		fflush(stdout);                 /* buffered out to fast */

		if (safe_read(0, &c, 1) < 1)
			/* if we can't read input then exit */
			goto prepare_to_die;

		ic = c;

#ifdef CONFIG_FEATURE_COMMAND_EDITING_VI
		newdelflag = 1;
		if (vi_cmdmode)
			ic |= vbit;
#endif
		switch (ic)
		{
		case '\n':
		case '\r':
			/* Enter */
			goto_new_line();
			break_out = 1;
			break;
		case CNTRL('A'):
			/* Control-a -- Beginning of line */
			input_backward(cursor);
			break;
		case CNTRL('B'):
			/* Control-b -- Move back one character */
			input_backward(1);
			break;
		case CNTRL('C'):
			/* Control-c -- stop gathering input */
			goto_new_line();
#ifndef CONFIG_ASH
			command[0] = 0;
			len = 0;
			lastWasTab = FALSE;
			put_prompt();
#else
			len = 0;
			break_out = -1; /* to control traps */
#endif
			break;
		case CNTRL('D'):
			/* Control-d -- Delete one character, or exit
			 * if the len=0 and no chars to delete */
			if (len == 0) {
					errno = 0;
prepare_to_die:
#if !defined(CONFIG_ASH)
				printf("quit");
				goto_new_line();
				/* cmdedit_reset_term() called in atexit */
				exit(EXIT_SUCCESS);
#else
				/* to control stopped jobs */
				len = break_out = -1;
				break;
#endif
			} else {
				input_delete(0);
			}
			break;
		case CNTRL('E'):
			/* Control-e -- End of line */
			input_end();
			break;
		case CNTRL('F'):
			/* Control-f -- Move forward one character */
			input_forward();
			break;
		case '\b':
		case DEL:
			/* Control-h and DEL */
			input_backspace();
			break;
		case '\t':
			break;
		case CNTRL('K'):
			/* Control-k -- clear to end of line */
			*(command + cursor) = 0;
			len = cursor;
			printf("\033[J");
			break;
		case CNTRL('L'):
			/* Control-l -- clear screen */
			printf("\033[H");
			redraw(0, len-cursor);
			break;
#if MAX_HISTORY >= 1
		case CNTRL('N'):
			/* Control-n -- Get next command in history */
			if (get_next_history())
				goto rewrite_line;
			break;
		case CNTRL('P'):
			/* Control-p -- Get previous command from history */
			if (cur_history > 0) {
				get_previous_history();
				goto rewrite_line;
			} else {
				beep();
			}
			break;
#endif
		case CNTRL('U'):
			/* Control-U -- Clear line before cursor */
			if (cursor) {
				strcpy(command, command + cursor);
				redraw(cmdedit_y, len -= cursor);
			}
			break;
		case CNTRL('W'):
			/* Control-W -- Remove the last word */
			while (cursor > 0 && isspace(command[cursor-1]))
				input_backspace();
			while (cursor > 0 &&!isspace(command[cursor-1]))
				input_backspace();
			break;
#if CONFIG_FEATURE_COMMAND_EDITING_VI
		case 'i'|vbit:
			vi_cmdmode = 0;
			break;
		case 'I'|vbit:
			input_backward(cursor);
			vi_cmdmode = 0;
			break;
		case 'a'|vbit:
			input_forward();
			vi_cmdmode = 0;
			break;
		case 'A'|vbit:
			input_end();
			vi_cmdmode = 0;
			break;
		case 'x'|vbit:
			input_delete(1);
			break;
		case 'X'|vbit:
			if (cursor > 0) {
				input_backward(1);
				input_delete(1);
			}
			break;
		case 'W'|vbit:
			vi_Word_motion(command, 1);
			break;
		case 'w'|vbit:
			vi_word_motion(command, 1);
			break;
		case 'E'|vbit:
			vi_End_motion(command);
			break;
		case 'e'|vbit:
			vi_end_motion(command);
			break;
		case 'B'|vbit:
			vi_Back_motion(command);
			break;
		case 'b'|vbit:
			vi_back_motion(command);
			break;
		case 'C'|vbit:
			vi_cmdmode = 0;
			/* fall through */
		case 'D'|vbit:
			goto clear_to_eol;

		case 'c'|vbit:
			vi_cmdmode = 0;
			/* fall through */
		case 'd'|vbit:
			{
			int nc, sc;
			sc = cursor;
			prevc = ic;
			if (safe_read(0, &c, 1) < 1)
				goto prepare_to_die;
			if (c == (prevc & 0xff)) {
			    /* "cc", "dd" */
			    input_backward(cursor);
			    goto clear_to_eol;
			    break;
			}
			switch(c) {
			case 'w':
			case 'W':
			case 'e':
			case 'E':
			    switch (c) {
			    case 'w':   /* "dw", "cw" */
				    vi_word_motion(command, vi_cmdmode);
				    break;
			    case 'W':   /* 'dW', 'cW' */
				    vi_Word_motion(command, vi_cmdmode);
				    break;
			    case 'e':   /* 'de', 'ce' */
				    vi_end_motion(command);
				    input_forward();
				    break;
			    case 'E':   /* 'dE', 'cE' */
				    vi_End_motion(command);
				    input_forward();
				    break;
			    }
			    nc = cursor;
			    input_backward(cursor - sc);
			    while (nc-- > cursor)
				    input_delete(1);
			    break;
			case 'b':  /* "db", "cb" */
			case 'B':  /* implemented as B */
			    if (c == 'b')
				    vi_back_motion(command);
			    else
				    vi_Back_motion(command);
			    while (sc-- > cursor)
				    input_delete(1);
			    break;
			case ' ':  /* "d ", "c " */
			    input_delete(1);
			    break;
			case '$':  /* "d$", "c$" */
			clear_to_eol:
			    while (cursor < len)
				    input_delete(1);
			    break;
			}
			}
			break;
		case 'p'|vbit:
			input_forward();
			/* fallthrough */
		case 'P'|vbit:
			put();
			break;
		case 'r'|vbit:
			if (safe_read(0, &c, 1) < 1)
				goto prepare_to_die;
			if (c == 0)
				beep();
			else {
				*(command + cursor) = c;
				putchar(c);
				putchar('\b');
			}
			break;
#endif /* CONFIG_FEATURE_COMMAND_EDITING_VI */

		case ESC:

#if CONFIG_FEATURE_COMMAND_EDITING_VI
			if (vi_mode) {
				/* ESC: insert mode --> command mode */
				vi_cmdmode = 1;
				input_backward(1);
				break;
			}
#endif
			/* escape sequence follows */
			if (safe_read(0, &c, 1) < 1)
				goto prepare_to_die;
			/* different vt100 emulations */
			if (c == '[' || c == 'O') {
				if (safe_read(0, &c, 1) < 1)
					goto prepare_to_die;
			}
			if (c >= '1' && c <= '9') {
				unsigned char dummy;

				if (safe_read(0, &dummy, 1) < 1)
					goto prepare_to_die;
				if(dummy != '~')
					c = 0;
			}
			switch (c) {
#if MAX_HISTORY >= 1
			case 'A':
				/* Up Arrow -- Get previous command from history */
				if (cur_history > 0) {
					get_previous_history();
					goto rewrite_line;
				} else {
					beep();
				}
				break;
			case 'B':
				/* Down Arrow -- Get next command in history */
				if (!get_next_history())
					break;
				/* Rewrite the line with the selected history item */
rewrite_line:
				/* change command */
				len = strlen(strcpy(command, history[cur_history]));
				/* redraw and go to eol (bol, in vi */
#if CONFIG_FEATURE_COMMAND_EDITING_VI
				redraw(cmdedit_y, vi_mode ? 9999:0);
#else
				redraw(cmdedit_y, 0);
#endif
				break;
#endif
			case 'C':
				/* Right Arrow -- Move forward one character */
				input_forward();
				break;
			case 'D':
				/* Left Arrow -- Move back one character */
				input_backward(1);
				break;
			case '3':
				/* Delete */
				input_delete(0);
				break;
			case '1':
			case 'H':
				/* <Home> */
				input_backward(cursor);
				break;
			case '4':
			case 'F':
				/* <End> */
				input_end();
				break;
			default:
				c = 0;
				beep();
			}
			break;

		default:        /* If it's regular input, do the normal thing */
#ifdef CONFIG_FEATURE_NONPRINTABLE_INVERSE_PUT
			/* Control-V -- Add non-printable symbol */
			if (c == CNTRL('V')) {
				if (safe_read(0, &c, 1) < 1)
					goto prepare_to_die;
				if (c == 0) {
					beep();
					break;
				}
			} else
#endif
			{
#if CONFIG_FEATURE_COMMAND_EDITING_VI
				if (vi_cmdmode)  /* don't self-insert */
					break;
#endif
				if (!Isprint(c)) /* Skip non-printable characters */
					break;
			}

			if (len >= (BUFSIZ - 2))        /* Need to leave space for enter */
				break;

			len++;

			if (cursor == (len - 1)) {      /* Append if at the end of the line */
				*(command + cursor) = c;
				*(command + cursor + 1) = 0;
				cmdedit_set_out_char(0);
			} else {                        /* Insert otherwise */
				int sc = cursor;

				memmove(command + sc + 1, command + sc, len - sc);
				*(command + sc) = c;
				sc++;
				/* rewrite from cursor */
				input_end();
				/* to prev x pos + 1 */
				input_backward(cursor - sc);
			}

			break;
		}
		if (break_out)                  /* Enter is the command terminator, no more input. */
			break;

		if (c != '\t')
			lastWasTab = FALSE;
	}/*while loop*/

	setTermSettings(0, (void *) &initial_settings);
	handlers_sets &= ~SET_RESET_TERM;

#if MAX_HISTORY >= 1
	/* Handle command history log */
	/* cleanup may be saved current command line */
	if (len> 0) {                                      /* no put empty line */
		int i = n_history;

		free(history[MAX_HISTORY]);
		history[MAX_HISTORY] = 0;
			/* After max history, remove the oldest command */
		if (i >= MAX_HISTORY) {
			free(history[0]);
			for(i = 0; i < (MAX_HISTORY-1); i++)
				history[i] = history[i+1];
		}
		history[i++] = strdup(command);
		cur_history = i;
		n_history = i;
#if defined(CONFIG_FEATURE_SH_FANCY_PROMPT)
		num_ok_lines++;
#endif
	}
#else  /* MAX_HISTORY < 1 */
#if defined(CONFIG_FEATURE_SH_FANCY_PROMPT)
	if (len > 0) {              /* no put empty line */
		num_ok_lines++;
	}
#endif
#endif  /* MAX_HISTORY >= 1 */
	if (break_out > 0) {
		command[len++] = '\n';          /* set '\n' */
		command[len] = 0;
	}
#if defined(CONFIG_FEATURE_SH_FANCY_PROMPT)
	free(cmdedit_prompt);
#endif
	cmdedit_reset_term();
	return len;
}



#endif  /* CONFIG_FEATURE_COMMAND_EDITING */


#ifdef TEST

const char *bb_applet_name = "debug stuff usage";

#ifdef CONFIG_FEATURE_NONPRINTABLE_INVERSE_PUT
#include <locale.h>
#endif

int main(int argc, char **argv)
{
	char buff[BUFSIZ];
	char *prompt =
#if defined(CONFIG_FEATURE_SH_FANCY_PROMPT)
		"\\[\\033[32;1m\\]\\u@\\[\\x1b[33;1m\\]\\h:\
\\[\\033[34;1m\\]\\w\\[\\033[35;1m\\] \
\\!\\[\\e[36;1m\\]\\$ \\[\\E[0m\\]";
#else
		"% ";
#endif
    /* Set the operation mode */
    g_opmode=getSysOperationMode();

    /* Overwrite the admin login ID and PWD */
    strcpy(loginAccList[0].name,apCfgGetStrValue(TELNETD_LOGIN_USERNAME_TOK));
    strcpy(loginAccList[0].pw,apCfgGetStrValue(TELNETD_REMOTE_PW_TOK));


#ifdef CONFIG_FEATURE_NONPRINTABLE_INVERSE_PUT
	setlocale(LC_ALL, "");
#endif
	while(1) {
		int l;
		l = cmdedit_read_input(prompt, buff);
		if(l > 0 && buff[l-1] == '\n') {
			buff[l-1] = 0;
			printf("*** cmdedit_read_input() returned line =%s=\n", buff);
		} else {
			break;
		}
	}
	printf("*** cmdedit_read_input() detect ^D\n");
	return 0;
}

#endif  /* TEST */
