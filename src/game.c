#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include "game.h"
#include "display.h"
#include "deque.h"
#include "terminal.h"


extern int signalVal;

int menuLogic(size_t score);
int gameLogic(size_t x, size_t y, size_t * score);
int gameOverLogic(size_t width, size_t height, snake * gameData);

/* Loop that runs the game */
void runGame(size_t width, size_t height)
{
		size_t score = 0;
		int outputSignal = 0;
			
		outputSignal = menuLogic(score);
    /* Exits the game if 'e' is pressed in the menu */
		if (outputSignal == 0 )
    	return;
		while (true)
		{
			outputSignal = gameLogic(width, height, &score);
			/* Exits the game if 'e' is pressed in the game screen*/
			if (outputSignal == 0 )
				return;
		}

}

/* Input logic for the menu */
int menuLogic(size_t score)
{
	displayMenu();
	int c = 0;
	while (true)
	{
		/* If ctrl C was pressed */
		if ( signalVal == 2 )
			return 0;
		
		/* Checks for window resize */
		signal(SIGWINCH, &windowResize);
		if ( signalVal == 1 )
			displayMenu();
			
		c = getchar();
		/* Arrows input handling */
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
		
		/* Input handling */
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

/* Input logic for paused game */
int pauseLogic(size_t width, size_t height, snake * gameData)
{
	/* Using this variable so that I only change the screen when necessary */
	bool screenChange = false;
	int x, y;
  TGetTerminalSize(&x,&y);
	displayPause(width, height, gameData);
	int c;

	while (true)
  {
    /* If ctrl C was pressed */
		if ( signalVal == 2 )
      return -1;

		/* Checks for window resizing */
		signal(SIGWINCH, &windowResize);
    if ( signalVal == 1 )
		{
			/* Displaying all information thats needed */
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

		/* Handling input*/
    switch (c)
    {
      /* Resumes the game if 'p' is pressed*/
			case 'P':
			case 'p':
      usleep(50000);
			if ( screenChange )
				return 1;
			else
				return 0;
			
			/* Exits the game if 'e' is pressed*/
      case 'E':
      case 'e':
        return -1;
    }
  }

}

/* Handles input logic for game over */
int gameOverLogic(size_t width, size_t height, snake * gameData)
{
  int x, y;
  TGetTerminalSize(&x,&y);
  displayGameOver(width, height, gameData);
  int c;
	fflush(stdout);
	usleep(750000);
	clearBuffer();
	while (true)
  {
    /* If 'CTRL C' was pressed*/
		if ( signalVal == 2 )
      return 0;

    /* Checks if window was resized and handles displaying the game*/
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
    /* Handles arrows input */
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

		/* Handles normal input */
		switch (c)
    {
      case 'w':
      case 'W':
      case 'a':
			case 'A':
			case 's':
			case 'd':
			case 'D':
      	return 1;

      case 'E':
      case 'e':
        return 0;
    }
  }

}


/* Handles input logic for the main game */
int gameLogic(size_t width, size_t height,size_t * score)
{
	/* Sets default settings just to be safe */
	snake gameData;
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
	bool breakFlag = 0; // if user pressed 'e' to exit the game
	while (true)
	{
		/* If 'CTRL C' was pressed*/
		if ( signalVal == 2 )
    {
			dequeFree(gameData.head);
			return 0;
		}

		/* If window was resized */	
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
		
		/* Using "timer" with usleep so that I can update the game screen to my needs */
		timer ++;
		if ( timer == 10 )
		{
			timer = 0;
			if ( !displaySnake(width, height, &gameData) )
				breakFlag = 1;;
		}

		c = getchar();
		/* Arrows input */

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
		
		/* Handles normal input, basically updates the snakes direction and displays new head and apple and clears the buffer*/
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
					timer = 0;
					clearBuffer();
				}
				break;
			
			/* Exits the game */
			case 'E':
			case 'e':
				dequeFree(gameData.head);
				return 0;
			
			/* Pauses the game */
			case 'P':
			case 'p':
				clearBuffer();
				/* Displays the pause menu and after exiting menu, if window size wasn't changed, only displays the snake and the board */
				if ( (result = pauseLogic(width, height, &gameData)) == 1 )
				{
					displayGame(width, height);
     		 	displaySnakeAll(&gameData, width, height);
      		displaySnakeTile(width, height, gameData.appleX, gameData.appleY, 255,0,0);
					fflush(stdout);
      		usleep(200000);

				}
				/* Displays the pause menu and if the display size was changed, displays everything */
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
				/* If 'e' was pressed in the pause menu, ends the game */
				else
				{
					dequeFree(gameData.head);
					return 0;
				}
				;
		}
		/* If 'e' was pressed during the main game loop */
		if ( breakFlag )
		{
			clearBuffer();
			bool result = gameOverLogic(width, height, &gameData);
			dequeFree(gameData.head);
			clearBuffer();
			return result;
		}
		fflush(stdout);
		usleep(40000);
	}
	
	return 0;
}

