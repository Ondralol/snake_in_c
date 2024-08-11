#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "conversion.h"

void strToNum(size_t * value, char * str )
{
  size_t val = 1;
  size_t newValue = 0; 
  size_t len = strlen(str);
  for ( int i = len - 1; i >=0 ; i -- )
  {
    if ( !isdigit(str[i]) )
      return;
    newValue += ( str[i] - '0') * val;
    val *= 10;
  }
  *value = newValue;
  printf("%zu\n", *value);
}
