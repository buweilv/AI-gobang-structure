/*
* 宏TWOUSERS和宏FIRST是不可以同时指定的
* 宏TWOUSERS表示的是当前的对战模式是双人对战
* 宏FIRST表示挑战擂主模式时，将用户的策略设置为先手策略
*/
#include "gobang.h"
#include "utils.h"
#include "AIStrategy.h"
#include <stdio.h>
#include <time.h>

// 默认情况下是挑战擂主模式，默认的先手是擂主策略，后手策略是user1Strategy
#if (!defined(TWOUSERS) && !defined(FIRST))
int first = AI;
void(*firstHandStrategy)(int*, int*) = ringKingStrategy;
void(*secondHandStrategy)(int*, int*) = user1Strategy;
#endif
#ifdef TWOUSERS // 双人对战时，user1Strategy是先手策略，user2Strategy是后手策略
int first = USER1;
void(*firstHandStrategy)(int*, int*) = user1Strategy;
void(*secondHandStrategy)(int*, int*) = user2Strategy;
#endif // TWOUSERS
#ifdef FIRST // 挑战擂主模式时，如果编译设置了FIRST宏，表示用户提交的策略是先手策略
int first = USER1;
void(*firstHandStrategy)(int*, int*) = user1Strategy;
void(*secondHandStrategy)(int*, int*) = ringKingStrategy;
#endif // FIRST

// 平局的情况下，允许两个棋手下棋总时间相差的阈值，此处暂且以秒来作为计时单位
double timeThreshold = 0; 
// 先手、后手下棋的总时间
double firstHandTime = 0;
double secondHandTime = 0;


int getBoardStatus()
{
	int i, j, iBak, jBak, winSide, ntimes;
	for (i = 0; i < boardLen; i++)
	{
		for (j = 0; j < boardLen; j++)
		{
			if (checkBoard[i][j] == BLACK || checkBoard[i][j] == WHITE)
			{
				winSide = checkBoard[i][j];
				iBak = i; jBak = j; ntimes = 1;
				// 以(i,j)为起点，存在向右的五子连珠
				while (jBak >= 0 && jBak < boardLen)
				{
					jBak++;
					if (checkBoard[iBak][jBak] == winSide) {
						ntimes++;
						if (ntimes == 5) {
							return winSide;
						}
					}
					else
						break;
				}
				iBak = i; jBak = j; ntimes = 1;
				// 以(i,j)为起点，存在向左的五子连珠
				while (jBak >= 0 && jBak < boardLen)
				{
					jBak--;
					if (checkBoard[iBak][jBak] == winSide) {
						ntimes++;
						if (ntimes == 5) {
							return winSide;
						}
					}
					else
						break;
				}
				iBak = i; jBak = j; ntimes = 1;
				// 以(i,j)为起点，存在向下的五子连珠
				while (iBak >= 0 && iBak < boardLen)
				{
					iBak++;
					if (checkBoard[iBak][jBak] == winSide) {
						ntimes++;
						if (ntimes == 5) {
							return winSide;
						}
					}
					else
						break;
				}
				iBak = i; jBak = j; ntimes = 1;
				// 以(i,j)为起点，存在向上的五子连珠
				while (iBak >= 0 && iBak < boardLen)
				{
					iBak--;
					if (checkBoard[iBak][jBak] == winSide) {
						ntimes++;
						if (ntimes == 5) {
							return winSide;
						}
					}
					else
						break;
				}
				iBak = i; jBak = j; ntimes = 1;
				// 以(i,j)为起点，存在向右下的五子连珠
				while (iBak >= 0 && iBak < boardLen && jBak >= 0 && jBak < boardLen)
				{
					iBak++; jBak++;
					if (checkBoard[iBak][jBak] == winSide) {
						ntimes++;
						if (ntimes == 5) {
							return winSide;
						}
					}
					else
						break;
				}
				iBak = i; jBak = j; ntimes = 1;
				// 以(i,j)为起点，存在向左下的五子连珠
				while (iBak >= 0 && iBak < boardLen && jBak >= 0 && jBak < boardLen)
				{
					iBak++; jBak--;
					if (checkBoard[iBak][jBak] == winSide) {
						ntimes++;
						if (ntimes == 5) {
							return winSide;
						}
					}
					else
						break;
				}
				iBak = i; jBak = j; ntimes = 1;
				// 以(i,j)为起点，存在向左上的五子连珠
				while (iBak >= 0 && iBak < boardLen && jBak >= 0 && jBak < boardLen)
				{
					iBak--; jBak--;
					if (checkBoard[iBak][jBak] == winSide) {
						ntimes++;
						if (ntimes == 5) {
							return winSide;
						}
					}
					else
						break;
				}
				iBak = i; jBak = j; ntimes = 1;
				// 以(i,j)为起点，存在向右上的五子连珠
				while (iBak >= 0 && iBak < boardLen && jBak >= 0 && jBak < boardLen)
				{
					iBak--; jBak++;
					if (checkBoard[iBak][jBak] == winSide) {
						ntimes++;
						if (ntimes == 5) {
							return winSide;
						}
					}
					else
						break;
				}
			} // if语句结束位置
		} //内层for循环结束位置
	}

	// 行至此处表示五子棋当前的局势不存在赢家，检查是否存在平局
	for (i = 0; i < boardLen; i++)
		for (j = 0; j < boardLen; j++)
			if (checkBoard[i][j] == EMPTY)
				goto end_judge;
	return DRAW;
end_judge:
	return CONTINUE;
}


// 判断当前的落子位置是否有效
int isValid(int row, int col, int side)
{
	if (checkBoard[row][col] != EMPTY || row >= boardLen || col >= boardLen) {
		status = STRATEGY_ERROR;
		// 日志记录当前落子无效的实际情况
		FILE *fp = fopen(FILE_NAME, "w");
		if (side == BLACK)
			fprintf(fp, "Black chess strategy Error, try to put chess on a invalid place(%d, %d)\n", row, col);
		else
			fprintf(fp, "White chess strategy Error, try to put chess on a invalid place(%d, %d)\n", row, col);
		fprintf(fp, "══════════════════════════\n");
		fclose(fp);
		return 0;
	}
	return 1;
}

void play(void (*strategy)(int*, int*), int side)
{
	// 落子的坐标
	int row, col;
	// 策略 -> 返回落子的位置
	clock_t start, end;
	start = clock();
	strategy(&row, &col);
	end = clock();
	double time = (double)(end - start); //经测试，Ubuntu16.04上显示精度为微秒级别
	if (timeThreshold != 0 && time / CLOCKS_PER_SEC > timeThreshold) { //当timeThreshold为0的时候，判断胜负依据时间的功能关闭
		if (side == BLACK)
			status = WHITE_WIN;
		else
			status = BLACK_WIN;
	}
	else { // 在timeThreshold范围内 or 没有超时
		if (isValid(row, col, side)) {
			put(row, col, side);
			if (side == BLACK)
				printf("BLACK chess on (%d,%d), took %lf micro secs\n", row, col, time);
			if (side == WHITE)
				printf("WHITE chess on (%d,%d), took %lf micro secs\n", row, col, time);
			status = getBoardStatus();
		}
	}
}

void firstHand()
{
	// 黑棋先手
	play(firstHandStrategy, BLACK);
}

void secondHand()
{
	// 白棋后手
	play(secondHandStrategy, WHITE);
}
