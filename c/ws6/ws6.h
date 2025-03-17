#include <stddef.h> 	/*size_t */



#ifndef __WS6_H__
#define __WS6_H__

/* Execrise 1 */
long Pow2(unsigned int x, unsigned int y);

/* Execrise 2 */
int IsPowerOfTwoWithLoop(unsigned int x);
int IsPowerOfTwoWithoutLoop(unsigned int x);

/* Execrise 3 */
unsigned int AddOne(unsigned int x);

/* Execrise 4 */
void Print3BitsOn(unsigned int array[], size_t length);

/* Execrise 5 */
unsigned char ByteMirrorWithLoop(unsigned char x);
unsigned char ByteMirrorWithoutLoop(unsigned char x);
unsigned char ByteMirrorLut(unsigned char x);

/* Execrise 6 */
int Are2And6BitsSet(unsigned char x);
int Are2Or6BitsSet(unsigned char x);
unsigned char Swap3And5Bits(unsigned char x);

/* Execrise 7 */
unsigned int FindClosestDivisibleBy16(unsigned int x);

/* Execrise 8 */
void Swap(unsigned int *num1, unsigned int *num2);

/* Execrise 9 */
size_t CountOnesWithLoop(unsigned int num);
size_t CountOnesWithoutLoop(unsigned int num);

/* Execrise 10 */
void PrintFloatBits(float num);
unsigned int SwapTwoBits(unsigned int num, size_t inx1, size_t inx2);
/* Remove later 
unsigned char SwapTwoBits(unsigned char x,unsigned int index1, unsigned int index2);
 */
unsigned int SubtractOne(unsigned int x);

#endif /*__WS6_H__*/

