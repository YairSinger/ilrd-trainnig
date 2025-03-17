#include <stdio.h>

size_t AddBitwise(size_t num)
{
	size_t i = 0;
	size_t mask = 1;

	while(num & (mask << i))
	{
		num ^= mask << i;
		++i;
	}
	num |= mask << i;
	return num;
}



int main()
{
	size_t a = 0, b = 5, c = 21845, d = 10922;
	if (1 != AddBitwise(a) || 6 != AddBitwise(b) || 21846 != AddBitwise(c) || 10923 != AddBitwise(d))
	{
		printf("Failed\n");
		printf("%lu resulted %lu\n",a, AddBitwise(a));
		printf("%lu resulted %lu\n",b, AddBitwise(b));
		printf("%lu resulted %lu\n",c, AddBitwise(c));
		printf("%lu resulted %lu\n",d, AddBitwise(d));		
	}
	else
	{
		printf("passed add bitwise\n");
	}
	return 0;
}
