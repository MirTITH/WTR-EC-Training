#include "PrintAdd.h"
#include <stdio.h>

static void PrintNum(int num);

void PrintAdd(int x, int y)
{
	PrintNum(x + y);
}

static void PrintNum(int num)
{
	printf("%d\n", num);
}