#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gameData.h"
#include "conversion.h"

/* Using Murmurhash algorithm :( */
size_t checkSum(size_t n)
{
	n ^= n >> 16;
	n *= 0x85ebca6b;
	n ^= n >> 13;
	n *= 0xc2b2ae35;
	n ^= n >> 16;
  return n;
}

void saveHighScore(size_t score)
{
	FILE * pF = fopen("gameData.txt", "w");
	if (pF == NULL)
		return;
	fprintf(pF, "%zu;%zu\n", score, checkSum(score));
	fclose(pF);
}
int getHighScore()
{
	FILE * pF = fopen("gameData.txt", "r");
	if(pF == NULL)
		return 0;

	char * line = NULL;
	size_t size = 0;
	int len;
	
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
	
	len = getdelim(&line, &size, '\n', pF);
  if (len == -1)
	{
		fprintf(pF, "%d;%zu\n", 0, checkSum(0));
		free(line);
		fclose(pF);
		return 0;
	}

	line[len - 1] = '\0';
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
