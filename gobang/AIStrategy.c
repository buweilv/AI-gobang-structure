#include "AIStrategy.h"
#include "gobang.h"
#include "utils.h"
#include <limits.h>
#define MAX_BOUND  (10 * FIVE)
#define MIN_BOUND -(10 * FIVE)


long negaMax(int depth, long alpha, long beta, int player, int *x, int *y);

/*
*下子
*/
void put(int row, int col, int side) {
	checkBoard[row][col] = side;
	updateScore(row, col);
}

/*
* 根据棋手的先后手情况获取棋型
*/
int getChess(int player)
{
	return (first == player ? BLACK : WHITE);
}

/*
* 在AI与对手对战的时候，反转角色
*/
int reversePlayer(int player)
{
	return (AI == player ? USER1 : AI);
}

void user1Strategy(int *row, int *col)
{
	long alpha = MIN_BOUND;
	long beta = MAX_BOUND;
	static int count = 0; //记录AI下了几步棋
	if (count == 0) { //是否是第一步棋
		if (first == USER1) { // 如果是先手
			*row = 7; *col = 7;
			//checkBoard[7][7] = side;
			initScore();
		}
		else { //后手
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
		//	checkBoard[*row][*col] = side; // 落子位置有效，则下棋
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


//row, col即落子的横纵坐标；先落子再判断落子的有效性
void ringKingStrategy(int *row, int *col)
{
	long alpha = MIN_BOUND;
	long beta = MAX_BOUND;
	static int count = 0; //记录AI下了几步棋
	if (count == 0) { //是否是第一步棋
		if (first == AI) { // 如果是先手
			*row = 7; *col = 7;
			//checkBoard[7][7] = side;
			initScore();
		}
		else { //后手
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
				//checkBoard[*row][*col] = side; // 落子位置有效，则下棋
				//updateScore(*row, *col, &ps);
			//}
		}
	count++;
}


/*
* 基于NegaMax的alpha-beta剪支
* 返回值：节点的bestvalue
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
		checkBoard[row][col] = getChess(player); //下棋
		long val = -negaMax(depth - 1, -beta, -alpha, reversePlayer(player), x, y);
		checkBoard[row][col] = EMPTY; //撤回这一步棋
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

