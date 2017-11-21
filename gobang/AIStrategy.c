#include "AIStrategy.h"
#include "gobang.h"
#include "utils.h"
#include <limits.h>

enum {MIN_PLAYER, MAX_PLAYER};
enum {UNAVALABLE, AVAILABLE};

long alphaBeta(int depth, long alpha, long beta, int maximizingPlayer, int chess, int *x, int *y);

void user1Strategy(int *row, int *col, int chess)
{
	long alpha = LONG_MIN;
	long beta = LONG_MAX;
	alphaBeta(4, alpha, beta, MAX_PLAYER, chess, row, col);
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
*  横、竖、斜方向，对手的局势
*/
void reverseStatus(char *status) 
{
	int i = 1;
	while (status[i] != '\0') {
		if (status[i] == 1)
			status[i] = 2;
		if (status[i] == 2)
			status[i] = 1;
		i++;
	}
	status[i - 1] = '2';
}

/*
* 对当前局势的评分策略
*/
long evaluate(int maximizingPlayer, int chess)
{
	if (maximizingPlayer == MIN_PLAYER)
		chess = reverseChess(chess);
	// 1表示目标棋子，0表示空位，2表示对手棋子
	const char* chessType[] = {
		"11111", // 长连
		"011110", // 活四，有2个连5的点
		"011112", // 冲四，有1个连5的点
		"211110",
		"10111",
		"11011",
		"11101", // 冲四 end
		"01110", // 活三，可以形成活四
		"010110",
		"011010", // 活三 end
		"001112", // 眠三，能够形成冲四的三
		"010112",
		"011012",
		"211100",
		"211010",
		"210110",
		"10011",
		"10101",
		"11001", // 眠三 end
		"00110", // 活二，能够形成活三
		"01010",
		"01100",
		"000112", // 眠二，能够形成眠三
		"001012",
		"010012",
		"211000",
		"210100",
		"210010" // 眠二 end
	};
	int patternNum = sizeof(chessType) / sizeof(const char *);
	long score[] = { 99999999, // 长连
		50000, // 活四
		5000, 5000, 5000, 5000, 5000, // 冲四
		5000, 5000, 5000, // 活三
		500, 500, 500, 500, 500, 500, 500, 500, 500, // 眠三
		500, 500, 500, //活二
		50, 50, 50, 50, 50, 50 // 眠二
	};
	long result = 0;
	int i, j, matchNum;
	// 横着的各路
	for (i = 0; i < boardLen; i++) {
		char status[2*boardLen];
		status[0] = '2';
		for (j = 0; j < boardLen; j++) {
			if (checkBoard[i][j] == EMPTY)
				status[j+1] = '0';
			if (checkBoard[i][j] == chess)
				status[j + 1] = '1';
			else
				status[j + 1] = '2';
		}
		status[j] = '2';
		status[j + 1] = '\0';
		for (j = 0; j < patternNum; j++) {
			matchNum = countMatch(chessType[j], status);
			result += matchNum * score[j];
		}
		reverseStatus(status);
		for (j = 0; j < patternNum; j++) {
			matchNum = countMatch(chessType[j], status);
			result -= matchNum * score[j];
		}
	}
	// 竖着的各路
	for (j = 0; j < boardLen; j++) {
		char status[2 * boardLen];
		status[0] = '2';
		for (i = 0; i < boardLen; i++) {
			if (checkBoard[i][j] == EMPTY)
				status[i + 1] = '0';
			if (checkBoard[i][j] == chess)
				status[i + 1] = '1';
			else
				status[i + 1] = '2';
		}
		status[i] = '2';
		status[i + 1] = '\0';
		for (i = 0; i < patternNum; i++) {
			matchNum = countMatch(chessType[i], status);
			result += matchNum * score[i];
		}
		reverseStatus(status);
		for (i = 0; i < patternNum; i++) {
			matchNum = countMatch(chessType[i], status);
			result -= matchNum * score[i];
		}
	}
	// 正斜方的各路
	for (i = 4; i < boardLen; i++) {
		char status[2 * boardLen];
		status[0] = '2';
		for (j = 0; j <= i; j++) {
			if (checkBoard[i-j][j] == EMPTY)
				status[j + 1] = '0';
			if (checkBoard[i-j][j] == chess)
				status[j + 1] = '1';
			else
				status[j + 1] = '2';
		}
		status[j] = '2';
		status[j + 1] = '\0';
		for (j = 0; j < patternNum; j++) {
			matchNum = countMatch(chessType[j], status);
			result += matchNum * score[j];
		}
		reverseStatus(status);
		for (j = 0; j < patternNum; j++) {
			matchNum = countMatch(chessType[j], status);
			result -= matchNum * score[j];
		}
	}
	for (j = 1; j < boardLen - 4; j++) {
		char status[2 * boardLen];
		status[0] = '2';
		int col = j, k = 1;
		for (i = boardLen - 1; i >= j; i--) {
			if (checkBoard[i][col] == EMPTY)
				status[k] = '0';
			if (checkBoard[i][col] == chess)
				status[k] = '1';
			else
				status[k] = '2';
			col++;
			k++;
		}
		status[k] = '2';
		status[k + 1] = '\0';
		for (k = 0; k < patternNum; k++) {
			matchNum = countMatch(chessType[k], status);
			result += matchNum * score[k];
		}
		reverseStatus(status);
		for (k = 0; k < patternNum; k++) {
			matchNum = countMatch(chessType[k], status);
			result -= matchNum * score[k];
		}
	}
	// 反斜方的各路
	for (j = 4; j < boardLen; j++) {
		char status[2 * boardLen];
		status[0] = '2';
		int col = j, k = 1;
		for (i = boardLen - 1; i >= boardLen - j - 1; i--) {
			if (checkBoard[i][col] == EMPTY)
				status[k] = '0';
			if (checkBoard[i][col] == chess)
				status[k] = '1';
			else
				status[k] = '2';
			col--;
			k++;
		}
		status[k] = '2';
		status[k + 1] = '\0';
		for (k = 0; k < patternNum; k++) {
			matchNum = countMatch(chessType[k], status);
			result += matchNum * score[k];
		}
		reverseStatus(status);
		for (k = 0; k < patternNum; k++) {
			matchNum = countMatch(chessType[k], status);
			result -= matchNum * score[k];
		}
	}
	for (i = boardLen - 2; i >= 4; i--) {
		char status[2 * boardLen];
		status[0] = '2';
		int row = i, k = 1;
		for (j = boardLen - 1; j >= boardLen - 1 - i; j--) {
			if (checkBoard[row][j] == EMPTY)
				status[k] = '0';
			if (checkBoard[row][j] == chess)
				status[k] = '1';
			else
				status[k] = '2';
			row--;
			k++;
		}
		status[k] = '2';
		status[k + 1] = '\0';
		for (k = 0; k < patternNum; k++) {
			matchNum = countMatch(chessType[k], status);
			result += matchNum * score[k];
		}
		for (k = 0; k < patternNum; k++) {
			matchNum = countMatch(chessType[k], status);
			result -= matchNum * score[k];
		}
	}
	return result;
}

/*
*aplpha-beta剪支：alpha代表max player的最大得分，初始值为负无穷；beta代表min player的最小得分，初始值为正无穷
* 返回值：当前局势的评分；max player的alpha；min player的beta
*/
long alphaBeta(int depth, long alpha, long beta, int maximizingPlayer, int chess, int *x, int *y)
{
	// base case: 棋盘局势是最终局势有两种情况：一方胜；平局，无子可下
	if (depth == 0 || getBoardStatus() != CONTINUE)
		return evaluate(maximizingPlayer, chess); // evaluate是当前形势的评分算法
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