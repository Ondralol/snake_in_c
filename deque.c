#include <stdlib.h>
#include "deque.h"


void dequeFree(snakePositionDeque * head)
{
	snakePositionDeque * prev;
	while (head)
	{
		prev = head;
		head = head -> prev;
		free(prev);
	}
}

/* Returns tail */
snakePositionDeque * dequePopBack(snakePositionDeque * tail)
{
	snakePositionDeque * next;
	if ( tail != NULL)
	{
		if ( tail -> next )
		{
			next = tail -> next;
			next -> prev = NULL;
		}
		free(tail);
		return next;
	}
	return NULL;
}

snakePositionDeque * dequeAddFront(snakePositionDeque * head, int x, int y)
{
	snakePositionDeque * new = (snakePositionDeque*) malloc(sizeof(snakePositionDeque));
	new -> x = x;
	new -> y = y;
	new -> prev = head;
	new -> next = NULL;
	return new;
}

bool dequeFindPosition(snakePositionDeque * head, int x, int y)
{
	while ( head )
	{
		if (head -> x == x && head -> y == y)
			return true;
		head = head -> next;
	}
	return false;
}

snakePositionDeque * dequeTail(snakePositionDeque * head)
{
	snakePositionDeque * prev = head;
	while(head)
	{
		prev = head;
		head = head -> prev;
	}
	return prev;
}
