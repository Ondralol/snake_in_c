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

extern bool signalVal;

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
		signal(SIGWINCH, &windowResize);
		if ( signalVal == 1 )
			displayMenu();
		
		
		c = getchar();
		switch (c)
		{
			case 'W':
			case 'w':
				return 1;
			
			case 'A':
			case 'a':
				return 1;

			case 'S':
			case 's':
				return 1;

			case 'D':
			case 'd':
				return 1;

			case 'E':
			case 'e':
				return 0;
		}
	}

	return 0;
}

int gameLogic(size_t x, size_t y, size_t * score)
{
	snake gameData;
	
	gameData.currentDirection = DOWN;
	gameData.head.x = 0;
	gameData.head.y = 0;
	gameData.tail.x = 0;
	gameData.tail.y = 0;



	displayGame(x, y, score);
	int c = 0;
	size_t timer = 0;
	while (true)
	{
		timer ++;
		signal(SIGWINCH, &windowResize);
		if ( signalVal == 1)
			displayGame(x, y, score);
			

		if ( timer == 14 )
		{
			timer = 0;
			displaySnake(x, y, &gameData);
		}
		c = getchar();
		switch (c)
		{
			case 'W':
			case 'w':
				if ( gameData.currentDirection != UP )
				{
					gameData.currentDirection = UP;
					//usleep(20000);
					//displaySnake(x, y, &gameData);
					//usleep(20000);
				}
				break;

			case 'A':
			case 'a':
				if ( gameData.currentDirection != LEFT )
				{
					gameData.currentDirection = LEFT;
					//usleep(20000);
					//displaySnake(x, y, &gameData);
					//usleep(20000);
				}
				break;

			case 'S':
			case 's':
				if ( gameData.currentDirection != DOWN )
				{
					gameData.currentDirection = DOWN;
					//usleep(20000);
					//displaySnake(x, y, &gameData);
					//usleep(20000);
				}
				break;

			case 'D':
			case 'd':
				if ( gameData.currentDirection != RIGHT )
				{
					gameData.currentDirection = RIGHT;
					//usleep(20000);
					//displaySnake(x, y, &gameData);
					//usleep(20000);
				}
				break;

			case 'E':
			case 'e':
				return 0;

			case 'P':
			case 'p':
				return 1;
		}
		fflush(stdout);
		usleep(20000);
	}
	
	return 0;
}

