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
* ��ȡ��ǰ�������ӵ�λ��
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
* ��ת��ǰ�����ӣ���->�ף� ��->��
*/
int reverseChess(int chess)
{
	if (chess == BLACK)
		return WHITE;
	if (chess == WHITE)
		return BLACK;
}

/*
* �Ե�ǰ���Ƶ����ֲ���
*/
long evaluate()
{
	return 0;
}

/*
*aplpha-beta��֧��alpha����max player�����÷֣���ʼֵΪ�����beta����min player����С�÷֣���ʼֵΪ������
* ����ֵ����ǰ���Ƶ����֣�max player��alpha��min player��beta
*/
long alphaBeta(int depth, long alpha, long beta, int maximizingPlayer, int chess, int *x, int *y)
{
	// base case: ���̾��������վ��������������һ��ʤ��ƽ�֣����ӿ���
	if (depth == 0 || getBoardStatus() != CONTINUE)
		return evaluate(); // evaluate�ǵ�ǰ���Ƶ������㷨
	int availablePosition[boardLen][boardLen]; //�������ӵ�λ��
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
					// ���ˣ�ȡ����һ��������
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