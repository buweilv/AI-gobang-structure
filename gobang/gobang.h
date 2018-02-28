#pragma once
#ifndef FILE_NAME
#define FILE_NAME "6-2"
#endif // !FILE_NAME
enum { 	boardLen = 15 };
// 棋盘规格
extern int checkBoard[boardLen][boardLen];
extern int first; //区分先手是AI还是对手
// CONTINUE: 尚未出现平局或者获胜方
// DRAW: 裁判判定这是一场平局
// BLACK_WIN/WHITE_WIN: 裁判判定黑子/白子获胜
// STRATEGY_ERROR: AI策略的落子到了棋盘外或者已经下到了已经落子的位置
enum { CONTINUE, BLACK_WIN, WHITE_WIN,  DRAW, STRATEGY_ERROR};
// status表示棋局的 
extern int status;
// 棋盘每个位置的状态
enum { EMPTY, BLACK, WHITE }; // 注意BLACK与BLACK_WIN WHITE与WHITE_WIN是对位的
enum { AI, USER1 }; //在和本机AI对垒的情况下，区分本机AI和对手
// 平局的情况下，允许两个棋手下棋总时间相差的阈值，此处暂且以秒来作为计时单位
extern double timeThreshold;
extern double firstHandTime;
extern double secondHandTime;
extern long comScore[boardLen][boardLen]; //棋盘每个位置如果落com棋子的得分
extern long humScore[boardLen][boardLen]; //棋盘每个位置如果落对手棋子的得分

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




// 初始化棋盘
void initCheckBoard();
// 先手落子
void firstHand();
// 后手落子
void secondHand();
// 输出棋盘结果的局势
void output();
// 判断当前棋盘局势的状态
int getBoardStatus();
// 判断当前落子位置是否有效
int isValid(int row, int col, int side);
