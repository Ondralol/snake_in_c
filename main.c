#include <stdio.h>
#include <stddef.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include "display.h"
#include "conversion.h"
#include "game.h"
#include "terminal.h"

#define WIDTH  42
#define HEIGHT 24
#define SNAKECHARACTER 100 /* TODO */

/* Only using single global variable for signal handling as there is no better way */
bool signalVal;

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
