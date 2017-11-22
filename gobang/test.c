#include "test.h"
#include "gobang.h"
#include "AIStrategy.h"
#include "utils.h"
#include <stdio.h>

static enum {MIN_PLAYER, MAX_PLAYER};
/*
* ���Խ����յ�����������ļ��е�Ч��
* ����������
* 1. �����ϴ��ںڰ���
* 2. ����λ�ڱ����ϣ��������ĸ�����
* 3. ����������֮��Ĵ�ӡЧ��
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
* ���Բ��й����ܷ���������
* 1. �����Բ��ԣ����ӻ����ʤ���ᡢ����б1��б2��
* 2. �����Բ��ԣ�ƽ�֣�����113������112�� ������ʱ����ʱ����ֵ����ڣ�ƽ�֣���������ʱ����ʱ����ֵ����⣨ʱ��̵�ѡ�ֻ�ʤ��
* 3. �쳣�Բ��ԣ����������ڽ��� or �����������Ѿ����ӵ�λ��
*/
void judgeTest()
{
	int i;
	// ��-win
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
	// ��-win
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
	// ��б-win
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
	// ��б-win
	
	initCheckBoard();
	checkBoard[0][0] = BLACK; checkBoard[0][1] = BLACK;
	checkBoard[1][0] = BLACK; checkBoard[1][2] = BLACK; checkBoard[2][1] = BLACK;
	for (i = 0; i < 4; i++)
		checkBoard[4-i][i] = WHITE;
	firstHandTime = 20000;
	secondHandTime = 150000;
	judge(0, 4, WHITE, 20);
	output();
	
	// ƽ��-�������ֵʱ���ڲ�
	/*
	// ż���е���ʽ
	int evenLine[boardLen] = {BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK};
	// �����е���ʽ
	int oddLine[boardLen] = {WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE};
	initCheckBoard();
	for (int i = 0; i < boardLen; i++) {
		if (i % 2) { //������
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
	// ƽ�֣�����һ��ʱ����������и�
	initCheckBoard();
	for (int i = 0; i < boardLen; i++) {
		if (i % 2) { //������
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
	// �������ڽ���
	/*
	initCheckBoard();
	judge(0, boardLen, BLACK, 12);
	output();
	*/
	// ���������Ѿ��¹���������
	/*
	initCheckBoard();
	checkBoard[10][10] = BLACK;
	firstHandTime = 12;
	judge(10, 10, WHITE, 12);
	output();
	*/
}

// �鿴��-DFIRST -DTWOUSERS �Լ�Ĭ��gcc����ѡ���������֮��
// �������յĽ����ʽ
void battleModeTest()
{
	firstHand();
	//secondHand();
	output();
}

/*
* �����ַ���ƥ�����
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
