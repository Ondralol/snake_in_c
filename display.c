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


void displayGame(size_t * currentScore, size_t width, size_t height, position pos )
{
  int x = pos.x;
  int y = pos.y;
  

  for (int i = 0; i < 100; i++) printf("\n");

  //printf("\033[44m");
  printf(" SCORE: %zu\n", *currentScore);


  /* Game borders */
  for (int i = 0; i < width; i ++)
  {
    if (i == 0)
      printf("╔");
    else if (i == width - 1)
      printf("╗");
    else
      printf("═");
  }
  printf("\n");

  for (int i = 0; i < height - 2; i ++)
  {
    printf("║");
    for (int j = 0; j < width -2; j++)
    {
      //printf(" ");
      if ( i == y && j == x )
        printf("▄");
      else
        printf(".");
    }
    printf("║\n");
  }

  for (int i = 0; i < width; i ++)
  {
    if (i == 0)
      printf("╚");
    else if (i == width -1)
      printf("╝");
    else
      printf("═");
  }
  printf("\n");

  /* 24FPS */
  //usleep(667);
}

bool showGame (size_t * currentScore, size_t width, size_t height)
{
  position pos;
  pos.x = width/2;
  pos.y = height/2;
  int c;

  while (true)
  {
    displayGame(currentScore, width, height, pos);
    c = getchar();
    switch (c)
    {
      case 'w':
        pos.y --; break;
      case 's':
        pos.y ++; break;
      case 'a':
        pos.x --; break;
      case 'd':
        pos.x ++; break;
      //case 'e':
        //return 0;
    }
    //pos.y --;
  }
  return 0;
}

