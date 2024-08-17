#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "deque.h"

void displayTiles(size_t, size_t, size_t, size_t);

void windowResize();

void displayBorders(const char * colour);

void displayMenu();

void displayGame(size_t width, size_t height, size_t * score);

void displaySnake(size_t width, size_t height, snake * gameData);
