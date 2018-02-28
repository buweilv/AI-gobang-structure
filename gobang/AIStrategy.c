#include "AIStrategy.h"
#include "gobang.h"
#include "utils.h"
#include <limits.h>
#define MAX_BOUND  (10 * FIVE)
#define MIN_BOUND -(10 * FIVE)


long negaMax(int depth, long alpha, long beta, int player, int *x, int *y);

/*
*����
*/
void put(int row, int col, int side) {
	checkBoard[row][col] = side;
	updateScore(row, col);
}

/*
* �������ֵ��Ⱥ��������ȡ����
*/
int getChess(int player)
{
	return (first == player ? BLACK : WHITE);
}

/*
* ��AI����ֶ�ս��ʱ�򣬷�ת��ɫ
*/
int reversePlayer(int player)
{
	return (AI == player ? USER1 : AI);
}

void user1Strategy(int *row, int *col)
{
	long alpha = MIN_BOUND;
	long beta = MAX_BOUND;
	static int count = 0; //��¼AI���˼�����
	if (count == 0) { //�Ƿ��ǵ�һ����
		if (first == USER1) { // ���������
			*row = 7; *col = 7;
			//checkBoard[7][7] = side;
			initScore();
		}
		else { //����
			if (checkBoard[7][7] == EMPTY) {
				*row = 7; *col = 7;
				//checkBoard[7][7] = side;
			}
			else if (checkBoard[7][8] == EMPTY) {
				*row = 7; *col = 8;
				//checkBoard[7][8] = side;
			}
		}
	}
	else {
		negaMax(2, alpha, beta, USER1, row, col);
		//if (isValid(*row, *col, side)) {
		//	checkBoard[*row][*col] = side; // ����λ����Ч��������
		//	updateScore(*row, *col, &ps);
		//}
	}
	count++;
}

void user2Strategy(int *row, int *col)
{
	*row = 1;
	*col = 1;
}


//row, col�����ӵĺ������ꣻ���������ж����ӵ���Ч��
void ringKingStrategy(int *row, int *col)
{
	long alpha = MIN_BOUND;
	long beta = MAX_BOUND;
	static int count = 0; //��¼AI���˼�����
	if (count == 0) { //�Ƿ��ǵ�һ����
		if (first == AI) { // ���������
			*row = 7; *col = 7;
			//checkBoard[7][7] = side;
			initScore();
		}
		else { //����
			if (checkBoard[7][7] == EMPTY) {
				*row = 7; *col = 7;
				//checkBoard[7][7] = side;
			}
			else if (checkBoard[7][8] == EMPTY) {
				*row = 7; *col = 8;
			//	checkBoard[7][8] = side;
			}
		}
	} else {
			negaMax(6, alpha, beta, AI, row, col);
			//if (isValid(*row, *col, side)) {
				//checkBoard[*row][*col] = side; // ����λ����Ч��������
				//updateScore(*row, *col, &ps);
			//}
		}
	count++;
}


/*
* ����NegaMax��alpha-beta��֧
* ����ֵ���ڵ��bestvalue
*/
long negaMax(int depth, long alpha, long beta, int player, int *x, int *y)
{
	if (depth == 0 || getBoardStatus() != CONTINUE)
		return evaluate(player);
	coordArray points = { .top = -1 };
	gen(&points);
	long bestVal = MIN_BOUND;
	for (int i = 0; i <= points.top; i++) {
		int row = points.arr[i].row;
		int col = points.arr[i].col;
		checkBoard[row][col] = getChess(player); //����
		long val = -negaMax(depth - 1, -beta, -alpha, reversePlayer(player), x, y);
		checkBoard[row][col] = EMPTY; //������һ����
		if (val > bestVal) {
			bestVal = val;
			*x = row;
			*y = col;
		}
		alpha = max(alpha, val);
		if (alpha >= beta)	
			break;
	}
	return bestVal;
}

