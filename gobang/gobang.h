#pragma once
#ifndef FILE_NAME
#define FILE_NAME "two_users"
#endif // !FILE_NAME
enum { 	boardLen = 15 };
// ���̹��
extern int checkBoard[15][15];
// CONTINUE: ��δ����ƽ�ֻ��߻�ʤ��
// DRAW: �����ж�����һ��ƽ��
// BLACK/WHITE: �����ж�����/���ӻ�ʤ
enum { CONTINUE, BLACK_WIN, WHITE_WIN,  DRAW, STRATEGY_ERROR};
// status��ʾ��ֵ� 
extern int status;
// ����ÿ��λ�õ�״̬
enum { EMPTY, BLACK, WHITE }; // ע��BLACK��BLACK_WIN WHITE��WHITE_WIN�Ƕ�λ��
// ƽ�ֵ�����£�������������������ʱ��������ֵ���˴�������������Ϊ��ʱ��λ
extern double totalTimeThreshold;
// ���֡������������ʱ��
extern double firstHandTime;
extern double secondHandTime;


// ��ʼ������
void initCheckBoard();
// ��������
void firstHand();
// ��������
void secondHand();
// ������̽���ľ���
void output();
// ����
void judge(int row, int col, int side, double time);