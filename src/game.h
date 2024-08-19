#pragma once
#include <stddef.h>
#include "display.h"
#include "deque.h"

void runGame(size_t , size_t );

int menuLogic(size_t score);

int gameLogic(size_t, size_t, size_t * score);

int pauseLogic(size_t, size_t, snake *);

int gameOverLogic(size_t width, size_t height, snake * gameData);

