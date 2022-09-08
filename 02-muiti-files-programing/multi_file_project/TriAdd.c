#include "TriAdd.h"
#include <stdio.h>

static void PrintNum(int num)
{
	printf("%d\n", num);
}

void PrintTriAdd(int x, int y, int z)
{
    PrintNum(x + y + z);
}
