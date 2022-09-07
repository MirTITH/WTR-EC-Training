#include "PrintAdd.h"
#include <stdio.h>

static int Add(int x, int y);

void PrintAdd(int x, int y)
{
	int result = Add(x, y);

	printf("%d\n", result);
}

static int Add(int x, int y)
{
	return x + y;
}
