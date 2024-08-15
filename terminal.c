#include <stdio.h>
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


  /* Black background colour */
  //printf("%s", TBGBLACK);
}


void TChangeSettings(const char * str)
{
  printf("%s", str);
}


void TCursorReset ()
{
  TCursorMoveXY(0,0);
}


void TCursorMoveXY(int x, int y)
{
  printf("\033[%d;%dH", y, x);
}


void TCursorMoveRight(int x)
{
  printf("\033[%dC", x);
}


void TCursorMoveLeft(int x)
{
  printf("\033[%dD", x);
}


void TCursorMoveUp(int x)
{
  printf("\033[%dA", x);
}


void TCursorMoveDown(int x)
{
  printf("\033[%dB", x);
}


void TClearScreen()
{
  TChangeSettings("\x1B[2J");
}


void TEraseLine()
{
  printf("\033[2K");
}

void TGetTerminalSize(int * x, int * y)
{
  struct winsize size;
  ioctl(1, TIOCGWINSZ, &size);
  *x = size.ws_col;
  *y = size.ws_row;
}









