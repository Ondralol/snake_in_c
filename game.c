#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "game.h"
#include "display.h"

void runGame(size_t width, size_t height)
{
    size_t currentScore = 0;
    while (true)
    {
      if ( !showMenu(currentScore) )
        return;
      
      showGame(&currentScore, width, height); 
    }
}
