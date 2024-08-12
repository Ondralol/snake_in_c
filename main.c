#include <stdio.h>
#include <stddef.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include "display.h"
#include "conversion.h"
#include "game.h"

#define WIDTH  16
#define HEIGHT 16
#define SNAKECHARACTER 100 //ascii value

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
  static struct termios oldSettings, newSettings;
  
  /* Saving the old terminal settings */
  tcgetattr(STDIN_FILENO, &oldSettings);
  newSettings = oldSettings;

  /* Changing STDIN settings - processing new line instantly and not after \n, turning off ECHO*/
  newSettings.c_lflag &= ~(ICANON | ECHO); 
  
  
  /* Applying new settings */
  tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

  runGame(width, height);

  /* Restoring the old settings */
  tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
  
  

  return 0;
}
