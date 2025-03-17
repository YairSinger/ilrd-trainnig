/***********************************************************
*PROJECT: 
*
*WRITER: Yair Singer
*
*REVIEWER:Dor Dalmedigo 
*
*STATUS: Approved
*
*DATE: 16/7/23
***********************************************************/
#include <assert.h> 	/* assert */
#include <stdio.h>		/* printf */
#include "ws6.h"

#define BIT_2_AND_6_ON 34
#define BIT_2_ON 2
#define BIT_6_ON 32
#define BIT_3_ON 4
#define BIT_5_ON 16
#define BIT_3_AND_5_OFF 235
#define BIT_SIZE 8

/* Execrise 1 */
long Pow2(unsigned int x, unsigned int y)
{
	long result = x << y;
	return result;
}

/* Execrise 2 */
int IsPowerOfTwoWithLoop(unsigned int x)
{
	unsigned int mask = 1;
	size_t count;
	
	for(count = 0; mask <= x && count < 2; mask = (mask << 1))
	{
		if((mask & x) == mask)
		{	
			++count;
		}
	}
	
	if (1 == count)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int IsPowerOfTwoWithoutLoop(unsigned int x)
{
	 if (((x - 1) & x) == 0)
	 {
	 	return 1;
	 } 
	 else
	 {
	 	return 0;
	 } 	
}


/* Execrise 3 */
unsigned int AddOne(unsigned int x)
{
	unsigned int mask = 1;
	unsigned int result = x;

	
	for(mask = 1; !(mask & x) ; mask <<= 1)
	{
		/* turn off bits until first on */
		result = (result ^ mask);
	}
	result = result | mask;
	
	return result; 
}

/* Execrise 4 */
void Print3BitsOn(unsigned int array[], size_t length)
{
	unsigned int mask = 1;
	size_t i = 0, count = 0;
	 
	assert( NULL != array);
	
	for(i = 0; i < length; ++i)
	{	
		for(mask = 1, count = 0; mask <= array[i] && count < 4; mask <<= 1)
		{
			if((mask & array[i]) == mask)
			{
				++count;
			}
		}
		
		if (3 == count)
		{
			printf("%u has 3 bits on\n", array[i]);
		}
	}
}

/* Execrise 5 */
unsigned char ByteMirrorWithLoop(unsigned char x)
{
	unsigned char result = 0, mask = 1;
	size_t i = 0;
	
	for(result = 0; i < 8; ++i, x >>= 1)
	{
		result <<= 1;	
		result |= (mask & x);
		
	}
	return result;
}

unsigned char ByteMirrorLut(unsigned char x)
{
	unsigned bits[BIT_SIZE] = {128,64,32,16,8,4,2,1};
	return	(bits[0] & (x << 7))|
			(bits[1] & (x << 5))|
			(bits[2] & (x << 3))|
			(bits[3] & (x << 1))|
			(bits[4] & (x >> 1))|
			(bits[5] & (x >> 3))|
			(bits[6] & (x >> 5))|
			(bits[7] & (x >> 7));
			
		
}		
	

unsigned char ByteMirrorWithoutLoop(unsigned char x)
{
	size_t i = 0;
	static unsigned char arr[BIT_SIZE] = {0};
	static int was_initialezed = 0;
	
	if (was_initialezed == 0)
	{
		was_initialezed = 1;
		for (i = 0; i < BIT_SIZE; ++i)
		{ 
			arr[i] = ByteMirrorWithLoop((unsigned char)i);		
		}
	}
		
	return arr[x];
}



/* Execrise 6 */
int Are2And6BitsSet(unsigned char x)
{
	return (((x >> 1) & 1) && ((x >> 5) & 1));
}


int Are2Or6BitsSet(unsigned char x)
{
	
	return (((x >> 1) & 1) || ((x >> 5) & 1));
}

unsigned char Swap3And5Bits(unsigned char x)
{
	unsigned char other_bits_rep = BIT_3_AND_5_OFF;
	unsigned char bit3 = BIT_3_ON;
	unsigned char bit5 = BIT_5_ON;
	
	other_bits_rep &= x;
	bit3 &= x;
	bit3 <<= 2;
	bit5 &= x;
	bit5 >>= 2;
	
	return(other_bits_rep | bit3 | bit5);
}	

unsigned int SwapTwoBits(unsigned int num, size_t inx1, size_t inx2)
{
	/*unsigned int wo_swapped_bits = num & (~((unsigned int)1 << inx1)) & (~((unsigned int)1 << inx2));
	return wo_swapped_bits | ((num >> inx1) & 1) << inx2 | ((num >> inx2) & 1) << inx1;*/
	unsigned int mask = 0;
	if (((num >> inx1) & 1) != ((num >> inx2) & 1))
	{
		mask = (1 << inx1) | (1 << inx2);
		num ^= mask;
	}
	return num;

}
/* Execrise 7 */

unsigned int SubtractOne(unsigned int x)
{
	/*unsigned int mask = 1;
	
	while ((x & mask) == 0)
	{
		x = (x ^ mask);
		mask <<= 1;
		
	}
	
	x = x ^ mask;
	
	return x; */

	unsigned int res = x;
	size_t inx = 0;

	while (res >= x)
	{
		res ^= (1 << inx);
		++inx;
	}

	return res;
}

static int Is16Devisable(unsigned int x)
{
	 return ((x >> 4)<<4) == x ? 1 : 0;
}

unsigned int FindClosestDivisibleBy16(unsigned int x)
{
	unsigned int result = x;
	while (1 < result)
	{
		if (Is16Devisable(result))
		{
			return result;
		}
		else 
		{
			result = SubtractOne(result);
		}
	}
	
	return result;
}

/* Execrise 8 */
void Swap(unsigned int *num1, unsigned int *num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}

/* Execrise 9 */
size_t CountOnesWithLoop(unsigned int num)
{
	unsigned int mask = 1;
	size_t count;
	
	for(count = 0; mask <= num; mask <<= 1)
	{
		if((mask & num) == mask)
		{	
			++count;
		}
	}
	return count;
}

size_t CountOnesWithoutLoop(unsigned int num)
{
	num = (num & 0x55555555) + ((num >> 1) & 0x55555555); 
    num = (num & 0x33333333) + ((num >> 2) & 0x33333333); 
    num = (num & 0x0F0F0F0F) + ((num >> 4) & 0x0F0F0F0F);
    num = (num & 0x00FF00FF) + ((num >> 8) & 0x00FF00FF);
    num = (num & 0x0000FFFF) + ((num >> 8) & 0x00FF00FF);
    
    return (size_t)num;
}

void PrintFloatBits(float num)
{
    size_t i = 0;

    unsigned int bits = (unsigned int)&num;
    unsigned int mask = 1 << (sizeof(float) * 8 - 1);

    for (; i < sizeof(float) * 8; ++i)
    {
        printf("%d", (bits & mask) != 0);

        bits = bits << 1;
    }
    printf("\n");
}

