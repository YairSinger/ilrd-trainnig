#include <stdio.h>
#include "ws1.h"






double tenPowerNum(int n) /* calculate 10^n */
{
	int  power = n, i;
	double total = 1, base = 10;

	if (n < 0)
	{
		base = (1/10);
		power *= -1;
	}

	for (i = 0 ; i < power ; i++)
	{
		total *= base;
		
	}
	
	return total;	

}

int flipDigits(int n)
{
	int flipped = 0, cur_dig;
	
	while (n != 0)
	{
		flipped *= 10;
		cur_dig = n % 10;
		// if (cur_dig == 0) 
		flipped += cur_dig;
		n /= 10;
	}
	
	return flipped;
	
		
}

void swapValues(int *num1, int *num2)
{
	int num_holder;
	
	num_holder = *num1;
	*num1 = *num2;
	*num2 = num_holder;
		
}

int holloWorld ()
{
	unsigned char hellow[] = { 0x22, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20,\
	 0x57, 0x6F, 0x7F, 0x72, 0x6C, 0x64, 0x21, 0x22, 0x0A, 0x00};
	 
	 
	 printf ("%s\n", hellow);
	 
	  return 0;
	  
}

