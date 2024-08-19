#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gameData.h"
#include "conversion.h"

/* Using Murmurhash algorithm */
size_t checkSum(size_t n)
{
	n ^= n >> 16;
	n *= 0x85ebca6b;
	n ^= n >> 13;
	n *= 0xc2b2ae35;
	n ^= n >> 16;
  return n;
}

/* Using simple checksum so that user cannot change the score */
void saveHighScore(size_t score)
{
	FILE * pF = fopen("gameData.txt", "w");
	if (pF == NULL)
		return;
	fprintf(pF, "%zu;%zu\n", score, checkSum(score));
	fclose(pF);
}

/* Tries to read highscore from file, checks for errors and checksum, if there are any problems, highscore is set to 0 */
int getHighScore()
{
	FILE * pF = fopen("gameData.txt", "r");
	if(pF == NULL)
		return 0;

	char * line = NULL;
	size_t size = 0;
	int len;

	/* Reads until delimeter */
	len = getdelim(&line, &size, ';', pF);
	if (len == -1)
	{
		fprintf(pF, "%d;%zu\n", 0, checkSum(0));
		free(line);
		fclose(pF);
		return 0;
	}
	line[len - 1] = '\0';

	size_t score;

	/* If failed to read */
	if (!strToNum(&score, line))
	{
		fprintf(pF, "%d;%zu\n", 0, checkSum(0));
		free(line);
		fclose(pF);
		return 0;
	}
	
	/* Reads until delimeter */
	len = getdelim(&line, &size, '\n', pF);
  /* If failed to read*/
	if (len == -1)
	{
		fprintf(pF, "%d;%zu\n", 0, checkSum(0));
		free(line);
		fclose(pF);
		return 0;
	}

	line[len - 1] = '\0';
	
	/* Checks if the checkSum is correct */
	
	size_t check;
	strToNum(&check, line);
	free(line);
	if (check != checkSum(score))
	{
		fprintf(pF, "%d;%zu\n", 0, checkSum(0));
		return 0;
	}
	
	fclose(pF);
	return score;
}
