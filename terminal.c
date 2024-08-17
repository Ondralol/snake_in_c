#include <stdio.h>
#include <unistd.h>
#include "terminal.h"


void TChangeSettings(const char * str);

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


	/* Changing STDIN settings - processing new line instantly and not after \n, turning off ECHO*/
	oldSettings.c_lflag &= ~(ICANON | ECHO);


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
	/* Black background colour */
	//printf("%s", TBGBLACK);
}


void TChangeSettings(const char * str)
{
	printf("%s", str);
	fflush(stdout);
}


void TCursorReset ()
{
	printf("\x1B[H");
	fflush(stdout);
}


void TCursorMoveXY(int x, int y)
{
	printf("\033[%d;%dH", y, x);
	fflush(stdout);
}


void TCursorMoveRight(int x)
{
	printf("\033[%dC", x);
	fflush(stdout);
}


void TCursorMoveLeft(int x)
{
	printf("\033[%dD", x);
	fflush(stdout);
}


void TCursorMoveUp(int x)
{
	printf("\033[%dA", x);
	fflush(stdout);
}


void TCursorMoveDown(int x)
{
	printf("\033[%dB", x);
	fflush(stdout);
}

void TCursorDownLines(int x)
{
	printf("\033[%dE", x);
	fflush(stdout);
}

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
	usleep(1000);
	ioctl(1, TIOCGWINSZ, &size);
	*x = size.ws_col;
	*y = size.ws_row;
}









