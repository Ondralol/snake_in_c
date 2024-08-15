#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include "display.h"
#include "terminal.h"

// TODO animation of the borders
// TODO start animation
// TODO save highscore

void displayBorders()
{
  int x, y;
  TGetTerminalSize(&x,&y);
  TCursorReset();
  TChangeSettings(TBWHITE);
  for ( int i = 0; i < x; i ++)
    printf("▀");

  for ( int i = 1; i < y; i ++ )
  {
    TCursorMoveXY(0,i);
    printf("█");
    TCursorMoveXY(x,i);
    printf("█");
  }
  TCursorMoveXY(0,y);
  for ( int i = 0; i < x; i ++) 
    printf("▀");

}

/* Pass score as argument somehow???*/
void displayMenu()
{
  TClearScreen();
  
  int x, y;
  TGetTerminalSize(&x,&y);
  
  displayBorders();

  TCursorMoveXY((x/2)-35, (y/2)-5);
  
  TChangeSettings(TBWHITE);
  //printf("S N A K E\n");
  
  
  printf(" ░▒▓███████▓▒░▒▓███████▓▒░  ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░\n");
  TCursorMoveRight((x/2)-35);
  printf("░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        \n");
  TCursorMoveRight((x/2)-35);
  printf("░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        \n");
  TCursorMoveRight((x/2)-35);
  printf(" ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓███████▓▒░░▒▓██████▓▒░   \n");
  TCursorMoveRight((x/2)-35);
  printf("       ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░        \n");
  TCursorMoveRight((x/2)-35);
  printf("       ░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░       \n");
  TCursorMoveRight((x/2)-35);
  printf("░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░ \n");

  TChangeSettings(TBRED);
  TCursorMoveDown(1);
  TCursorMoveRight((x/2)-8);
  printf("HIGHSCORE: %d\n", 0); //TODO
  
  TChangeSettings(TBGREEN);
  TCursorMoveRight((x/2)-35);
  printf("PRESS W/A/S/D TO START THE GAME, USE P TO PAUSE, E TO EXIT THE GAME"); // use esc later
}


void displayGame(size_t * currentScore, size_t width, size_t height, position pos )
{
  int x = pos.x;
  int y = pos.y;
  

  for (int i = 0; i < 100; i++) printf("\n");

  //printf("\033[44m");
  printf(" SCORE: %zu\n", *currentScore);


  /* Game borders */
  for (int i = 0; i < width; i ++)
  {
    if (i == 0)
      printf("╔");
    else if (i == width - 1)
      printf("╗");
    else
      printf("═");
  }
  printf("\n");

  for (int i = 0; i < height - 2; i ++)
  {
    printf("║");
    for (int j = 0; j < width -2; j++)
    {
      //printf(" ");
      if ( i == y && j == x )
        printf("▄");
      else
        printf(".");
    }
    printf("║\n");
  }

  for (int i = 0; i < width; i ++)
  {
    if (i == 0)
      printf("╚");
    else if (i == width -1)
      printf("╝");
    else
      printf("═");
  }
  printf("\n");

  /* 24FPS */
  usleep(10000);
}

bool showGame (size_t * currentScore, size_t width, size_t height)
{
  position pos;
  pos.x = width/2;
  pos.y = height/2;
  int c;

  while (true)
  {
    displayGame(currentScore, width, height, pos);
    c = getchar();
    switch (c)
    {
      case 'w':
        pos.y --; break;
      case 's':
        pos.y ++; break;
      case 'a':
        pos.x --; break;
      case 'd':
        pos.x ++; break;
      //case 'e':
        //return 0;
    }
    pos.y --;
  }
  return 0;
}

