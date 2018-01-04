/*
* ��TWOUSERS�ͺ�FIRST�ǲ�����ͬʱָ����
* ��TWOUSERS��ʾ���ǵ�ǰ�Ķ�սģʽ��˫�˶�ս
* ��FIRST��ʾ��ս����ģʽʱ�����û��Ĳ�������Ϊ���ֲ���
*/
#include "gobang.h"
#include "utils.h"
#include "AIStrategy.h"
#include <stdio.h>
#include <time.h>

// Ĭ�����������ս����ģʽ��Ĭ�ϵ��������������ԣ����ֲ�����user1Strategy
#if (!defined(TWOUSERS) && !defined(FIRST))
void(*firstHandStrategy)(int*, int*, int) = ringKingStrategy;
void(*secondHandStrategy)(int*, int*, int) = user1Strategy;
#endif
#ifdef TWOUSERS // ˫�˶�սʱ��user1Strategy�����ֲ��ԣ�user2Strategy�Ǻ��ֲ���
void(*firstHandStrategy)(int*, int*, int) = user1Strategy;
void(*secondHandStrategy)(int*, int*, int) = user2Strategy;
#endif // TWOUSERS
#ifdef FIRST // ��ս����ģʽʱ���������������FIRST�꣬��ʾ�û��ύ�Ĳ��������ֲ���
void(*firstHandStrategy)(int*, int*, int) = user1Strategy;
void(*secondHandStrategy)(int*, int*, int) = ringKingStrategy;
#endif // FIRST

// ƽ�ֵ�����£�������������������ʱ��������ֵ���˴�������������Ϊ��ʱ��λ
double totalTimeThreshold = 10; 
// ���֡������������ʱ��
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
				// ��(i,j)Ϊ��㣬�������ҵ���������
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
				// ��(i,j)Ϊ��㣬�����������������
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
				// ��(i,j)Ϊ��㣬�������µ���������
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
				// ��(i,j)Ϊ��㣬�������ϵ���������
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
				// ��(i,j)Ϊ��㣬���������µ���������
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
				// ��(i,j)Ϊ��㣬���������µ���������
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
				// ��(i,j)Ϊ��㣬���������ϵ���������
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
				// ��(i,j)Ϊ��㣬���������ϵ���������
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
			} // if������λ��
		} //�ڲ�forѭ������λ��
	}

	// �����˴���ʾ�����嵱ǰ�ľ��Ʋ�����Ӯ�ң�����Ƿ����ƽ��
	for (i = 0; i < boardLen; i++)
		for (j = 0; j < boardLen; j++)
			if (checkBoard[i][j] == EMPTY)
				goto end_judge;
	return DRAW;
end_judge:
	return CONTINUE;
}

// �������ж������Ƿ���ȷ�����жϾ���
// ע�⣬�˴��ľ���̫С�Ļ����п������
void judge(int row, int col, int side, double time)
{
	// �ж������Ƿ���ȷ
	if (checkBoard[row][col] != EMPTY || row >= boardLen || col >= boardLen) {
		status = STRATEGY_ERROR;
		FILE *fp = fopen(FILE_NAME, "w");
		if (side == BLACK)
			fprintf(fp, "Black chess strategy Error, try to put chess on a invalid place(%d, %d)\n", row, col);
		else
			fprintf(fp, "White chess strategy Error, try to put chess on a invalid place(%d, %d)\n", row, col);
		fprintf(fp, "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
		fclose(fp);
	} // �жϵ�ǰ����
	else
	{
		checkBoard[row][col] = side; //�����ж���������֮��׼������
		if (side == BLACK)
			firstHandTime += time;
		else
			secondHandTime += time;
		// �жϵ�ǰ�ľ���
		status = getBoardStatus();
		// �����ƽ�֣�����Ҫ��ע˫����ʱ��֮���Ƿ�����ֵ��Χ��
		if (status == DRAW) {
			if (diffFabs(firstHandTime / CLOCKS_PER_SEC, secondHandTime / CLOCKS_PER_SEC) > totalTimeThreshold) {
				if (firstHandTime > secondHandTime)
					status = WHITE_WIN;
				else
					status = BLACK_WIN;
			}
		}
	}
}


void play(void (*strategy)(int*, int*, int), int side)
{
	// ���ӵ�����
	int row, col;
	// ���� -> �������ӵ�λ��
	clock_t start, end;
	start = clock();
	strategy(&row, &col, side);
	end = clock();
	double time = (double)(end - start); //�����ԣ�Ubuntu16.04����ʾ����Ϊ΢�뼶��
	if (side == BLACK)
		printf("BLACK chess on (%d,%d), took %ld micro secs\n", row, col, time);
	if (side == WHITE)
		printf("WHITE chess on (%d,%d), took %ld micro secs\n", row, col, time);
	judge(row, col, side, time);
}

void firstHand()
{
	// ��������
	play(firstHandStrategy, BLACK);
}

void secondHand()
{
	// �������
	play(secondHandStrategy, WHITE);
}
