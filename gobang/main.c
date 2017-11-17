#include <stdio.h>
#include "gobang.h"
#include "test.h"

int checkBoard[boardLen][boardLen];
int status = CONTINUE;


int main()
{
	/*
	initCheckBoard();
	while (status == CONTINUE) {
		firstHand(); 
		if (status == CONTINUE)
			secondHand(); 
	}
	output(); 
	*/
	//outputTest();
	//judgeTest();
	battleModeTest();
    return 0;
}