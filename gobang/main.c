#include <stdio.h>
#include "gobang.h"
#include "utils.h"

int checkBoard[boardLen][boardLen];
int status = CONTINUE;
long comScore[boardLen][boardLen];
long humScore[boardLen][boardLen];


int main()
{
	initCheckBoard();
	
	while (status == CONTINUE) {
		firstHand(); 
		if (status == CONTINUE)
			secondHand(); 
	}
	output(); 
	
    return 0;
}
