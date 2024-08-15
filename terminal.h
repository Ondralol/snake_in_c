#pragma once

#include <stddef.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/ioctl.h>

/* Reset */
#define TRESET   "\x1B[0m"

/* Character colours (regular) */

#define TRNORMAL "\x1B[0m"
#define TRRED    "\x1B[0;31m"
#define TRGREEN  "\x1B[0;32m"
#define TRYELLOW "\x1B[0;33m"
#define TRBLUE   "\x1B[0;34m"
#define TRWHITE  "\x1B[0;37m"

/* Character colours (bold) */

#define TBNORMAL "\x1B[1;0m"
#define TBRED    "\x1B[1;31m"
#define TBGREEN  "\x1B[1;32m"
#define TBYELLOW "\x1B[1;33m"
#define TBBLUE   "\x1B[1;34m"
#define TBWHITE  "\x1B[1;37m"

/* Background colour */

#define TBGBLACK "\x1B[40m"
#define TBGWHITE "\x1B[47m"

/* High intensity */

#define THIBLACK  "\x1B[0;90m"
#define THIRED    "\x1B[0;91m"
#define THIGREEN  "\x1B[0;92m"
#define THIYELLOW "\x1B[0;93m"
#define THIBLUE   "\x1B[0;94m"
#define THIWHITE  "\x1B[0;97m"

/* Bold high intensity */

#define THIBBLACK  "\x1B[1;90m"
#define THIBRED    "\x1B[1;91m"
#define THIBGREEN  "\x1B[1;92m"
#define THIBYELLOW "\x1B[1;93m"
#define THIBBLUE   "\x1B[1;94m"
#define THIBWHITE  "\x1B[1;97m"

/* High intensity background */

#define THIBGBLACK "\x1B[0;100m"
#define THIBGWHITE "\x1B[0;107m"

/* Cursor settings */

#define TDISABLECURSOR "\x1B[?25l"
#define TENABLECURSOR  "\x1B[?25h"

/* Alt screen */

#define TENTERALTSCREEN "\033[?1049h\033[H"
#define TEXITALTSCREEN  "\033[?1049l"

/* Terminal settings */
void TSetup(struct termios * settings);

void TReset(struct termios * settings);

/* Cursor functions */

void TChangeSettings(const char *);

void TCursorReset ();

void TCursorMoveXY(int x, int y);

void TCursorMoveRight(int x);

void TCursorMoveLeft(int x);

void TCursorMoveUp(int x);

void TCursorMoveDown(int x);

void TClearScreen();

void TEraseLine();

void TGetTerminalSize(int * x, int * y);

