#include <stdbool.h>

typedef struct position
{
  int x;
  int y;
} position;

void displayMenu();

void displayGame(size_t * currentScore, size_t width, size_t height, position pos );

bool showGame (size_t * currentScore, size_t widht, size_t height);
