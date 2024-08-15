#include <stdio.h>

#define NORMAL "\x1B[0m"
#define RED    "\x1B[1;31m"
#define clear()  printf("\x1B[2J")


#define move_cursour(X, Y) printf("\033[%d;%dH", X, Y)

int main ()
{
  printf("%sHello world\n%s", RED, NORMAL);
  //clear();
  move_cursour(1,1);
  printf("10");
  return 0;
}
