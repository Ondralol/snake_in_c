#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "conversion.h"

/* Converts string to number, returns "true" if string contains at least one digit and "false" if it doesn't contain any number */
bool strToNum(size_t * value, char * str )
{
	bool seenDigit = 0;
	
	size_t mult = 1;
	size_t newValue = 0; 
	
	size_t len = strlen(str);
	for ( int i = len - 1; i >=0 ; i -- )
	{
		if ( !isdigit(str[i]) )
			break;
		newValue += ( str[i] - '0') * mult;
		mult *= 10;
		seenDigit = 1;
	}

	if (!seenDigit)
		return 0;
	
	*value = newValue;
	return 1;
}


