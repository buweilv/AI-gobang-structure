#include "AIStrategy.h"
#include "gobang.h"
#include "utils.h"
#include <limits.h>

enum {MIN_PLAYER, MAX_PLAYER};
enum {UNAVALABLE, AVAILABLE};

long alphaBeta(int depth, long alpha, long beta, int maximizingPlayer, int chess, int *x, int *y);

void user1Strategy(int *row, int *col, int chess)
{
	*row = boardLen - 1;
	*col = boardLen - 1;
}

void user2Strategy(int *row, int *col, int chess)
{
	*row = 1;
	*col = 1;
}

void ringKingStrategy(int *row, int *col, int chess)
{
	long alpha = LONG_MIN;
	long beta = LONG_MAX;
	alphaBeta(4, alpha, beta, MAX_PLAYER, chess, row, col);
}

/*
* 获取当前可以落子的位置
*/
void initPosition(int *availablePosition, int len) 
{
	int i, j;
	for (i = 0; i < len; i++) {
		for (j = 0; j < len; j++) {
			if (checkBoard[i][j] == EMPTY)
				*(availablePosition + i*len + j) = AVAILABLE;
			else
				*(availablePosition + i*len + j) = UNAVALABLE;
		}
	}
}

/*
* 反转当前的棋子：黑->白； 白->黑
*/
int reverseChess(int chess)
{
	if (chess == BLACK)
		return WHITE;
	if (chess == WHITE)
		return BLACK;
}

/*
* 对当前局势的评分策略
*/
long evaluate()
{
	return 0;
}

/*
*aplpha-beta剪支：alpha代表max player的最大得分，初始值为负无穷；beta代表min player的最小得分，初始值为正无穷
* 返回值：当前局势的评分；max player的alpha；min player的beta
*/
long alphaBeta(int depth, long alpha, long beta, int maximizingPlayer, int chess, int *x, int *y)
{
	// base case: 棋盘局势是最终局势有两种情况：一方胜；平局，无子可下
	if (depth == 0 || getBoardStatus() != CONTINUE)
		return evaluate(); // evaluate是当前形势的评分算法
	int availablePosition[boardLen][boardLen]; //可以落子的位置
	int i, j;
	if (maximizingPlayer == MAX_PLAYER) {
		long bestValue = LONG_MIN;
		initPosition((int *)availablePosition, boardLen);
		for (i = 0; i < boardLen; i++) {
			for (j = 0; j < boardLen; j++) {
				if (availablePosition[i][j] == AVAILABLE) {
					checkBoard[i][j] = chess;
					long re = alphaBeta(depth - 1, alpha, beta, MIN_PLAYER, reverseChess(chess), x, y);
					if (re > bestValue) {
						bestValue = re;
						*x = i;
						*y = j;
					}
					alpha = max(alpha, bestValue);
					// 回退，取消这一步的落子
					checkBoard[i][j] = EMPTY;
					if (alpha >= beta)
						goto maxEnd;
				}
			}
		}
	maxEnd:
		return bestValue;
	}
	else if (maximizingPlayer == MIN_PLAYER) {
		long bestValue = LONG_MAX;
		initPosition((int *)availablePosition, boardLen);
		for (i = 0; i < boardLen; i++) {
			for (j = 0; j < boardLen; j++) {
				if (availablePosition[i][j] == AVAILABLE) {
					checkBoard[i][j] = chess;
					long re = alphaBeta(depth - 1, alpha, beta, MIN_PLAYER, reverseChess(chess), x, y);
					if (re < bestValue) {
						bestValue = re;
						*x = i;
						*y = j;
					}
					beta = min(beta, bestValue);
					checkBoard[i][j] = EMPTY;
					if (alpha >= beta)
						goto minEnd;
				}
			}
		}
	minEnd:
		return bestValue;
	}
}