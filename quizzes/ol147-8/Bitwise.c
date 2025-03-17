#include <stdlib.h>
#include <stdio.h>

int CountPairedBits(int a)
{
	size_t i = 0;
	int coupls = 0;
	int mask = 3;
	
	for(; i < 7; ++i, a >>= 1)
	{
		if(((a & mask) == 3))
		{
			++coupls;
		}
	}
	
	return coupls;
}

void Swap1(int *a, int *b)
{
	*a = *b + *a;
	*b = *a - *b;
	*a = *a - *b;
}

void Swap2(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void Swap3(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int CountSetBits(long a)
{
	int bits_on = 0;
	while(a > 0)
	{
		++bits_on;
		a = (a & (a-1));
	}

	return bits_on;
}

int main(void)
{
	int a = 9, b = 3;
	long c = 2500;
	si
	
	Swap1(&a, &b);
	if (a == 3 && b == 9)
	{
		printf("swap1 passed\n");
	}
	Swap2(&a, &b);
	if (a == 9 && b == 3)
	{
		printf("swap2 passed\n");
	}
	Swap3(&a, &b);
	if (a == 3 && b == 9)
	{
		printf("swap3 passed\n");
	}
	
	if (CountPairedBits(90) == 1 && CountPairedBits(199) == 3)
	{
		printf("CountPairedBits passed\n");
	}
	else 
	{
		printf("CountPairedBits failed\n");
	}

	if (CountSetBits(c) == 5)
	{
		printf("CountSetBits passed\n");
	}

	return 0;
}

