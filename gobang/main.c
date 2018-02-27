#include <stdio.h>
#include "gobang.h"
#include "test.h"
#include "utils.h"

int checkBoard[boardLen][boardLen];
int status = CONTINUE;
long comScore[boardLen][boardLen];
long humScore[boardLen][boardLen];


int main()
{
	initCheckBoard();
	
	if (first == AI)
		printf("first is AI\n");
	if (first == USER1)
		printf("first is USER1\n");
	while (status == CONTINUE) {
		firstHand(); 
		if (status == CONTINUE)
			secondHand(); 
	}
	output(); 
	
    return 0;
}
