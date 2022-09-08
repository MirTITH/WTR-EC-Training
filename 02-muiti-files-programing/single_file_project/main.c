#include <stdio.h>

void PrintNum(int num)
{
	printf("%d\n", num);
}

void PrintAdd(int x, int y)
{
	PrintNum(x + y);
}

void PrintTriAdd(int x, int y, int z)
{
    PrintNum(x + y + z);
}

int main()
{
	PrintAdd(4,5);
	PrintTriAdd(1,2,3);
	
	return 0;
}
