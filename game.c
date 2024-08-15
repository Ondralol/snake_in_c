#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include "game.h"
#include "display.h"


/* TODO */ 

/*
typedef struct Settings
{
  int x;
  int y;
} Settings;
*/

int menuLogic(size_t score);
int gameLogic(size_t x, size_t y, size_t * score);

void runGame(size_t width, size_t height)
{
    size_t score = 0;
    int outputSignal = 0;
    while (true)
    {
      outputSignal = menuLogic(score);
      if (outputSignal == 0 )
        return;
     
      //else if (outputSignal == 1)
      
      outputSignal = gameLogic(width, height, &score);

      if (outputSignal == 0 )
        return;
    }

}

int menuLogic(size_t score)
{
  displayMenu();
  int c = 0;
  while (true)
  {
    signal(SIGWINCH, &displayMenu);
    
    c = getchar();
    switch (c)
    {
      case 'w':
        return 1;
      
      case 'a':
        return 1;

      case 's':
        return 1;

      case 'd':
        return 1;

      case 'e':
        return 0;
    }
  }

  return 0;
}

int gameLogic(size_t x, size_t y, size_t * score)
{
  return 0;
}

