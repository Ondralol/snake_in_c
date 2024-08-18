#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include "game.h"
#include "display.h"
#include "deque.h"

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
int gameOverLogic(size_t * score);

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
			else
				displayGameOver();
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

void clearBuffer()
{
	int c;
	while ( (c = getchar()) != EOF );
}

/* XY is width and height */
int gameLogic(size_t x, size_t y, size_t * score)
{
	snake gameData;
	//TODO RANDOM
	gameData.currentDirection = DOWN;
	gameData.head = NULL;
	gameData.tail = NULL;
	gameData.colour = 254;
	gameData.appleX = -1;
	gameData.appleY = -1;

	displayGame(x, y, score);
	displaySnake(x, y, &gameData); //maybe remove
	int c = 0;
	size_t timer = 0;
	bool breakFlag = 0;
	while (true)
	{
		timer ++;
		signal(SIGWINCH, &windowResize);
		if ( signalVal == 1)
		{
			displayGame(x, y, score);
			displaySnakeAll(&gameData, x, y);
			fflush(stdout);
			usleep(200000);
			//signalVal = 0;
		}

		if ( timer == 10 )
		{
			timer = 0;
			if ( !displaySnake(x, y, &gameData) )
				breakFlag = 1;;
		}
		c = getchar();
		switch (c)
		{
			case 'W':
			case 'w':
				if ( gameData.currentDirection != UP && gameData.currentDirection != DOWN)
				{
					gameData.currentDirection = UP;
					usleep(5000 * (10 - timer));
					if ( !displaySnake(x, y, &gameData) )
        		breakFlag = 1;
					//usleep(20000);
					timer = 0;	
					clearBuffer();
				}
				break;

			case 'A':
			case 'a':
				if ( gameData.currentDirection != LEFT && gameData.currentDirection != RIGHT)
				{
					gameData.currentDirection = LEFT;
					usleep(5000 * (10 - timer));
					if ( !displaySnake(x, y, &gameData) )
						breakFlag = 1;
					//usleep(20000);
					timer = 0;
					clearBuffer();
				}
				break;

			case 'S':
			case 's':
				if ( gameData.currentDirection != DOWN && gameData.currentDirection != UP)
				{
					gameData.currentDirection = DOWN;
					usleep(5000 * (10 - timer));
					if ( !displaySnake(x, y, &gameData) )
						breakFlag = 1;
					//usleep(20000);
					timer = 0;
					clearBuffer();
				}
				break;

			case 'D':
			case 'd':
				if ( gameData.currentDirection != RIGHT && gameData.currentDirection != LEFT)
				{
					gameData.currentDirection = RIGHT;
					usleep(5000 * (10 - timer) );
					if ( !displaySnake(x, y, &gameData) )
						breakFlag = 1;
					//usleep(20000);
					timer = 0;
					clearBuffer();
				}
				break;

			case 'E':
			case 'e':
				dequeFree(gameData.head);
				return 0;

			case 'P':
			case 'p':
				sleep(1000);
				;
		}
		if ( breakFlag )
		{
			dequeFree(gameData.head);
			printf("GAME OVER");
			sleep(1);
			return 1;
		}
		fflush(stdout);
		usleep(40000);
	}
	
	return 0;
}

