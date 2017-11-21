#include "utils.h"
#include <string.h>
#include <stdlib.h>

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