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

	/* Printing border */
	TCursorMoveXY(x/2 - width * 2 - 1, y/2 - height - 1 );
	TChangeSettings(THIBLACK);
	
	printf("█");
	for ( int i = 0; i < width; i ++ )
		printf("████");
	printf("███");
	
	for ( int i = 0; i < height * 2; i ++)
	{
		TCursorMoveXY(x/2 - width * 2 - 1, y/2 - height  + i);
		printf("██");
		TCursorMoveXY(x/2 - width * 2 + width * 4 + 1, y/2 - height  + i);
    printf("██");
	}
	
	TCursorMoveXY(x/2 - width * 2 - 1, y/2 - height + height * 2 );

	printf("█");
	for ( int i = 0; i < width; i ++ )
    printf("████");
  printf("███");

	

	/* Printing the pattern */

	TCursorDownLines(1);
	TCursorMoveXY(x/2 - width * 2 + 1, y/2 - height);	
	TChangeSettings(THIGREEN);
	for (int i = 0; i < height*2; i ++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("████");
			fflush(stdout);
		}
		printf("\n");
		TCursorMoveRight(x/2 - width * 2);
	}
	
	/* Printing tiles */
  //usleep(15000);
	//fflush(stdout);
	//usleep(2500);
	
	    
	TCursorMoveXY(x/2 - width * 2 + 1, y/2 - height); 
	TChangeSettings(TRGREEN);
	//problem with odd numbers
	for (int i = 0; i < height; i ++)
  {
    for (int j = 0; j < width/2; j++)
    {
      if ( i % 2 == 0 )
			{
				printf("████");
				TCursorMoveRight(4);
			}
			else
			{
        TCursorMoveRight(4);
				printf("████");
			}
    }
    printf("\n");
    TCursorMoveRight(x/2 - width * 2);
  	
		for (int j = 0; j < width/2; j++)
    {
      if ( i % 2 == 0 )
      {
        printf("████");
        TCursorMoveRight(4);
      }
			else
      {
        TCursorMoveRight(4);
        printf("████");
      }
    }
		printf("\n");
    TCursorMoveRight(x/2 - width * 2);

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
	//TODO random
  if ( gameData -> head == NULL )
  {
    gameData -> head = dequeAddFront(gameData -> head, x/2 - width * 2 + 1 + width / 2 * 4, y/2 - height + height);
	}

	
	if ( gameData ->  currentDirection == UP )
		gameData -> head = dequeAddFront(gameData -> head, gameData -> head -> x, gameData -> head -> y - 2);
	
	else if ( gameData -> currentDirection == DOWN )
		gameData -> head = dequeAddFront(gameData -> head, gameData -> head -> x, gameData -> head -> y + 2);

	else if ( gameData -> currentDirection == RIGHT )
		gameData -> head = dequeAddFront(gameData -> head, gameData -> head -> x + 4, gameData -> head -> y);
	
	else if ( gameData -> currentDirection == LEFT )
		gameData -> head = dequeAddFront(gameData -> head, gameData -> head -> x - 4, gameData -> head -> y);

	TCursorMoveXY(gameData -> head -> x, gameData -> head -> y);
	//TChangeSettings(TBBLUE);
	TRGBForeground(0,0,139);
	printf("████");
	TCursorMoveXY( gameData -> head -> x, gameData->head -> y + 1);
	printf("████");
	
	
	if ( gameData->tail != NULL )
	{
		//if no apple TODO
		/* Restores screen after snake*/
		TCursorMoveXY(x/2 - width * 2 + 1, y/2 - height);
		if ( (gameData -> tail -> x - (x/2 - width * 2 + 1) ) % 8 == 0 && (gameData -> tail -> y - (y/2 - height) ) % 4 == 0 ) 
			TChangeSettings(TBGREEN);
		else if ( (gameData -> tail -> x + 4 - (x/2 - width * 2 + 1) ) % 8 == 0 && (gameData -> tail -> y + 2 - (y/2 - height) ) % 4 == 0 ) 
			TChangeSettings(TBGREEN);
		else
			TChangeSettings(THIGREEN);
		
		TCursorMoveXY( gameData -> tail -> x, gameData -> tail -> y);
		printf("████");
		TCursorMoveXY( gameData -> tail -> x, gameData -> tail -> y +1);
		printf("████");	
	}
	
	gameData -> tail = dequeTail(gameData -> head);

	gameData -> tail -> x = gameData -> head -> x;
	gameData -> tail -> y = gameData -> head -> y;


	TChangeSettings(TRESET);
	fflush(stdout);
}





