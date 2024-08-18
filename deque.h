#pragma once
#include <stdbool.h>

/* Represents directions */
typedef enum dir
{
  UP, DOWN, RIGHT, LEFT
} direction;

/* Using deque to represent tile positions */
/* X, Y corresponds to tile position */
typedef struct snakePosDeque
{
	int x;
	int y;
	struct snakePosDeque * next;
	struct snakePosDeque * prev;
} snakePositionDeque;

typedef struct snake
{
  direction currentDirection;
  snakePositionDeque * head;
  snakePositionDeque * tail;
	int appleX;
	int appleY;
	size_t colour;
} snake;

/* Deque */

void dequeFree(snakePositionDeque * head);

snakePositionDeque * dequePopBack(snakePositionDeque * tail);

snakePositionDeque * dequeAddFront(snakePositionDeque * head, int x, int y);

snakePositionDeque * dequeTail(snakePositionDeque * head);

bool dequeFindPosition(snakePositionDeque * head, int x, int y);
