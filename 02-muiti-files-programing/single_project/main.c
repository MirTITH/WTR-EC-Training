#include <stdio.h>

int Add(int x, int y)
{
	return x + y;
}

void PrintAdd(int x, int y)
{
	int result = Add(x, y);

	printf("%d\n", result);
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

int main()
{
	PrintAdd(4,5);
	PrintTriAdd(1,2,3);
	
	return 0;
}
