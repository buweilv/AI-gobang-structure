#pragma once
#ifndef FILE_NAME
#define FILE_NAME "6-2"
#endif // !FILE_NAME
enum { 	boardLen = 15 };
// ���̹��
extern int checkBoard[boardLen][boardLen];
extern int first; //����������AI���Ƕ���
// CONTINUE: ��δ����ƽ�ֻ��߻�ʤ��
// DRAW: �����ж�����һ��ƽ��
// BLACK_WIN/WHITE_WIN: �����ж�����/���ӻ�ʤ
// STRATEGY_ERROR: AI���Ե����ӵ�������������Ѿ��µ����Ѿ����ӵ�λ��
enum { CONTINUE, BLACK_WIN, WHITE_WIN,  DRAW, STRATEGY_ERROR};
// status��ʾ��ֵ� 
extern int status;
// ����ÿ��λ�õ�״̬
enum { EMPTY, BLACK, WHITE }; // ע��BLACK��BLACK_WIN WHITE��WHITE_WIN�Ƕ�λ��
enum { AI, USER1 }; //�ںͱ���AI���ݵ�����£����ֱ���AI�Ͷ���
// ƽ�ֵ�����£�������������������ʱ��������ֵ���˴�������������Ϊ��ʱ��λ
extern double timeThreshold;
extern double firstHandTime;
extern double secondHandTime;
extern long comScore[boardLen][boardLen]; //����ÿ��λ�������com���ӵĵ÷�
extern long humScore[boardLen][boardLen]; //����ÿ��λ�������������ӵĵ÷�

enum 
{
	ONE = 10,
	TWO = 100,
	THREE = 1000,
	FOUR = 100000,
	FIVE = 1000000,
	BLOCKED_ONE = 1,
	BLOCKED_TWO = 10,
	BLOCKED_THREE = 100,
	BLOCKED_FOUR = 10000
};




// ��ʼ������
void initCheckBoard();
// ��������
void firstHand();
// ��������
void secondHand();
// ������̽���ľ���
void output();
// �жϵ�ǰ���̾��Ƶ�״̬
int getBoardStatus();
// �жϵ�ǰ����λ���Ƿ���Ч
int isValid(int row, int col, int side);
