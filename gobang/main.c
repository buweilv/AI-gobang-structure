#include <stdio.h>
#include "gobang.h"
#include "test.h"
#include "utils.h"

int checkBoard[boardLen][boardLen];
int status = CONTINUE;


int main()
{
	initCheckBoard();
	/*
	while (status == CONTINUE) {
		firstHand(); 
		if (status == CONTINUE)
			secondHand(); 
	}
	output(); 
	*/
    //matchTest();
	testEvaluate();
    return 0;
}
