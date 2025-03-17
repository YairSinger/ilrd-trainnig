#include <stdio.h>  /*printf*/

#include "ws6.h"


int main()
{
	unsigned int x = 4, y = 3, z = 34;
	unsigned int a = 120, b = 22;
	unsigned int array[] = {2, 4, 6, 7, 8, 9, 11, 199, 200, 201,1048};
	/* Execrise 1 */
	/*if (Pow2(x, y) == 32)
	{
		printf("Pow2 passed Test\n");
	}
	else 
	{
		printf("Pow2 faild test\n");
	}
	
	/* Execrise 2 */
	/*if (IsPowerOfTwoWithLoop(x) == 1 && IsPowerOfTwoWithLoop(y) == 0)
	{
		printf("IsPowerOfTwoWithLoop passed Test\n");
	}
	else 
	{
		printf("IsPowerOfTwoWithLoop faild test\n");
	}
	
  	/*part 2 */
  	/*if (IsPowerOfTwoWithoutLoop(x) == 1 && IsPowerOfTwoWithoutLoop(y) == 0)
	{
		printf("IsPowerOfTwoWithoutLoop passed Test\n");
	}
	else 
	{
		printf("IsPowerOfTwoWithoutLoop faild test\n");
	}
	
	/* Execrise 3 */
	
  	/*if (AddOne(x) == 5 && AddOne(y) == 4)
	{
		printf("AddOne passed Test\n");
	}
	else 
	{
		printf("AddOne faild test\n");
	}
	
	/* Execrise 4 */
	/*Print3BitsOn(array,11);
	
	/* Execrsie 5 */

	/*if (ByteMirrorWithLoop(120) == 30)
	{
		printf("ByteMirrorWithLoop passed Test\n");
	}
	else 
	{
		printf("ByteMirrorWithLoop faild test\n");
	}*/
	
	if (ByteMirrorLut((unsigned char)120) == 30)
	{
		printf("ByteMirrorWithoutLoop passed Test\n");
	}
	else 
	{
		printf("ByteMirrorWithoutLoop faild test\n");
		printf("num 120: ");
		PrintFloatBits(120);
		printf("returned %d:", ByteMirrorLut(120));
		PrintFloatBits((float)ByteMirrorLut(120));
	}

	/* Execrise 6 */
	if (Are2And6BitsSet(z) == 1 && Are2And6BitsSet(y) != 1)
	{
		printf("Are2And6BitsSet passed Test\n");
	}
	else 
	{
		printf("Are2And6BitsSet faild test\n");
	}
	
	/* Part b */
	if (Are2Or6BitsSet(2) == 1 && Are2Or6BitsSet(32) == 1 && Are2Or6BitsSet(16) == 0)
	{
		printf("Are2Or6BitsSet passed Test\n");
	}
	else 
	{
		printf("Are2Or6BitsSet faild test\n");
	}
	
	/* Part c */
	
	if (Swap3And5Bits(120) == 108 && Swap3And5Bits(22) == 22 )
	{
		printf("Swap3And5Bits passed Test\n");
	}
	else 
	{
		printf("Swap3And5Bits faild test\n");
	}
	
	/* Execrise 7 */
	
	

	if (FindClosestDivisibleBy16(122) == 112 && FindClosestDivisibleBy16(100) == 96 )
	{
		printf("FindClosestDivisibleBy16 passed Test\n");
	}
	else 
	{
		printf("FindClosestDivisibleBy16 faild test\n");
	}
	 
	/* Execrise 8 */
	Swap(&a,&b);	
	if (a == 22 && b == 120 )
	{
		printf("Swap passed Test\n");
	}
	else 
	{
		printf("Swap faild test\n");
	}
	
	/* Execrise 9 */
	
	if (CountOnesWithLoop(50) == 3 && CountOnesWithLoop(120) == 4)
	{
		printf("CountOnesWithLoop passed Test\n");
	}
	else 
	{
		printf("CountOnesWithLoop faild test\n");
	}
	

	if (CountOnesWithoutLoop(50) == 3 && CountOnesWithoutLoop(120) == 4)
	{
		printf("CountOnesWithoutLoop passed Test\n");
	}
	else 
	{
		printf("CountOnesWithoutLoop faild test\n");
	}
  	PrintFloatBits(3.14);
  	if (SwapTwoBits(120,3,5) == 108 && SwapTwoBits(22,3,5) == 22)
	{
		printf("SwapTwoBits passed Test\n");
	}
	else 
	{
		printf("SwapTwoBits faild test. returned %ld expected %d\n returned %ld expected %d \n",SwapTwoBits(120,3,5),108, SwapTwoBits(22,3,5),22);
	}

	printf("200 - 1 equals: %d\n", SubtractOne(200));
  	
  	return 0;
  	
}



