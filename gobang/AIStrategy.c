#include "AIStrategy.h"
#include "gobang.h"
#include "utils.h"
#include <limits.h>
#define MAX_BOUND  (10 * FIVE)
#define MIN_BOUND -(10 * FIVE)

enum {MIN_PLAYER, MAX_PLAYER};
enum {UNAVALABLE, AVAILABLE};


//long alphaBeta(int depth, long alpha, long beta, int maximizingPlayer, int chess, int *x, int *y);
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
			negaMax(4, alpha, beta, AI, row, col);
			//if (isValid(*row, *col, side)) {
				//checkBoard[*row][*col] = side; // ����λ����Ч��������
				//updateScore(*row, *col, &ps);
			//}
		}
	count++;
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
*  �ᡢ����б���򣬶��ֵľ���
*/
void reverseStatus(char *status) 
{
	int i = 1;
	while (status[i] != '\0') {
		if (status[i] =='1')
			status[i] = '2';
		else if (status[i] == '2')
			status[i] = '1';
		i++;
	}
	status[i - 1] = '2';
}

/*
* �Ե�ǰ���Ƶ����ֲ���
*/
/*
long evaluate(int maximizingPlayer, int chess)
{
	if (maximizingPlayer == MIN_PLAYER)
		chess = reverseChess(chess);
	// 1��ʾĿ�����ӣ�0��ʾ��λ��2��ʾ��������
	const char* chessType[] = {
		"11111", // ����
		"011110", // ���ģ���2����5�ĵ�
		"011112", // ���ģ���1����5�ĵ�
		"211110",
		"10111",
		"11011",
		"11101", // ���� end
		"01110", // �����������γɻ���
		"010110",
		"011010", // ���� end
		"001112", // �������ܹ��γɳ��ĵ���
		"010112",
		"011012",
		"211100",
		"211010",
		"210110",
		"10011",
		"10101",
		"11001", // ���� end
		"00110", // ������ܹ��γɻ���
		"01010",
		"01100",
		"000112", // �߶����ܹ��γ�����
		"001012",
		"010012",
		"211000",
		"210100",
		"210010" // �߶� end
	};
	int patternNum = sizeof(chessType) / sizeof(const char *);
	long score[] = { 99999999, // ����
		50000, // ����
		5000, 5000, 5000, 5000, 5000, // ����
		5000, 5000, 5000, // ����
		500, 500, 500, 500, 500, 500, 500, 500, 500, // ����
		500, 500, 500, //���
		50, 50, 50, 50, 50, 50 // �߶�
	};
	long result = 0;
	int i, j, matchNum;
	// ���ŵĸ�·
	for (i = 0; i < boardLen; i++) {
		char status[2*boardLen];
		status[0] = '2';
		for (j = 0; j < boardLen; j++) {
			if (checkBoard[i][j] == EMPTY)
				status[j+1] = '0';
			else if (checkBoard[i][j] == chess)
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
	// ���ŵĸ�·
	for (j = 0; j < boardLen; j++) {
		char status[2 * boardLen];
		status[0] = '2';
		for (i = 0; i < boardLen; i++) {
			if (checkBoard[i][j] == EMPTY)
				status[i + 1] = '0';
			else if (checkBoard[i][j] == chess)
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
	// ��б���ĸ�·
	for (i = 4; i < boardLen; i++) {
		char status[2 * boardLen];
		status[0] = '2';
		for (j = 0; j <= i; j++) {
			if (checkBoard[i-j][j] == EMPTY)
				status[j + 1] = '0';
			else if (checkBoard[i-j][j] == chess)
				status[j + 1] = '1';
			else
				status[j + 1] = '2';
		}
		status[j + 1] = '2';
		status[j + 2] = '\0';
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
			else if (checkBoard[i][col] == chess)
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
	// ��б���ĸ�·
	for (j = 4; j < boardLen; j++) {
		char status[2 * boardLen];
		status[0] = '2';
		int col = j, k = 1;
		for (i = boardLen - 1; i >= boardLen - j - 1; i--) {
			if (checkBoard[i][col] == EMPTY)
				status[k] = '0';
			else if (checkBoard[i][col] == chess)
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
			else if (checkBoard[row][j] == chess)
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
		reverseStatus(status);
		for (k = 0; k < patternNum; k++) {
			matchNum = countMatch(chessType[k], status);
			result -= matchNum * score[k];
		}
	}
	return result;
}
*/

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

/*
*aplpha-beta��֧��alpha����max player�����÷֣���ʼֵΪ�����beta����min player����С�÷֣���ʼֵΪ������
* ����ֵ����ǰ���Ƶ����֣�max player��alpha��min player��beta
*/
/*
long alphaBeta(int depth, long alpha, long beta, int maximizingPlayer, int chess, int *x, int *y)
{
	// base case: ���̾��������վ��������������һ��ʤ��ƽ�֣����ӿ���
	if (depth == 0 || getBoardStatus() != CONTINUE)
		return evaluate(maximizingPlayer, chess); // evaluate�ǵ�ǰ���Ƶ������㷨
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
					long re = alphaBeta(depth - 1, alpha, beta, MAX_PLAYER, reverseChess(chess), x, y);
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
*/
