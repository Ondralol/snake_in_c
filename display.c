#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "display.h"

void displayMenu(size_t currentScore)
{
  for (int i = 0; i < 100; i++) printf("\n");
  printf("PRESS 'S' TO START THE GAME\n");
  printf("PRESS 'E' TO END THE GAME");
}

bool showMenu(size_t currentScore)
{
  int c = 0;
  while (true)
  {
    displayMenu(currentScore);
 
    c = getchar();
    if ( c == 'e' || c == 'E')
      return 0;
    else if ( c == 's' || c == 'S')
      return 1;
  
  
  }

  return 0;
}


void displayGame(size_t * currentScore, size_t width, size_t height )
{
  
  for (int i = 0; i < 100; i++) printf("\n");
  
  /* Game borders */
  for (int i = 0; i < width; i ++)
  {
    if (i == 0)
      printf("┌");
    else if (i == width - 1)
      printf("┐");
    else
      printf("─");
  }
  printf("\n");

  for (int i = 0; i < height - 2; i ++)
  {
    printf("│");
    for (int j = 0; j < width -2; j++)
    {
      //printf(" ");
      if ( i == 10 && j == 10 )
        printf("%zu", *currentScore);
      else
        printf(" ");
    }
    printf("│\n");
  }

  for (int i = 0; i < width; i ++)
  {
    if (i == 0)
      printf("└");
    else if (i == width -1)
      printf("┘");
    else
      printf("─");
  }
  printf("\n");

  /* 24FPS */
  usleep(41667);
}

bool showGame (size_t * currentScore, size_t width, size_t height)
{
  while (true)
  {
    displayGame(currentScore, width, height);
    //(*currentScore) ++;
  }
  return 0;
}

