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

	fflush(stdout);
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
	TCursorDownLines(2);
	TCursorMoveRight((x/2)-8);
	printf("HIGHSCORE: %d\n", 0); //TODO
	
	TChangeSettings(TBGREEN);
	TCursorMoveRight((x/2)-35);
	printf("PRESS W/A/S/D TO START THE GAME, USE P TO PAUSE, E TO EXIT THE GAME"); // use esc later
	TChangeSettings(TRESET);
	fflush(stdout);
}


void displayGame(size_t width, size_t height, size_t * score )
{
	TClearScreen();
	signalVal = 0;
	
	int x, y;
  TGetTerminalSize(&x,&y);
	
	displayBorders(TBWHITE);
	
	TChangeSettings(THIBLACK);
	TCursorMoveXY((x - width) / 2 + 1, (y - height) / 2);
	
	/* Game borders */
	
	for (int i = 0; i < width; i ++)
	{
		printf("▄");
	}
	TCursorMoveXY((x - width) / 2 + 1, (y - height) / 2 + 1);	
	
	
	for (int i = 0; i < height - 2; i ++)
	{
		printf("█");
		TChangeSettings(TBWHITE);
		for (int j = 0; j < width -2; j++)
		{
			printf(".");
		}
		TChangeSettings(THIBLACK);
		printf("█");
		TCursorDownLines(1);
		TCursorMoveRight( (x-width) / 2);
	}	
	
	for (int i = 0; i < width; i ++)
	{
		printf("▀");
	}
	TCursorDownLines(2);	
	TCursorMoveRight((x)/2 - 5);
	TChangeSettings(TBGREEN);
	printf("SCORE: %zu", *score);
	TChangeSettings(TRESET);
}

void displaySnake(size_t width, size_t height, snake * gameData)
{
	int x, y;
  TGetTerminalSize(&x,&y);

	if ( (gameData->head).x == 0 && (gameData->head).y == 0 )
	{
		(gameData->head).x = x / 2;
		(gameData->head).y = y / 2;
	}

	
	if ( gameData -> currentDirection == UP )
		(gameData->head).y -= 1;
	
	else if ( gameData -> currentDirection == DOWN )
    (gameData->head).y += 1;

	else if ( gameData -> currentDirection == RIGHT )
		(gameData->head).x +=1;
	
	else if ( gameData -> currentDirection == LEFT )
    (gameData->head).x -= 1;


	TCursorMoveXY((gameData->head).x, (gameData->head).y);
	TChangeSettings(THIYELLOW);
	printf("▄");
	TCursorMoveXY((gameData->tail).x, (gameData->tail).y);
	
	if ( (gameData->tail).x != 0 && (gameData->tail).y != 0 )
  {
		TChangeSettings(TBWHITE);
		printf(".");
	}

	(gameData->tail).x = (gameData->head).x;
  (gameData->tail).y = (gameData->head).y;


	TChangeSettings(TRESET);
}





