#include <stdio.h>
#include <stdlib.h>
#include "deque.h"
#include "terminal.h"

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
	if (tail != NULL)
	{
		if (tail -> next)
		{
			next = tail -> next;
			next -> prev = NULL;
		}
		free(tail);
		return next;
	}
	return NULL;
}

/* Returns head */
snakePositionDeque * dequeAddFront(snakePositionDeque * head, int x, int y)
{
	snakePositionDeque * new = (snakePositionDeque*) malloc(sizeof(snakePositionDeque));
	new -> x = x;
	new -> y = y;
	new -> prev = head;
	new -> next = NULL;
	if ( head != NULL )
		head -> next = new;
	return new;
}

/* Retuns true if found and false if not found */
bool dequeFindPosition(snakePositionDeque * head, int x, int y)
{
	while (head)
	{
		if (head -> x == x && head -> y == y)
			return true;
		head = head -> prev;
	}
	return false;
}

/* Returns tail */
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




