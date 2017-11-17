#include "utils.h"

double diffFabs(double d1, double d2)
{
	double re = d1 - d2;
	if (re < 0)
		re = -re;
	return re;
}
