#include "test.h"
#include "gobang.h"
#include "AIStrategy.h"
#include "utils.h"
#include <stdio.h>

static enum {MIN_PLAYER, MAX_PLAYER};
/*
* 测试将最终的棋盘输出到文件中的效果
* 测试用例：
* 1. 棋盘上存在黑白棋
* 2. 棋子位于边线上，甚至在四个角上
* 3. 棋子连起来之后的打印效果
*/
void outputTest()
{
	checkBoard[0][0] = BLACK;
	checkBoard[0][1] = BLACK;
	checkBoard[0][2] = WHITE;
	checkBoard[0][3] = WHITE;
	checkBoard[1][4] = BLACK;
	checkBoard[3][boardLen - 1] = BLACK;
	checkBoard[3][boardLen - 2] = BLACK;
	checkBoard[boardLen-1][3] = WHITE;
	output();
}

/*
* 测试裁判功能能否正常工作
* 1. 功能性测试：黑子或白子胜（横、竖、斜1、斜2）
* 2. 功能性测试：平局（黑子113，白子112） 两者用时在总时间阈值误差内（平局），两者用时在总时间阈值误差外（时间短的选手获胜）
* 3. 异常性测试：棋手落子在界外 or 棋手落子在已经落子的位置
*/
void judgeTest()
{
	int i;
	// 横-win
	/*
	initCheckBoard();
	for (i = 0; i < 4; i++) {
		checkBoard[0][i] = BLACK;
		checkBoard[1][i] = WHITE;
	}
	firstHandTime = 20000;
	secondHandTime = 150000;
	judge(0, 4, BLACK, 20);
	output();
	*/
	// 竖-win
	/*
	initCheckBoard();
	for (i = 0; i < 4; i++) {
		checkBoard[i][0] = BLACK;
		checkBoard[i][1] = WHITE;
	}
	firstHandTime = 20000;
	secondHandTime = 150000;
	judge(4, 0, BLACK, 20);
	output();
	*/
	// 反斜-win
	/*
	initCheckBoard();
	checkBoard[0][0] = BLACK; checkBoard[0][1] = BLACK;
	checkBoard[1][0] = BLACK; checkBoard[1][2] = BLACK; checkBoard[2][1] = BLACK;
	for (i = 1; i <= 4; i++)
		checkBoard[i][i] = WHITE;
	firstHandTime = 20000;
	secondHandTime = 150000;
	judge(5, 5, WHITE, 20);
	output();
	*/
	// 正斜-win
	
	initCheckBoard();
	checkBoard[0][0] = BLACK; checkBoard[0][1] = BLACK;
	checkBoard[1][0] = BLACK; checkBoard[1][2] = BLACK; checkBoard[2][1] = BLACK;
	for (i = 0; i < 4; i++)
		checkBoard[4-i][i] = WHITE;
	firstHandTime = 20000;
	secondHandTime = 150000;
	judge(0, 4, WHITE, 20);
	output();
	
	// 平局-误差在阈值时间内部
	/*
	// 偶数行的形式
	int evenLine[boardLen] = {BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK};
	// 奇数行的形式
	int oddLine[boardLen] = {WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE};
	initCheckBoard();
	for (int i = 0; i < boardLen; i++) {
		if (i % 2) { //奇数行
			for (int j = 0; j < boardLen; j++)
				checkBoard[i][j] = oddLine[j];
		}
		else {
			for (int j = 0; j < boardLen; j++)
				checkBoard[i][j] = evenLine[j];
		}
	}
	checkBoard[boardLen - 1][boardLen - 1] = EMPTY;
	firstHandTime = 20000;
	secondHandTime = 150000;
	judge(boardLen-1, boardLen-1, BLACK, 20);
	output();
	*/
	/*
	// 平局，但是一方时间过长，被判负
	initCheckBoard();
	for (int i = 0; i < boardLen; i++) {
		if (i % 2) { //奇数行
			for (int j = 0; j < boardLen; j++)
				checkBoard[i][j] = oddLine[j];
		}
		else {
			for (int j = 0; j < boardLen; j++)
				checkBoard[i][j] = evenLine[j];
		}
	}
	checkBoard[boardLen - 1][boardLen - 1] = EMPTY;
	firstHandTime = 200000000;
	secondHandTime = 15000000;
	judge(boardLen - 1, boardLen - 1, BLACK, 200000);
	output();
	*/
	// 棋子落在界外
	/*
	initCheckBoard();
	judge(0, boardLen, BLACK, 12);
	output();
	*/
	// 棋子落在已经下过的棋子上
	/*
	initCheckBoard();
	checkBoard[10][10] = BLACK;
	firstHandTime = 12;
	judge(10, 10, WHITE, 12);
	output();
	*/
}

// 查看以-DFIRST -DTWOUSERS 以及默认gcc编译选项编译运行之后
// 棋盘最终的结果形式
void battleModeTest()
{
	firstHand();
	//secondHand();
	output();
}

/*
* 测试字符串匹配情况
*/

void matchTest()
{
	printf("aabbccabaacaabb has %d aa\n", countMatch( "aa", "aabbccabaacaabb"));
	printf("abcdsedad has %d aa\n", countMatch("aa", "abcdsedad"));
	printf("aabbbbbbsss has %d aa\n", countMatch("aa", "aabbbbbbsss"));
	printf("1111111 has %d 11\n", countMatch("11", "1111111"));
	printf("2111112 has %d 11111\n", countMatch("11111", "2111112"));
}

void testEvaluate()
{
	int i;
	initCheckBoard();
	checkBoard[0][0] = BLACK; checkBoard[0][1] = BLACK;
	checkBoard[1][0] = BLACK; checkBoard[1][2] = BLACK; checkBoard[2][1] = BLACK;
	for (i = 0; i < 4; i++)
		checkBoard[4 - i][i] = WHITE;
	firstHandTime = 20000;
	secondHandTime = 150000;
	judge(0, 4, WHITE, 20);
	output();
	long re = evaluate(MAX_PLAYER, WHITE);
	printf("score: %ld\n",re);
}
