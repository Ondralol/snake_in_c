#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "deque.h"

void displayTiles(size_t, size_t, size_t, size_t);

void windowResize();

void displayBorders(const char * colour);

void displayMenu();

void displaySnakeAll(snake * gameData, int width, int height);

void displaySnakeTile(int width, int height, int tileX, int tileY, int r, int g, int b);

bool displaySnake(size_t width, size_t height, snake * gameData);

void displayGame(size_t width, size_t height);

void displayStartGame(size_t width, size_t height, snake * gameData);

void displayPause(size_t width, size_t height, snake * gameData);

void displayGameOver(size_t width, size_t height, snake * gameData);
