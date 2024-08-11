#include <stdio.h>
#include <stddef.h>
#include "display.h"
#include "conversion.h"

#define WIDTH  32
#define HEIGHT 32
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

  runGame(width, height);
  return 0;
}
