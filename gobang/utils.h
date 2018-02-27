#pragma once
#define MAX_SIZE  225 //coordArray����ܹ��洢Ԫ�صĸ���
// ��������ľ���ֵ
double diffFabs(double d1, double d2);
long max(long a, long b);
long min(long a, long b);
// ͳ���ı�����ģʽ�����ֵĴ���
int countMatch(const char* pattern, const char* text);

typedef struct {
	int row;
	int col;
} coordinate;

typedef struct {
	coordinate arr[MAX_SIZE]; //���������̵�����λ��
	int top;
} coordArray;


void push(coordArray *s, coordinate c);
coordinate pop(coordArray *s);
void unshift(coordArray *s, coordinate c);
coordArray * connect(coordArray *a, coordArray *b);
void userInterface(int *row, int *col); //�û��ֶ�����