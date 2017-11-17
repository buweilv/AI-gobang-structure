#pragma once
#ifndef FILE_NAME
#define FILE_NAME "two_users"
#endif // !FILE_NAME
enum { 	boardLen = 15 };
// 棋盘规格
extern int checkBoard[15][15];
// CONTINUE: 尚未出现平局或者获胜方
// DRAW: 裁判判定这是一场平局
// BLACK/WHITE: 裁判判定黑子/白子获胜
enum { CONTINUE, BLACK_WIN, WHITE_WIN,  DRAW, STRATEGY_ERROR};
// status表示棋局的 
extern int status;
// 棋盘每个位置的状态
enum { EMPTY, BLACK, WHITE }; // 注意BLACK与BLACK_WIN WHITE与WHITE_WIN是对位的
// 平局的情况下，允许两个棋手下棋总时间相差的阈值，此处暂且以秒来作为计时单位
extern double totalTimeThreshold;
// 先手、后手下棋的总时间
extern double firstHandTime;
extern double secondHandTime;


// 初始化棋盘
void initCheckBoard();
// 先手落子
void firstHand();
// 后手落子
void secondHand();
// 输出棋盘结果的局势
void output();
// 裁判
void judge(int row, int col, int side, double time);