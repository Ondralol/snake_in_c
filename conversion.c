#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "conversion.h"

bool strToNum(size_t * value, char * str )
{
	//printf("Val: %s\n", str);
	bool seenDigit = 0;
	size_t val = 1;
	size_t newValue = 0; 
	size_t len = strlen(str);
	for ( int i = len - 1; i >=0 ; i -- )
	{
		if ( !isdigit(str[i]) )
			break;
		newValue += ( str[i] - '0') * val;
		val *= 10;
		seenDigit = 1;
	}
	if (!seenDigit)
		return 0;
	
	*value = newValue;
	return 1;
}


