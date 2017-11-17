#pragma once
/*
* 提供策略的接口
* ringKingStrategy 是程序提供的擂主策略
* user1Strategy 是用户1提交的策略
* user2Strategy 是用户2提交的策略
* 如果用户采取挑战擂主的模式，则仅需要一个用户提交策略，该策略会提交到user1Strategy
* 如果选择两个用户对擂的模式，需要两个用户提交策略，先手提交的策略至user1Strategy；后手提交的策略至user2Strategy
*/

void ringKingStrategy(int *, int *);
void user1Strategy(int *, int *);
void user2Strategy(int *, int *);