/*
** ��ʼ������ void initCheckBoard()
** ������̽���ľ��� void output();
*/
#include "gobang.h"
#include <stdio.h>
#include <time.h>

void initCheckBoard()
{
	int i, j;
	for (i = 0; i < boardLen; i++)
		for (j = 0; j < boardLen; j++)
			checkBoard[i][j] = EMPTY;
}

void output()
{
	FILE *fp = NULL;
	if (status == STRATEGY_ERROR)
		fp = fopen(FILE_NAME, "a");
	else
		fp = fopen(FILE_NAME, "w");
	int i, j;
	for (i = 0; i < boardLen; i++)
	{
		for (j = 0; j < boardLen; j++) {
			if (checkBoard[i][j] == EMPTY) {
				if (i == 0 && j == 0) fprintf(fp, "��");
				else if (i == 0 && j == boardLen - 1) fprintf(fp, "��");
				else if (i == boardLen - 1 && j == 0) fprintf(fp, "��");
				else if (i == boardLen - 1 && j == boardLen - 1) fprintf(fp, "��");
				else {
					switch (j)
					{
					case boardLen - 1: fprintf(fp, "��"); break;
					case 0: fprintf(fp, "��"); break;
					default:
						switch (i)
						{
						case 0: fprintf(fp, "��"); break;
						case boardLen - 1: fprintf(fp, "��"); break;
						default: fprintf(fp, "��"); break;
						}
						break;
					}
				}
			}
			if (checkBoard[i][j] == BLACK)
				fprintf(fp, "��");
			if (checkBoard[i][j] == WHITE)
				fprintf(fp, "��");
				
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	if (status == BLACK_WIN)
		fprintf(fp, "Black Chess wins!\n");
	if (status == WHITE_WIN)
		fprintf(fp, "White Chess wins!\n");
	if (status == DRAW)
		fprintf(fp, "Game to draw...\n");
	fclose(fp);
}
