#pragma once
/*
* �ṩ���ԵĽӿ�
* ringKingStrategy �ǳ����ṩ����������
* user1Strategy ���û�1�ύ�Ĳ���
* user2Strategy ���û�2�ύ�Ĳ���
* ����û���ȡ��ս������ģʽ�������Ҫһ���û��ύ���ԣ��ò��Ի��ύ��user1Strategy
* ���ѡ�������û����޵�ģʽ����Ҫ�����û��ύ���ԣ������ύ�Ĳ�����user1Strategy�������ύ�Ĳ�����user2Strategy
* evaluate ��player�ĽǶȶԵ�ǰ���̾��ƽ�������
* gen �����Ѿ�����õĿ������ӵ�����
*/
#include "utils.h"
#include "gobang.h"

/*
typedef struct {
	long comScore[boardLen][boardLen]; //����ÿ��λ�������com���ӵĵ÷�
	long humScore[boardLen][boardLen]; //����ÿ��λ�������������ӵĵ÷�
}positionScore;
*/


void ringKingStrategy(int *, int *);
void user1Strategy(int *, int *);
void user2Strategy(int *, int *);
long evaluate(int player); 
void gen(coordArray *re);
void initScore(); //��һ����֮�󣬸���λ�õķ�����ʼ��
void updateScore(int row, int col); 
void put(int row, int col, int side);