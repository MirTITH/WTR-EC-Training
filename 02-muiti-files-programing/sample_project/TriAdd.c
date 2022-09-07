#include "TriAdd.h"
#include <stdio.h>

static int Add(int x, int y)
{
	return x + y;
}

int TriAdd(int x, int y, int z)
{
    int temp = Add(x, y);
    return Add(temp, z);
}

void PrintTriAdd(int x, int y, int z)
{
    printf("%d\n", TriAdd(x, y, z));
}
