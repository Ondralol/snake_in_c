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

/* Width and height of the game screen, x and y represent size of the terminal window */
void displayTiles(size_t width, size_t height, size_t x, size_t y)
{
	/* Turning off buffer */
	//setvbuf(stdout, NULL, _IONBF, 0);

	/* White background */

	TCursorMoveXY(x/2 - (width*4 + width*2 + 1)/2 + 1, y / 2 - (height * 2 + height + 1)/2 );	
	TChangeSettings(TBWHITE);
	for (int i = 0; i < height*2 + height + 1; i ++)
	{
		for (int j = 0; j < width + width / 2; j++)
		{
			printf("████");
			fflush(stdout);
		}
		printf("██");
		printf("\n");
		TCursorMoveRight(x/2 - (width*4 + width*2 + 1)/2);
	}
	
	/* Printing tiles */
  //usleep(15000);
	//fflush(stdout);
	//usleep(2500);
	TCursorMoveXY(x/2 - (width*4 + width*2 + 1)/2 + 1, y / 2 - (height * 2 + height + 1)/2  + 1);
	TChangeSettings(TBGREEN);
	TCursorMoveRight(2);
	for (int i = 0; i < height * 2; i ++)
  {
		for (int j = 0; j < width ; j ++ )
    {
		  printf("████");
			TCursorMoveRight(2);
			//usleep(10000);
		}
    printf("\n");
    if (i %2 != 0)
			TCursorDownLines(1);
		TCursorMoveRight(x/2 - (width*4 + width*2 + 1)/2 + 2);
  	//if ( i == height )
		//	usleep(1500);
		
	}
	
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
	
	/* Game borders */
	displayTiles(width, height, x, y);


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
		(gameData->head).x = x/2 - (width*4 + width*2 + 1)/2 + 3;
		(gameData->head).y = y / 2 - (height * 2 + height)/2 + 1;
	}

	
	if ( gameData -> currentDirection == UP )
		(gameData->head).y -= 3;
	
	else if ( gameData -> currentDirection == DOWN )
		(gameData->head).y += 3;

	else if ( gameData -> currentDirection == RIGHT )
		(gameData->head).x += 6;
	
	else if ( gameData -> currentDirection == LEFT )
		(gameData->head).x -= 6;


	TCursorMoveXY((gameData->head).x, (gameData->head).y);
	TChangeSettings(THIYELLOW);
	printf("████");
	TCursorMoveXY((gameData->head).x, (gameData->head).y + 1);
	printf("████");
	TCursorMoveXY((gameData->tail).x, (gameData->tail).y);
	
	if ( (gameData->tail).x != 0 && (gameData->tail).y != 0 )
	{
		TChangeSettings(TBGREEN);
		printf("████");
		TCursorMoveXY((gameData->tail).x, (gameData->tail).y +1);
		printf("████");
	}

	(gameData->tail).x = (gameData->head).x;
	(gameData->tail).y = (gameData->head).y;


	TChangeSettings(TRESET);
}





