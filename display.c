#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "display.h"
#include "terminal.h"
#include "gameData.h"


extern int signalVal;

/* Sets flag when the window is resized */
void windowResize()
{
	signalVal = 1;
}


void displayBorders(const char * colour)
{
	int x, y;
	TGetTerminalSize(&x,&y);
	TCursorReset();
	
	/* Prints borders */

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

/* Displays the menu text */
void displayMenu()
{
	TClearScreen();
	signalVal = 0;

	int x, y;
	TGetTerminalSize(&x,&y);
	
	displayBorders(TBWHITE);

	TCursorMoveXY((x/2)-35, (y/2)-5);
	
	TChangeSettings(THIBLACK);

	/* Displays pixel art */
	
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
	printf("HIGHSCORE: %d\n", getHighScore());
	
	TChangeSettings(TBGREEN);
	TCursorMoveRight((x/2)-41);
	printf("PRESS 'W'/'A'/'S'/'D' OR 'ARROWS' TO START THE GAME, USE 'P' TO PAUSE, 'E' TO EXIT THE GAME"); // use esc later
	TCursorDownLines(1);
	TCursorMoveRight(x/2-25);
	printf("USE 'W/'A'/'S'/'D' OR ARROWS TO CONTROL THE SNAKE");
	TChangeSettings(TRESET);
	fflush(stdout);
}

/* Calls other functions needed to display the main game screen*/
void displayGame(size_t width, size_t height)
{
	TClearScreen();
	signalVal = 0;
	
	int x, y;
	TGetTerminalSize(&x,&y);
	
	displayBorders(TBWHITE);
	
	/* Game borders */
	displayTiles(width, height, x, y);

	TChangeSettings(TRESET);
}

/* Displays single tile based on width and height of the board, size of the window and tile position */
void displaySnakeTile(int width, int height, int tileX, int tileY, int r, int g, int b)
{
	int x, y;
  TGetTerminalSize(&x,&y);
	TCursorMoveXY(x/2 - width * 2 + 1 + tileX * 4, y/2 - height + tileY * 2);
	
	TRGBForeground(r,g,b);
  printf("████");
  TCursorMoveXY(x/2 - width * 2 + 1 + tileX * 4, y/2 - height + tileY * 2 + 1);
	printf("████");

}

/* Display all snake 'tiles' */
void displaySnakeAll(snake * gameData, int width, int height)
{
	snakePositionDeque * head = gameData -> head;
	bool first = 1;
	while ( head )
	{
		if (first)
			displaySnakeTile(width, height, head -> x, head -> y, 0, 0, 128);
		else
		displaySnakeTile(width, height, head -> x, head -> y, 8,24,168);

		first = 0;
		head = head -> prev;
	}
}

/* Displays the game board based on width and height of the game board, x and y which represent the size of the terminal window */
void displayTiles(size_t width, size_t height, size_t x, size_t y)
{

	/* Prints the border of the board */
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

	

	/* Prints the chess pattern */

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
	
	    
	TCursorMoveXY(x/2 - width * 2 + 1, y/2 - height); 
	TChangeSettings(TRGREEN);
	for (int i = 0; i < height; i ++)
  {
		for (int j = 0; j < width / 2; j++)
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
  	
		for (int j = 0; j < width / 2; j++)
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

/* Displays the first 3 snake tiles and the apple, basically sets up the game */
void displayStartGame(size_t width, size_t height, snake * gameData)
{
	
	int x, y;
  TGetTerminalSize(&x,&y);

	TCursorMoveXY(x/2 - 5, y/2 - height - 1  + 2 * height + 4);
  TChangeSettings(TBGREEN);
  printf("SCORE: %x", gameData -> score);
	
	gameData -> head = dequeAddFront(gameData -> head,  width / 2, height / 2 - 2);
	
	displaySnakeTile(width, height, gameData -> head -> x, gameData -> head -> y,8,24,168);

	fflush(stdout);
	usleep(100000);

	gameData -> head = dequeAddFront(gameData -> head, width / 2, height / 2 - 1);
	displaySnakeTile(width, height, gameData -> head -> x, gameData -> head -> y, 8,24,168);

	fflush(stdout);
  usleep(100000);


	gameData -> head = dequeAddFront(gameData -> head, width / 2, height / 2 );

	displaySnakeTile(width, height, gameData -> head -> x, gameData -> head -> y, 0,0,128);

	fflush(stdout);
  usleep(100000);
	usleep(2);
	
	gameData -> tail = dequeTail(gameData -> head);

}

/* Displays the pause game graphics */
void displayPause(size_t width, size_t height, snake * gameData)
{
	signalVal = 0;
	int x, y;
  TGetTerminalSize(&x,&y);
	
	/* Changes color to white*/
	TChangeSettings(THIWHITE);
	TRGBBackground(255,255,255);
	
	/* Printing 'PAUSE' in pixel ART, line by line */
	/* First line */
	TCursorMoveXY(x/2 - 24, y/2 - 5 );
	printf("██████"); TCursorMoveRight(6);printf("████"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(4);printf("██");
	TCursorMoveRight(4); printf("██████"); TCursorMoveRight(2); printf("████████");

	/* Second line*/
	TCursorMoveXY(x/2 - 24, y/2 - 4 );
	printf("██"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(2);printf("██"); TCursorMoveRight(4);printf("██"); 
  TCursorMoveRight(2); printf("██"); TCursorMoveRight(4); printf("██");TCursorMoveRight(2); printf("██"); TCursorMoveRight(8); printf("██");
	
	/* Third line*/
	TCursorMoveXY(x/2 - 24, y/2 - 3 );
  printf("██████"); TCursorMoveRight(4);printf("████████"); TCursorMoveRight(2);printf("██"); TCursorMoveRight(4);printf("██");
  TCursorMoveRight(4); printf("████");TCursorMoveRight(4); printf("██████");
	
	/* Fourth line*/
	TCursorMoveXY(x/2 - 24, y/2 - 2 );
  printf("██"); TCursorMoveRight(8);printf("██"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(2);printf("██");
  TCursorMoveRight(4); printf("██");TCursorMoveRight(8); printf("██");TCursorMoveRight(2); printf("██");
	
	/* Fifth line*/
  TCursorMoveXY(x/2 - 24, y/2 - 1 );
  printf("██"); TCursorMoveRight(8);printf("██"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(2);printf("████████");
  TCursorMoveRight(2); printf("██████");TCursorMoveRight(4); printf("████████");

	/* Prints the text */
	TCursorMoveXY(x/2 - 20, y/2 + 1 );
	TChangeSettings(THIWHITE);
	printf("PRESS 'P' TO CONTINUE, PRESS 'E' TO EXIT");
}

/* Handles the collision, apple spawning and displaying logic for snake */
bool displaySnake(size_t width, size_t height, snake * gameData)
{
	int x, y;
	TGetTerminalSize(&x,&y);
	
	/* Spawns the first apple */
	if ( gameData -> appleX == -1 )
	{
		gameData -> appleX = rand() % width;
    gameData -> appleY = rand() % height;
	}
	
	/* Displays the apple*/
	displaySnakeTile(width, height, gameData -> appleX, gameData -> appleY, 255,0,0);

  /* If there is no head */
	if ( gameData -> head == NULL )
  {
		displayStartGame(width, height, gameData);
	}

	/* Displays snakes body */
	displaySnakeTile(width, height, gameData -> head -> x, gameData -> head -> y, 8,24,168);

	/* Updates snakes position based on direction */
	if ( gameData ->  currentDirection == UP )
		gameData -> head = dequeAddFront(gameData -> head, gameData -> head -> x, gameData -> head -> y - 1);
	
	else if ( gameData -> currentDirection == DOWN )
		gameData -> head = dequeAddFront(gameData -> head, gameData -> head -> x, gameData -> head -> y + 1);

	else if ( gameData -> currentDirection == RIGHT )
		gameData -> head = dequeAddFront(gameData -> head, gameData -> head -> x + 1, gameData -> head -> y);
	
	else if ( gameData -> currentDirection == LEFT )
		gameData -> head = dequeAddFront(gameData -> head, gameData -> head -> x - 1, gameData -> head -> y);

	/* Checks for collision with wall */
	if ( gameData -> head -> x < 0 || gameData -> head -> x >= width || gameData -> head -> y < 0 || gameData -> head -> y >= height )
	{
		displaySnakeTile(width, height, gameData -> head -> x, gameData -> head -> y, 128, 0, 0);
		return false;
	}
	/* Check for collision with the snake body */
	if (dequeFindPosition(gameData -> head -> prev, gameData -> head -> x, gameData -> head -> y) )
  {
		displaySnakeTile(width, height, gameData -> head -> x, gameData -> head -> y, 128,0,0);
		return false;
	}
	/* Snakes head */
	displaySnakeTile(width, height, gameData -> head -> x, gameData -> head -> y, 0,0,128);
	
	/* Check for snake collision */

	
	if ( gameData->tail != NULL )
	{
		/* If snake ate apple, spawn new one */
		if ( dequeFindPosition(gameData -> head, gameData -> appleX, gameData -> appleY))
		{
			displaySnakeAll(gameData, width, height);
			gameData -> appleX = rand() % width;
			gameData -> appleY = rand() % height;
			(gameData -> score)++;
		}
		/* If snake did not eat the apple this iteration, remove the tail and print the board on its place */
		else
		{
			/* Simple logic so the chess pattern is preserved */
			if ( gameData -> tail -> y % 2 == 0 && gameData -> tail -> x % 2 == 0 ) 
				displaySnakeTile(width, height, gameData -> tail -> x, gameData -> tail -> y, 38, 162, 105);
			else if ( gameData -> tail -> y % 2 != 0 && gameData -> tail -> x % 2 != 0) 
				displaySnakeTile(width, height, gameData -> tail -> x, gameData -> tail -> y, 38, 162, 105);
			else
				displaySnakeTile(width, height, gameData -> tail -> x, gameData -> tail -> y, 51, 218, 122);	
			
			gameData -> tail = dequePopBack(gameData -> tail);
		}
	}
	
	/* Displays the score */	
	TCursorMoveXY(x/2 - 5, y/2 - height - 1  + 2 * height + 4);
 	TChangeSettings(TBGREEN);
  printf("SCORE: %x", gameData -> score);
	

	TChangeSettings(TRESET);
	fflush(stdout);
	return true;
}

/* Displays score, highscore and pixel art for gameover screen */
void displayGameOver(size_t width, size_t height, snake * gameData)
{
	signalVal = 0;
  int x, y;
  TGetTerminalSize(&x,&y);

  /* Changes the colour to white */
	TChangeSettings(THIWHITE);
		
	/* Displaying "GAME OVER" in pixel art, basically just moving to the right coordinates and printing the "pixels" */
	/* No, there is no better way to do this, because I want to preserve the the game screen under the text */
	
	/* 1st line */
  TCursorMoveXY(x/2 - 20, y/2 - 8 );
  TCursorMoveRight(2);printf("██████"); TCursorMoveRight(4);printf("████"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(6);printf("██");
   TCursorMoveRight(2); printf("████████");

  /* 2nd line*/
  TCursorMoveXY(x/2 - 20, y/2 - 7 );
  printf("██"); TCursorMoveRight(8);printf("██"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(2);printf("████");
  TCursorMoveRight(2); printf("████");TCursorMoveRight(2);printf("██");

  /* 3rd line*/
  TCursorMoveXY(x/2 - 20, y/2 - 6 );
  printf("██"); TCursorMoveRight(2);printf("████"); TCursorMoveRight(2);printf("████████");TCursorMoveRight(2);printf("██"); TCursorMoveRight(2);printf("██");
  TCursorMoveRight(2); printf("██"); TCursorMoveRight(2); printf("██████");

  /* 4th line*/
  TCursorMoveXY(x/2 - 20, y/2 - 5 );
  printf("██"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(2);printf("██"); TCursorMoveRight(4);printf("██");
  TCursorMoveRight(2); printf("██");TCursorMoveRight(6); printf("██");TCursorMoveRight(2); printf("██");

	/* 5th line*/
  TCursorMoveXY(x/2 - 20, y/2 - 4 );
  TCursorMoveRight(2);printf("██████"); TCursorMoveRight(2);printf("██"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(2);printf("██");
	TCursorMoveRight(6); printf("██"); TCursorMoveRight(2); printf("████████");

	/* 6th line*/
  TCursorMoveXY(x/2 - 20, y/2 - 2 );
  TCursorMoveRight(2);printf("████"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(2);printf("██"); TCursorMoveRight(2);printf("████████");
  TCursorMoveRight(2); printf("██████");

	/* 7th line*/
  TCursorMoveXY(x/2 - 20, y/2 - 1 );
  printf("██"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(2);printf("██"); TCursorMoveRight(2);printf("██");TCursorMoveRight(2); printf("██");
	TCursorMoveRight(8); printf("██"); TCursorMoveRight(4); printf("██");

	/* 8th line*/
  TCursorMoveXY(x/2 - 20, y/2  );
	printf("██"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(2);printf("██"); TCursorMoveRight(2);printf("██");TCursorMoveRight(2); printf("██████");
  TCursorMoveRight(4); printf("██████");

	/* 9th line*/
  TCursorMoveXY(x/2 - 20, y/2 + 1 );
	printf("██"); TCursorMoveRight(4);printf("██"); TCursorMoveRight(2);printf("██"); TCursorMoveRight(2);printf("██");TCursorMoveRight(2); printf("██");
  TCursorMoveRight(8); printf("██"); TCursorMoveRight(2); printf("██");

	/* 10th line*/
  TCursorMoveXY(x/2 - 20, y/2 + 2 );
	TCursorMoveRight(2);printf("████"); TCursorMoveRight(6);printf("██"); TCursorMoveRight(4);printf("████████"); TCursorMoveRight(2);printf("██");
	TCursorMoveRight(4); printf("██");

	/* Updates the highscore if new highscore was achieved */
	if (getHighScore() < gameData -> score)
		saveHighScore(gameData -> score);

	/* Prints the text, score and highscore */
	
	TCursorMoveXY(x/2 - 24, y/2 + 4 );
  TChangeSettings(THIWHITE);
  printf("PRESS 'W'/'A'/'S'/'D or 'ARROWS' TO CONTINUE");
	TCursorMoveXY(x/2 - 8, y/2 + 5 );
	printf("PRESS 'E' TO EXIT");

	TCursorMoveXY(x/2 - 5, y/2 - height - 1  + 2 * height + 3 );	
  TChangeSettings(TBRED);
  printf("HIGHSCORE: %d", getHighScore());
	
	TCursorMoveXY(x/2 - 5, y/2 - height - 1  + 2 * height + 4);
  TChangeSettings(TBGREEN);
  printf("SCORE: %x", gameData -> score);

}








