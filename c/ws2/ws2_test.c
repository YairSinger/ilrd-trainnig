#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ws2.h"

void SwapValuesTest(void);	
void CopyArrayTest (void);	
void PrintAdressesTest(void);
void SwapsTypeTPointersTest();


int main ()
{
	
	
	SwapValuesTest();	
	CopyArrayTest();	
	PrintAdressesTest();	
	SwapsTypeTPointersTest();	
	
	
	  return 0;  
}


void SwapValuesTest()	
{
	int num1 = 30, num2 =-5;
	
	printf("before swap num1 = %d, num2 = %d\n", num1, num2);
	swapValues (&num1, &num2);
	printf("after swap num1 = %d, num2 = %d\n", num1, num2);
	printf("swap two ints passed\n\n");
}

void CopyArrayTest ()	
{
	int i;
	int arr_source[] = {1, 2, 3, 4};
	int *copyied_arrey = copyArray(arr_source,4) ;
	
	
	for (i = 0 ; i < 4 ; i++)
	{
		printf("source arrey  arr[%d],%d\n", i,   arr_source[i]);
		printf("copyied arrey arr[%d],%d\n", i,   copyied_arrey[i]);
	}
	free(copyied_arrey);
	copyied_arrey = NULL;
	printf("copy an array passed\n\n");
}

void PrintAdressesTest()	
{
	printAdresses();
	printf("print addresses passed\n\n");
}


void SwapsTypeTPointersTest()
{
	size_t  a = 100, b = 200;
	size_t *p_a = &a, *p_b = &b;
	size_t **p_p_a = &p_a, **p_p_b = &p_b;

	printf("adresses before swap,a %p, b %p \n", (void *)&a,(void *)&b);
	printf("adresses  pointers before swap,a %p, b %p \n", (void *)&p_a,(void *)&p_b);
	printf("value in pointers before swap,a %lu, b %lu \n", *p_a,*p_b);
	SwapsTypeTPointers(p_p_a, p_p_b);
	printf("adresses  pointers after swap,a %p, b %p \n", (void *)&p_a,(void *)&p_b);
	printf("value in pointers after swap,a %lu, b %lu \n", *p_a,*p_b);
	printf("swap size_t pointers passed\n\n");
	

}

void IsPalindromeTest()
{
	char str1[] = "abniinba", str2[] = "abniimba", str3[] = "a";
	
	if (0 == IsPalindrome (str1))
	{
		printf("%s is a palindrome!\n" , str1);
	}
	else 
	{
		printf("%s is  not apalindrome \n" , str1);
	}
	
	if (0 == IsPalindrome (str2))
	{
		printf("%s is a palindrome!\n" , str2);
	}
	else 
	{
		printf("%s is  not apalindrome \n" , str2);
	}
	
	if (0 == IsPalindrome (str3))
	{
		printf("%s is a palindrome!\n" , str3);
	}
	else 
	{
		printf("%s is  not apalindrome \n" , str3);
	}
}


