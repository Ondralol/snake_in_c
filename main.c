#include <stdio.h>
#include <stddef.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include "display.h"
#include "conversion.h"
#include "game.h"
#include "terminal.h"

/* For now requires even numbers */
#define WIDTH	14
#define HEIGHT 14
#define SNAKECHARACTER 100 /* TODO */

/* Only using single global variable for signal handling as there is no better way */
int signalVal = -1;

int main (int argc, char ** argv)
{
	size_t width = WIDTH;
	size_t height = HEIGHT;
	
	if ( argc == 3 )
	{
		strToNum(&width, argv[1]);
		strToNum(&height, argv[2]);
	}

	/* Changing terminal settings */
	struct termios settings;

	TSetup(&settings);
	runGame(width, height);

	/* Restoring the old settings */
	
	TReset(&settings);

	return 0;
}
