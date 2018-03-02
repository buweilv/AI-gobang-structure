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

