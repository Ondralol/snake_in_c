#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include "display.h"
#include "terminal.h"

// TODO animation of the borders
// TODO start animation
// TODO save highscore

extern bool signalVal;

void windowResize()
{
  signalVal = 1;
}


void displayBorders(const char * colour)
{
  int x, y;
  TGetTerminalSize(&x,&y);
  TCursorReset();
  TChangeSettings(colour);
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
	
	TChangeSettings(TRESET);
}

/* Pass score as argument somehow???*/
void displayMenu()
{
  TClearScreen();
	signalVal = 0;

  int x, y;
  TGetTerminalSize(&x,&y);
  
  displayBorders(TBWHITE);

  TCursorMoveXY((x/2)-35, (y/2)-5);
  
  TChangeSettings(THIBLACK);
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
	TChangeSettings(TRESET);
}


void displayGame(size_t width, size_t height, size_t * score, snake * gameData )
{
	TClearScreen();
	signalVal = 0;

	displayBorders(TBWHITE);
 	
	int x, y;
  TGetTerminalSize(&x,&y);

  displayBorders(TBWHITE);
	
	TChangeSettings(THIBLACK);

  TCursorMoveXY((x/2)-width/2 + 1, (y/2)-height/2);

  /* Game borders */
  for (int i = 0; i < width; i ++)
  {
      printf("▄");
  }
	printf("\n");
	TCursorMoveRight((x/2)-width/2);

  for (int i = 0; i < height - 2; i ++)
  {
    printf("█");
    for (int j = 0; j < width -2; j++)
    {
      TChangeSettings(THIWHITE);
			printf(".");
			TChangeSettings(THIBLACK);
    }	
    printf("█\n");
		TCursorMoveRight((x/2)-width/2);
  }	

  for (int i = 0; i < width; i ++)
  {
    printf("▀");
  }
  printf("\n");
	
	TCursorMoveDown(3);
	TCursorMoveRight((x/2)-4);
	
	TChangeSettings(TBGREEN);
	printf("SCORE: %zu", *score);

}

