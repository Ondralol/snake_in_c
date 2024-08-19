#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include "game.h"
#include "display.h"
#include "deque.h"
#include "terminal.h"

/* TODO */ 

/*
typedef struct Settings
{
	int x;
	int y;
} Settings;
*/

extern int signalVal;

int menuLogic(size_t score);
int gameLogic(size_t x, size_t y, size_t * score);
int gameOverLogic(size_t width, size_t height, snake * gameData);

void runGame(size_t width, size_t height)
{
		size_t score = 0;
		int outputSignal = 0;
		
		outputSignal = menuLogic(score);
    if (outputSignal == 0 )
    	return;
		while (true)
		{
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
		if ( signalVal == 2 )
			return 0;

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

int pauseLogic(size_t width, size_t height, snake * gameData)
{
	bool screenChange = false;
	int x, y;
  TGetTerminalSize(&x,&y);
	displayPause(width, height, gameData);
	int c;

	while (true)
  {
    if ( signalVal == 2 )
      return -1;

		signal(SIGWINCH, &windowResize);
    if ( signalVal == 1 )
		{
			screenChange = true;
			usleep(20000);
			displayGame(width, height);
  		displaySnakeAll(gameData, width, height);
  		displaySnakeTile(width, height, gameData -> appleX, gameData -> appleY, 255,0,0);
			displayPause(width, height, gameData);
			fflush(stdout);
			usleep(200000);
		}
    c = getchar();
    switch (c)
    {
      case 'P':
			case 'p':
      usleep(50000);
			if ( screenChange )
				return 1;
			else
				return 0;

      case 'E':
      case 'e':
        return -1;
    }
  }

}

int gameOverLogic(size_t width, size_t height, snake * gameData)
{
  int x, y;
  TGetTerminalSize(&x,&y);
  displayGameOver(width, height, gameData);
  int c;

  while (true)
  {
    if ( signalVal == 2 )
      return 0;

    signal(SIGWINCH, &windowResize);
    if ( signalVal == 1 )
    {
      usleep(20000);
      displayGame(width, height);
      displaySnakeAll(gameData, width, height);
      displaySnakeTile(width, height, gameData -> appleX, gameData -> appleY, 255,0,0);
      displayGameOver(width, height, gameData);
      fflush(stdout);
      usleep(200000);
    } 
    c = getchar();
    
		 if (c == '\x1B')
    {
      if (getchar() == '[')
      {
        switch(getchar())
        {
          case 'A':
          case 'B':
          case 'C':
          case 'D':
          c = 'A'; break;
        }
      }
    }

		switch (c)
    {
      case 'w':
      case 'W':
      case 'a':
			case 'A':
			case 's':
			case 'd':
			case 'D':
				usleep(50000);
      	return 1;

      case 'E':
      case 'e':
        return 0;
    }
  }

}


/* XY is width and height */
int gameLogic(size_t width, size_t height,size_t * score)
{
	snake gameData;
	//TODO RANDOM
	gameData.currentDirection = DOWN;
	gameData.head = NULL;
	gameData.tail = NULL;
	gameData.colour = 254;
	gameData.appleX = -1;
	gameData.appleY = -1;
	gameData.score = 0;

	displayGame(width, height);
	displaySnake(width, height, &gameData); //maybe remove
	int c = 0;
	int result;
	size_t timer = 0;
	bool breakFlag = 0;
	while (true)
	{
		if ( signalVal == 2 )
    {
			dequeFree(gameData.head);
			return 0;
		}
		timer ++;
		signal(SIGWINCH, &windowResize);
		if ( signalVal == 1)
		{
			displayGame(width, height);
			displaySnakeAll(&gameData, width, height);
			displaySnakeTile(width, height, gameData.appleX, gameData.appleY, 255,0,0);
			fflush(stdout);
			usleep(200000);
			//signalVal = 0;
		}

		if ( timer == 10 )
		{
			timer = 0;
			if ( !displaySnake(width, height, &gameData) )
				breakFlag = 1;;
		}
		c = getchar();
		if (c == '\x1B')
		{
			if (getchar() == '[')
			{
				switch(getchar())
				{
					case 'A':
						c = 'W'; break;
					case 'B':
            c = 'S'; break;
					case 'C':
            c = 'D'; break;
					case 'D':
            c = 'A'; break;
				}
			}
		}

		switch (c)
		{
			case 'W':
			case 'w':
				if ( gameData.currentDirection != UP && gameData.currentDirection != DOWN)
				{
					gameData.currentDirection = UP;
					usleep(5000 * (10 - timer));
					if ( !displaySnake(width, height, &gameData) )
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
					if ( !displaySnake(width, height, &gameData) )
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
					if ( !displaySnake(width, height, &gameData) )
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
					if ( !displaySnake(width, height, &gameData) )
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
				clearBuffer();
				if ( (result = pauseLogic(width, height, &gameData)) == 1 )
				{
					displayGame(width, height);
     		 	displaySnakeAll(&gameData, width, height);
      		displaySnakeTile(width, height, gameData.appleX, gameData.appleY, 255,0,0);
					fflush(stdout);
      		usleep(200000);

				}
				else if (result == 0)
				{	
					int x, y;
  				TGetTerminalSize(&x,&y);
					displayTiles(width, height, x, y);
					displaySnakeAll(&gameData, width, height);
          displaySnakeTile(width, height, gameData.appleX, gameData.appleY, 255,0,0);
          fflush(stdout);
          usleep(200000);
				}
				else
				{
					dequeFree(gameData.head);
					return 0;
				}
				;
		}
		if ( breakFlag )
		{
			sleep(1);
			clearBuffer();
			bool result = gameOverLogic(width, height, &gameData);
			dequeFree(gameData.head);
			clearBuffer();
			//sleep(1);
			return result;
		}
		fflush(stdout);
		usleep(40000);
	}
	
	return 0;
}

