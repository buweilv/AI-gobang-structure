#include "AIStrategy.h"
#include "gobang.h"

void user1Strategy(int *row, int *col)
{
	*row = boardLen - 1;
	*col = boardLen - 1;
}

void user2Strategy(int *row, int *col)
{
	*row = 1;
	*col = 1;
}

void ringKingStrategy(int *row, int *col)
{
	*row = 0;
	*col = 0;
}