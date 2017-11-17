#include "gobang.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>

// 平局的情况下，允许两个棋手下棋总时间相差的阈值，此处暂且以秒来作为计时单位
double totalTimeThreshold = 10; 
// 先手、后手下棋的总时间
double firstHandTime = 0;
double secondHandTime = 0;


// 裁判先判断落子是否正确；再判断局势
// 注意，此处的精度太小的话很有可能溢出
void judge(int row, int col, int side, double time)
{
	// 判断落子是否正确
	if (checkBoard[row][col] != EMPTY || row >= boardLen || col >= boardLen) {
		status = STRATEGY_ERROR;
		FILE *fp = fopen(FILE_NAME, "w");
		if (side == BLACK)
			fprintf(fp, "Black chess strategy Error, try to put chess on a invalid place(%d, %d)\n", row, col);
		else
			fprintf(fp, "White chess strategy Error, try to put chess on a invalid place(%d, %d)\n", row, col);
		fprintf(fp, "══════════════════════════\n");
		fclose(fp);
	} // 判断当前局势
	else
	{
		checkBoard[row][col] = side; //裁判判定落子无误之后，准许落子
		if (side == BLACK)
			firstHandTime += time;
		else
			secondHandTime += time;
		// 判断当前的局势
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
								status = winSide;
								return;
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
								status = winSide;
								return;
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
								status = winSide;
								return;
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
								status = winSide;
								return;
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
								status = winSide;
								return;
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
								status = winSide;
								return;
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
								status = winSide;
								return;
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
								status = winSide;
								return;
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
		
		if (diffFabs(firstHandTime/CLOCKS_PER_SEC, secondHandTime/CLOCKS_PER_SEC) <= totalTimeThreshold)
			status = DRAW;
		else if (firstHandTime > secondHandTime)
			status = WHITE_WIN;
		else
			status = BLACK_WIN;
	end_judge:;
	}
}


void firstHand()
{
	// 黑棋先手
	//play(strategy, BLACK);
}

void secondHand()
{
	// 白棋后手
	//play(x, WHITE);
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
	double time = (double)(start - end); //经测试，Ubuntu16.04上显示精度为微秒级别
	judge(row, col, side, time);
}