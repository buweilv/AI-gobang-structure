#include "utils.h"
#include <string.h>
#include <stdlib.h>


#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'
#define ok 'j'		//落子是j

double diffFabs(double d1, double d2)
{
	double re = d1 - d2;
	if (re < 0)
		re = -re;
	return re;
}

long max(long a, long b)
{
	return (a > b ? a : b);
}

long min(long a, long b)
{
	return (a < b ? a : b);
}


int *buildNext(const char *p)
{
	int i = 0, j = -1;
	int *next = (int *)malloc(sizeof(int)*(strlen(p) + 1));
	next[i] = j;
	while (p[i])
	{
		if (j == -1 || p[i] == p[j]) {
			i++; j++;
			if (p[i] == p[j])
				next[i] = next[j];
			else
				next[i] = j;
		}
		else
			j = next[j];
	}
	return next;
}
int countMatch(const char* pattern, const char* text)
{
	int matchCount = 0, i = 0, j = 0;
	int *next = buildNext(pattern);
	while (text[i])
	{
		if (j == -1 || text[i] == pattern[j]) {
			++i; ++j;
			if (!pattern[j]) {
				++matchCount; j = next[j];
			}
		}
		else j = next[j];
	}
	free(next);
	return matchCount;
}

void push(coordArray *s, coordinate c) {
	if (s != NULL && s->top < MAX_SIZE - 1) {
		s->arr[s->top+1] = c;
		s->top++;
	}
}

coordinate pop(coordArray *s) {
	coordinate c = { 15, 15 }; //非法位置
	if (s != NULL && s->top > -1) {
		c = s->arr[s->top];
		s->top--;
	}
	return c;
}

void unshift(coordArray *s, coordinate c) {
	if (s != NULL && s->top > -1 && s->top < MAX_SIZE - 1) {
		for (int i = s->top; i >= 0; i--)
			s->arr[i + 1] = s->arr[i];
		s->arr[0] = c;
		s->top++;
	}
}

coordArray * connect(coordArray *a, coordArray *b) {
	if (a != NULL && b != NULL && a->top + b->top <= MAX_SIZE - 2) {
		for (int i = 0; i <= b->top; i++) {
			push(a, b->arr[i]);
		}
	}
	return a;
}

void userInterface(int *row, int *col) 
{
//
	
}