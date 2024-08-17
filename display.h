#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct pos
{
	int x;
	int y;
} position;


typedef enum dir
{
	UP, DOWN, RIGHT, LEFT
} direction;

typedef struct snake
{
	direction currentDirection;
	position head;
	position tail;
} snake;


void displayTiles(size_t, size_t, size_t, size_t);

void windowResize();

void displayBorders(const char * colour);

void displayMenu();

void displayGame(size_t width, size_t height, size_t * score);

void displaySnake(size_t width, size_t height, snake * gameData);
