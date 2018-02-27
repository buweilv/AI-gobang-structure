#pragma once
#define MAX_SIZE  225 //coordArray最多能够存储元素的个数
// 求两数差的绝对值
double diffFabs(double d1, double d2);
long max(long a, long b);
long min(long a, long b);
// 统计文本串中模式串出现的次数
int countMatch(const char* pattern, const char* text);

typedef struct {
	int row;
	int col;
} coordinate;

typedef struct {
	coordinate arr[MAX_SIZE]; //五子棋棋盘的所有位置
	int top;
} coordArray;


void push(coordArray *s, coordinate c);
coordinate pop(coordArray *s);
void unshift(coordArray *s, coordinate c);
coordArray * connect(coordArray *a, coordArray *b);
void userInterface(int *row, int *col); //用户手动下棋