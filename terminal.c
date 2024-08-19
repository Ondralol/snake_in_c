#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "terminal.h"

extern int signalVal;

void TChangeSettings(const char * str);

/* Handles Ctrl C */
void INTHandler(int dummy)
{
	signalVal = 2;
}

/* Sets up all terminal settings */
void TSetup(struct termios * settings)
{
	/* Saving the old terminal settings */
	struct termios oldSettings;
	tcgetattr(STDIN_FILENO, &oldSettings);
	*settings = oldSettings;

	/* Enters alt screen */
	TChangeSettings(TENTERALTSCREEN);

	/* Disabling the cursor */
	TChangeSettings(TDISABLECURSOR);

	/* Non-blocking behaviour*/
	fcntl( 0, F_SETFL, O_NONBLOCK);

	/* Ctrl C signal handling */
	signal(SIGINT, INTHandler);

	/* Changing STDIN settings - processing new line instantly and not after \n, turning off ECHO */
	oldSettings.c_lflag &= ~(ICANON | ECHO);
	
	/* For random number generation */
	srand(time(NULL));

	/* Applying new settings */
	tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
	fflush(stdout);
}

/* Resets all terminal settings */
void TReset(struct termios * settings)
{
	tcsetattr(STDIN_FILENO, TCSANOW, settings);
	
	/* Resets colours and style */
	TChangeSettings(TRESET);

	/* Shows cursor */
	TChangeSettings(TENABLECURSOR);

	/* Exits alt screen */
	TChangeSettings(TEXITALTSCREEN);

	fflush(stdout);
}

/* Changes settings using ansi escape sequence */
void TChangeSettings(const char * str)
{
	printf("%s", str);
	fflush(stdout);
}

void TRGBBackground (size_t r, size_t g, size_t b)
{
	printf("\033[48;2;%zu;%zu;%zum", r,g,b);
	fflush(stdout);
}

void TRGBForeground (size_t r, size_t g, size_t b)
{
  printf("\033[38;2;%zu;%zu;%zum", r,g,b);
  fflush(stdout);
}

/* Sets cursor to position 0,0 */
void TCursorReset ()
{
	printf("\x1B[H");
	fflush(stdout);
}

/* Move to XY coordinate */
void TCursorMoveXY(int x, int y)
{
	printf("\033[%d;%dH", y, x);
	fflush(stdout);
}

/* Moves right by X */
void TCursorMoveRight(int x)
{
	printf("\033[%dC", x);
	fflush(stdout);
}

/* Moves left by X */
void TCursorMoveLeft(int x)
{
	printf("\033[%dD", x);
	fflush(stdout);
}

/* Moves up by X */
void TCursorMoveUp(int x)
{
	printf("\033[%dA", x);
	fflush(stdout);
}

/* Moves down by X */
void TCursorMoveDown(int x)
{
	printf("\033[%dB", x);
	fflush(stdout);
}

/* Moves down by X linex */
void TCursorDownLines(int x)
{
	printf("\033[%dE", x);
	fflush(stdout);
}

/* Moves up by X lines*/
void TCursorUpLines(int x)
{
	printf("\033[%dF", x);
	fflush(stdout);
}


void TClearScreen()
{
	TChangeSettings("\x1B[2J");
	fflush(stdout);
}


void TEraseLine()
{
	printf("\033[2K");
	fflush(stdout);
}

void TGetTerminalSize(int * x, int * y)
{
	struct winsize size;
	usleep(1000); // apparently this is really needed here
	ioctl(1, TIOCGWINSZ, &size);
	*x = size.ws_col;
	*y = size.ws_row;
}









