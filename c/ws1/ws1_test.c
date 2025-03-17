#include <stdio.h>
#include <assert.h>
#include "ws1.h"

void ex3 (void);	/*hellow world*/
void ex4 (void);	/* tenPowerNum */
void ex5(void);		/*flipDigits */
void ex6(void);		/*swapValues */


int main ()
{
	ex3(),
	ex4();
	ex5();
	ex6();
	printf("4 tests exe completed succsefully")
	 
	 
	 
	  return 0;  
}


void ex3 (void) 	/*hellow world*/
{

	holloWorld ();

}

void ex4 (void) 	/* tenPowerNum */
{

	
	assert(1 == tenPowerNum(0));
	 assert(0.00001 == tenPowerNum(-5)); 
	assert(100000 == tenPowerNum(5));
		
	 
	 

}

void ex5(void)		/*flipDigits */
{

	assert(1234 == flipDigits(4321));
	assert(1 ==flipDigits(100));

}

void ex6(void)		/*swapValues */
{
	int num1 = 30, num2 =-5;
	int *ptr1 = &num1, *ptr2 = &num2;
	swapValues (ptr1, ptr2);
	
	assert(-5 == num1);
	assert(30 == num2);
	
}


