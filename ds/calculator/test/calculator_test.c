#include <stdio.h> 	/* printf */
#include <stdlib.h> /*srand */
#include <time.h> 	/*clock_t, clock() */
#include "calculator.h"


#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"




void TestAddSub();
void TestBrackets();
void TestManual();
static const char* GetCalcStatus(calc_status_t status)
{
	switch (status)
	{
		case CALC_SUCCESS: return "CALC_SUCCESS";
		case CALC_SYNTEX_ERROR: return "CALC_SYNTEX_ERROR";
		case CALC_MATH_ERROR: return "CALC_MATH_ERROR";
		case CALC_ALLOC_FAILED: return "CALC_ALLOC_FAILED";
	}

}





int main()
{
	TestAddSub();
	TestBrackets();
	TestManual();
	
	return 0;
}

/********************/

void TestAddSub()
{
	char *str1[] = 
		{"0+0","0+1","2+3","-2+3","3-1","3-5","3+5+7","8-5-3","3+-3","3+-4",
	"--4","++4", "4", "6---4"	
			};
	double expected1[] = {0,1,5,1,2,-2,15,0,0,-1,0,0,4,0};
	calc_status_t expec_stats [] = 	
	{CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS,
	CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS,CALC_SYNTEX_ERROR,
	CALC_SYNTEX_ERROR,CALC_SUCCESS,CALC_SYNTEX_ERROR};
	double result;
	
	
	size_t i = 0;
	calc_status_t status = CALC_SUCCESS;
	int fails = 0;
		 
	for (i = 0; i < 14; ++i)
 	{
 		status = Calc(str1[i], &result);
 		if (expected1[i] != result || status != expec_stats[i])
 		{
 			++fails;
			printf(RED"Add Sub failed\n"RESET_COLOR);
 			printf("status is %s result of %s is:\n %f vs %f expected \n",GetCalcStatus(status), str1[i], result,expected1[i]);
 		}
 		
 	}
	
	if (0 == fails)
	{
		printf(GREEN"Calculator Add brackets Pass PASSED\n"RESET_COLOR);
	}
	
	
}

void TestBrackets()
{
	char *str1[] = 
		{"4+(5+4)","(3+4)", "4*3+5", "4*(3+5)", "4(3+5)","4+3*(-4+3)",
		"3+(((5)))"
			};
	double expected1[] = {13,7,17,32,32,1,8};
	calc_status_t expec_stats [] = 	
	{CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS,CALC_SUCCESS};
	double result;
	
	
	size_t i = 0;
	calc_status_t status = CALC_SUCCESS;
	int fails = 0;
		 
	for (i = 0; i < 7; ++i)
 	{
 		status = Calc(str1[i], &result);
 		if (expected1[i] != result || status != expec_stats[i])
 		{
 			++fails;
			printf(RED"brackets failed\n"RESET_COLOR);
 			printf("status is %s result of %s is:\n %f vs %f expected \n",GetCalcStatus(status), str1[i], result,expected1[i]);
 		}
 		
 	}
	
	if (0 == fails)
	{
		printf(GREEN"Calculator Add Pass PASSED\n"RESET_COLOR);
	}
	
	
}

void TestManual()
{
	char str1[20] = {'\0'};
	double result = 0;
	calc_status_t status = CALC_SUCCESS;
	
	while ('$' != *str1 )
	{
		printf("please insert expression or '$' to end loop:\n");
		scanf("%19s", str1);
		status = Calc(str1, &result);
		printf("ex %s resulted:\n status is %s,\n and value: %f\n",str1,GetCalcStatus(status), result);
				
	}
}

