#include <stdio.h> 	/* printf, size_t		*/
#include <string.h> /* memcmp 				*/
#include <stdlib.h> /* malloc , free, rand, srand			*/
#include <time.h>   /* time , clock */
#include <sys/types.h> /* ssize_t*/
#include <math.h> /* pow */

#include "calculator.h" 		
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red 	  */
#define GREEN   "\033[32m"      /* Green */
#define BLUE 	"\033[34m"      /* Blue   */

#define WORD_SIZE sizeof(size_t)
#define MAX_RANGE  2500
#define MIN_RANGE  -2500
#define PRINT 1
#define PRINT_ERR 1
#define GLOBAL_ARR_SIZE 2500


#define PREC  0.000001

static int TestCalc(calc_status_t expected_status,
			 char *str, double expected, int line);
static int ArrMax(int arr[], size_t size);
static void InitIntArrRandom(int arr[], size_t from, size_t to);
static int CompareResults(void *expected, void *result, size_t element_size, int line);
static void ShowResetStatus();
static void PrintName(const char *name ,int line);
static void IntExpected(int *expected , int *result);
static void PrintLine(int line);
static void PrintSizeT(size_t t);
static size_t SizeAllignedToWordSize(size_t size);
static void SizeTExpected(size_t *expected , size_t *result);
static void PrintIntArrs(int *exp_arr ,int *result_arr, size_t size);
static int CmpFunc(const void *lhs,const void *rhs);
static int CompareSsizeT(ssize_t expected, ssize_t result, int line);
static ssize_t SlowAndSteadySearch(int arr[], size_t size, int target);
static void CompareInt(int expected, int result, int line);
static void InitIntArr(int arr[], size_t from, size_t to);
static int ArrMin(int arr[], size_t size);
static int CompareSizes(size_t expected, size_t result, int line);
static int CompareSizesSilently(size_t expected, size_t result, int line);
static int CompareIntSilently(int expected, int result, int line);
static int ActionFunc(void *tree_data, void *user_params);
static int ActionFunc2(void *tree_data, void *user_params);
static int ActionFunc3(void *data, void *param);
static int ActionFunc4(void *data, void *param);
static void InitArrRandomEven(int arr[], size_t from, size_t to);
static int CompareSSizesSilently(ssize_t expected, ssize_t result, int line);
static int CompareDouble(double expected, double result, int line);

/* temporary test functions */
static int TestRtnStatus(calc_status_t expected_status, char *str, int line);
static int TestResValue(double expected, char *str, int line);

size_t error = 0, test_num = 0;



int main()
{
	size_t element_size = 0, exp = 0, result = 0, i = 0, j = 0,
		   size = 0, size_1 = 0, size_2 = 0, i_flag = 0, loops = 0,
				loops2 = 0, i_2 = 0, arr_size = 0;
	int int_result = 0, int_exp = 0, param = 0, status = 0, line = 0,
		is_sorted = 0, is_found = 0, expected = 0;
	double exp_dbl = 0.0;
	void *result_ptr = NULL, *expected_ptr = NULL;
	void *element_1 = (void *)malloc(100);
	void *element_2 = (void *)malloc(100);
	void *element_3 = (void *)malloc(100);
	void *element_4 = (void *)malloc(100);
	int *l_arr = NULL, *r_arr = NULL;
		
	char *str = NULL;

	static int test_int[5000] = {0};
	static int test_int_2[5000] = {0};
	static int test_int_3[5000] = {0};

	clock_t begin = clock();	
	clock_t end = clock();	
	
	
	
	(void)element_size;
	(void)i;
	(void)result;
	(void)exp;
	(void)test_num;
	(void)error;
	(void)element_1;
	(void)element_2;
	(void)PrintName;
	(void)ShowResetStatus;
	(void)CompareResults;
	(void)result_ptr;
	(void)SizeTExpected;
	(void)IntExpected;
	(void)PrintSizeT;
	(void)SizeAllignedToWordSize;
	(void)CompareSsizeT;
	(void)size;
	(void)size_1;
	(void)size_2;
	(void)i_flag;
	(void)int_result;
	(void)int_exp;
	(void)param;
	(void)expected_ptr;
	(void)test_int;
	(void)test_int_2;
	(void)status;
	(void)CompareInt;
	(void)PrintIntArrs;
	(void)line;
	(void)end;
	(void)begin;
	(void)r_arr;
	(void)l_arr;
	(void)is_sorted;
	(void)CmpFunc;
	(void)SlowAndSteadySearch;
	(void)ArrMax;
	(void)ArrMin;
	(void)ActionFunc2;
	(void)test_int_3;
	(void)is_found;
	(void)i_2;
	(void)loops2;
	(void)loops;
	(void)j;
	(void)CompareSizes;
	(void)CompareSizesSilently;
	(void)CompareIntSilently;
	(void)ActionFunc;
	(void)ActionFunc2;
	(void)ActionFunc3;
	(void)ActionFunc4;
	(void)InitIntArr;
	(void)InitIntArrRandom;
	(void)InitArrRandomEven;
	(void)CompareSSizesSilently;
	(void)arr_size;
	srand(time(NULL));	
/*****************************************************************************/	
	
	
	
/*****************************************************************************/	
	
	PrintName("Test '+' and '-'", __LINE__);
	expected = CALC_SUCCESS;
	TestRtnStatus(expected, str = "4 + 5", __LINE__);		
	TestResValue(exp_dbl = 4 + 5, str , __LINE__);	
	
	TestCalc(expected = CALC_SUCCESS, str = "4 + 5",exp_dbl = 4 + 5, __LINE__);
	
	TestRtnStatus(expected, str = "4 + 9", __LINE__);
	TestResValue(exp_dbl = 4 + 9, str, __LINE__);

	TestRtnStatus(expected, str = "1 + 3", __LINE__);
	TestResValue(exp_dbl = 1 + 3, str, __LINE__);

	TestRtnStatus(expected, str = "1 - 5", __LINE__);
	TestResValue(exp_dbl = 1 - 5, str, __LINE__);
	
	TestRtnStatus(expected, str = "2 - 3", __LINE__);
	TestResValue(exp_dbl = 2 - 3, str, __LINE__);
	
	TestRtnStatus(expected, str = "9 - 4", __LINE__);
	TestResValue(exp_dbl = 9 - 4, str, __LINE__);
	
	TestRtnStatus(expected, str = "9 - 4 + 5", __LINE__);
	TestResValue(exp_dbl = 9 - 4 + 5, str, __LINE__);

	TestRtnStatus(expected, str = "9 - 4 + 9", __LINE__);
	TestResValue(exp_dbl = 9 - 4 + 9, str, __LINE__);
	
	TestRtnStatus(expected,str =  "9 - 4 + 11", __LINE__);
	TestResValue(exp_dbl = 9 - 4 + 11, str, __LINE__);
	
	
	TestRtnStatus(expected, str = "9000 - 4 + 9", __LINE__);
	TestResValue(exp_dbl = 9000 - 4 + 9, str, __LINE__);
	
	TestRtnStatus(expected, str = "9000 - 4 + 9 + 99 +  55 +-9", __LINE__);
	TestResValue(exp_dbl = 9000 - 4 + 9 + 99 +  55 +-9, str, __LINE__);
	
	TestRtnStatus(expected, str = "+9000 - 4 + 9 + 99 +  55 +-9", __LINE__);
	TestResValue(exp_dbl = +9000 - 4 + 9 + 99 +  55 +-9, str, __LINE__);

	TestRtnStatus(expected,str = "-9000 - 4 + 9 + 99 +  55 +-9", __LINE__);
	TestResValue(exp_dbl = -9000 - 4 + 9 + 99 +  55 +-9, str, __LINE__);


	TestRtnStatus(expected, str = "9000 - 4 + 9 + -99 +  55 +-9", __LINE__);
	TestResValue(exp_dbl = 9000 - 4 + 9 + -99 +  55 +-9, str, __LINE__);


	TestRtnStatus(expected,str =  "  9000 - 4 + 9 + -99 +  55 +-9 ", __LINE__);
	TestResValue(exp_dbl = 9000 - 4 + 9 + -99 +  55 +-9, str, __LINE__);


	TestRtnStatus(expected, str = "  9000 - 4 + 0 + -99 +  0 +-0 ", __LINE__);
	TestResValue(exp_dbl = 9000 - 4 + 0 + -99 +  0 +-0, str, __LINE__);

	TestRtnStatus(expected,str =  "9 - 9", __LINE__);
	TestResValue(exp_dbl = 0, str, __LINE__);

	expected = CALC_SYNTEX_ERROR;
	TestRtnStatus(expected, "", __LINE__);
	TestRtnStatus(expected, "1000 -", __LINE__);
	TestRtnStatus(expected, "1000 A", __LINE__);
	TestRtnStatus(expected, "0000 - 4 + 9 + 99    55 +-9", __LINE__);
	TestRtnStatus(expected, "9000 - 4 + 9 + 99  +++ 55 +-9", __LINE__);
	TestRtnStatus(expected, "---9000 - 4 + 9 + 99   55 +-9", __LINE__);
	TestRtnStatus(expected, "--9000 - 4 + 9 + 99   55 +-9", __LINE__);
	TestRtnStatus(expected, "800  4  9  99 5 +-9", __LINE__);
	TestRtnStatus(expected, "7000  4  9  99 5 +-9", __LINE__);
	TestRtnStatus(expected, "6000  + 4 - 9  + 99 -  5 +-A9", __LINE__);
	TestRtnStatus(expected, "5000  + 4 - 9  + 99 #-  5 +-9", __LINE__);
	TestRtnStatus(expected, "4000  + 4 - 9  + 99 ==-  5 +-9", __LINE__);
	TestRtnStatus(expected, "3000  + 5 +-9 -$ 3", __LINE__);
	TestRtnStatus(expected, "2000  + 5 +-9 -$ 3kjaetjblv;nhu1", __LINE__);
	TestRtnStatus(expected, "+& -  9000  + 5 +-9 ", __LINE__);
	TestRtnStatus(expected, "9 - 4 + 11 + +", __LINE__);
	TestRtnStatus(expected, "9 - 4 + 11 + + ", __LINE__);
	
	ShowResetStatus();
	
/*****************************************************************************/	
	
	PrintName("Test '*'", __LINE__);
    TestCalc(CALC_SUCCESS, "4 * 5", 4 * 5, __LINE__);
    TestCalc(CALC_SUCCESS, "4 * 5 * 5", 4 * 5 * 5, __LINE__);
    TestCalc(CALC_SUCCESS, "4 * 4 * 3 * 2", 4 * 4 * 3 * 2, __LINE__);
    TestCalc(CALC_SUCCESS, "9.3 * 8.5", 9.3 * 8.5, __LINE__);
    TestCalc(CALC_SUCCESS, "4 * 5 * 0", 4 * 5 * 0, __LINE__);
    TestCalc(CALC_SUCCESS, "4 * 5 * -1", 4 * 5 * -1, __LINE__);
    TestCalc(CALC_SUCCESS, "-1 * -3 * 55.3", -1 * -3 * 55.3, __LINE__);
    TestCalc(CALC_SUCCESS, "0.0 * 0.0 * 89999.33", 0.0 * 0.0 * 89999.33, __LINE__);
    TestCalc(CALC_SUCCESS, "75.444333222 * 99.111122202",
							 75.444333222 * 99.111122202, __LINE__);
    TestCalc(CALC_SUCCESS, "-1 * 1", -1 * 1, __LINE__);

	expected = CALC_SYNTEX_ERROR;
	TestRtnStatus(expected, "9 - 4 + 11 * + ", __LINE__);
	TestRtnStatus(expected, "9 * * 3 ", __LINE__);
	TestRtnStatus(expected, "* 9   ", __LINE__);
	TestRtnStatus(expected, "* -19   ", __LINE__);
	TestRtnStatus(expected, "-9 * --5   ", __LINE__);
	TestRtnStatus(expected, "-9 * -5 * 3 * ", __LINE__);
	TestRtnStatus(expected, "*", __LINE__);
	
	
	ShowResetStatus();
	

/*****************************************************************************/


/*****************************************************************************/	
	
	PrintName("Integrate '*' , '+' , '-'", __LINE__);
    TestCalc(CALC_SUCCESS, "4 * 5 + 3 - 2 - 1", 4 * 5 + 3 - 2 - 1, __LINE__);
    TestCalc(CALC_SUCCESS, "1 + 2 * 3 + 4", 1 + 2 * 3 + 4, __LINE__);
    TestCalc(CALC_SUCCESS, "-5.5 * -4.4 * -3.3 + 2 + 9 * 5.5",
						 -5.5 * -4.4 * -3.3 + 2 + 9 * 5.5, __LINE__);
    TestCalc(CALC_SUCCESS, "-0 + 9.3 * 8.5", -0 + 9.3 * 8.5, __LINE__);
    
    TestCalc(CALC_SUCCESS, "-3.4578 * 2.111 + 22000.3",
     -3.4578 * 2.111 + 22000.3, __LINE__);
    
    TestCalc(CALC_SUCCESS, "4.1978 * 342.3 * -11 + 1",
     4.1978 * 342.3 * -11 + 1, __LINE__);
    
    TestCalc(CALC_SUCCESS, "-1  + 1 * 5 * 0 ", 
	-1  + 1 * 5 * 0, __LINE__);
	
    TestCalc(CALC_SUCCESS, "-7.7130022 + 1 * 5 * -2 * 0",
	-7.7130022 + 1 * 5 * -2 * 0 , __LINE__);

    TestCalc(CALC_SUCCESS, "2 * 2.2 + 4 * 0 * -1",
							 2 * 2.2 + 4 * 0 * -1, __LINE__);
    TestCalc(CALC_SUCCESS, "-1 * -1 * -1",-1 * -1 * -1, __LINE__);

	
	ShowResetStatus();
	

/*****************************************************************************/

/*****************************************************************************/	
	
	PrintName("Test Parenthases", __LINE__);
    TestCalc(CALC_SUCCESS, "(3 + 1)", 3 + 1, __LINE__);
    TestCalc(CALC_SUCCESS, "(-9 + 3) + 4", (-9 + 3) + 4, __LINE__);
    TestCalc(CALC_SUCCESS, "(-9) * (-1)", (-9) * (-1), __LINE__);
    TestCalc(CALC_SUCCESS, "(2.55 * -2048.9301112)", (2.55 * -2048.9301112), __LINE__);
    TestCalc(CALC_SUCCESS, "(8.123456 - 0.44) * 5", (8.123456 - 0.44) * 5, __LINE__);
    TestCalc(CALC_SUCCESS, "((-1) * (-3)) * 55.3", ((-1) * (-3)) * 55.3, __LINE__);
    TestCalc(CALC_SUCCESS, "1.1 * (0.44 - (255.7 * (0.8 - 0.9)))",
						 1.1 * (0.44 - (255.7 * (0.8 - 0.9))), __LINE__);
    TestCalc(CALC_SUCCESS, "0.1 * 3 - (2.5 + 4 * (-5))",
							 0.1 * 3 - (2.5 + 4 * (-5)), __LINE__);
    TestCalc(CALC_SUCCESS, "(-1) * (1) * (0 - 0)", 0, __LINE__);
    TestCalc(CALC_SUCCESS, "(-1) * (1) * (1-1)", 0, __LINE__);
    TestCalc(CALC_SUCCESS, "((-0) * (((1)))) * (0 - 0)", 0, __LINE__);
    TestCalc(CALC_SUCCESS, "(0.33 * (0.22 - (15 * (5 - (3 + (0.2 - 4))))))",
					 (0.33 * (0.22 - (15 * (5 - (3 + (0.2 - 4)))))), __LINE__);
	TestCalc(CALC_SUCCESS, "9 - (4 - 4)", 9 - (4 - 4), __LINE__);
	
	/* FIXME - implemntation defined, some might do it differently */
	expected = CALC_SYNTEX_ERROR;
	TestRtnStatus(expected, "9 + 4 ) ", __LINE__);
	TestRtnStatus(expected, "9 + 4 + ) ", __LINE__);
	TestRtnStatus(expected, "(9 * 3 ", __LINE__);
	TestRtnStatus(expected, "9) + 5", __LINE__);
	TestRtnStatus(expected, "-14 + (3 * 3 - (5 * 5 - 1 )))", __LINE__);
	TestRtnStatus(expected, "((()))", __LINE__);
	TestRtnStatus(expected, "(((-14.3 + 5 * 2) ", __LINE__);
	TestRtnStatus(expected, "(-5) + 1 * (-3) + 4(", __LINE__);
	TestRtnStatus(expected, "(-5) + 1 * (-3) + 4)", __LINE__);
	
	
	ShowResetStatus();
	

/*****************************************************************************/

/*****************************************************************************/	
	
	PrintName("Test '/'", __LINE__);
    TestCalc(CALC_SUCCESS, "3 / 1", 3 / 1, __LINE__);
    TestCalc(CALC_SUCCESS, "1 / 3", 1.0 / 3, __LINE__);
    TestCalc(CALC_SUCCESS, "1 / (3 / 1)", 1.0 / (3.0 / 1.0), __LINE__);
    TestCalc(CALC_SUCCESS, "1 / 3 / 1", 1.0 / 3.0 / 1.0, __LINE__);
    TestCalc(CALC_SUCCESS, "(3.88 / 5.25)", (3.88 / 5.25), __LINE__);
    TestCalc(CALC_SUCCESS, "(8.123456 / 0.44) * 5", (8.123456 / 0.44) * 5, __LINE__);
    TestCalc(CALC_SUCCESS, "((-1) * (-3)) / 55.3", ((-1) * (-3)) / 55.3, __LINE__);
    TestCalc(CALC_SUCCESS, "1.1 / (0.44 - (255.7 / (0.8 - 0.9)))",
						 1.1 / (0.44 - (255.7 / (0.8 - 0.9))), __LINE__);
    TestCalc(CALC_SUCCESS, "1.1 * (0.44 / (255.7 * (0.8 / 0.9)))",
						 1.1 * (0.44 / (255.7 * (0.8 / 0.9))), __LINE__);						
    TestCalc(CALC_SUCCESS, "0.1 / 3 - (2.5 + 4.0 / (-5))",
							 0.1 / 3 - (2.5 + 4.0 / (-5)), __LINE__);
    TestCalc(CALC_SUCCESS, "(-1) * (1) / (0 - 1)", (-1.0) * (1.0) / (0 - 1), __LINE__);
    TestCalc(CALC_SUCCESS, "(-1) * (1) * (1.1/1.1)", (-1) * (1) * (1.1/1.1), __LINE__);
    TestCalc(CALC_SUCCESS, "((-0) / (((1)))) / (5 - 7)", 0, __LINE__);
    TestCalc(CALC_SUCCESS, "(0.33 * (0.22 / (15 * (5 - (3 + (0.2 / 4))))))",
					 (0.33 * (0.22 / (15 * (5 - (3 + (0.2 / 4)))))), __LINE__);
    TestCalc(CALC_SUCCESS, "9.2 * 8.5 / (3.0 + 1.0 / 4) / 85.4 / -11",
						9.2 * 8.5 / (3.0 + 1.0 / 4) / 85.4 / -11, __LINE__);
	
	/* FIXME - implemntation defined, some might do it differently */
	expected = CALC_SYNTEX_ERROR;
	TestRtnStatus(expected, "9 / 4 ) ", __LINE__);
	TestRtnStatus(expected, "9 - 4 / ) ", __LINE__);
	TestRtnStatus(expected, "(9 / 3 ", __LINE__);
	TestRtnStatus(expected, "9) / 5", __LINE__);
	TestRtnStatus(expected, "-14 + (3 * 3 - (5 / 5 / 1 )))", __LINE__);
	TestRtnStatus(expected, "(((/)))", __LINE__);
	TestRtnStatus(expected, "(((-14.3 // 5 * 2) ", __LINE__);
	TestRtnStatus(expected, "(-5) / 1 * (-3) / 4(", __LINE__);
	TestRtnStatus(expected, "(-5) + 1 / (-3) / 4)", __LINE__);
	
	
	expected = CALC_MATH_ERROR;
	TestRtnStatus(expected, "9 / 0", __LINE__);
	TestRtnStatus(expected, "9 / (4 - 4)", __LINE__);
	TestRtnStatus(expected, "(9 / (3 - 2 - 1))", __LINE__);
	TestRtnStatus(expected, "9 / (5 * 0)", __LINE__);
	TestRtnStatus(expected, "-14 + (3 * 3 - (5 / 5 / 0 )))", __LINE__);
	TestRtnStatus(expected, "(((1/0)))", __LINE__);
	TestRtnStatus(expected, "(((-14.3 / (5 * 2 - 10)))) ", __LINE__);
	TestRtnStatus(expected, "4 + 4 + 4 + 4 + 4 + 4.44 / 0", __LINE__);
	TestRtnStatus(expected, "3 / (3 * (3 / (3 + 3 + 6 - 12)))", __LINE__);
	
	
	ShowResetStatus();
	

/*****************************************************************************/


/*****************************************************************************/	
	
	/* FIXME - this is an advanced method, if you didn't do it - 
	   just comment it out */
	PrintName("Advanced - exponentiation ('^')", __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ 1", pow(3, 1), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ 2", pow(3, 2), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ 3", pow(3, 3), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ 4", pow(3, 4), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ 5", pow(3, 5), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ 6", pow(3, 6), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ 7", pow(3, 7), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ 8", pow(3, 8), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ 9", pow(3, 9), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ 10",pow(3, 10), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ 0",pow(3, 0), __LINE__);
    TestCalc(CALC_SUCCESS, "0 ^ 0",pow(0, 0), __LINE__);
    TestCalc(CALC_SUCCESS, "1 ^ 0",pow(1, 0), __LINE__);
    TestCalc(CALC_SUCCESS, "0 ^ 1",pow(0, 1), __LINE__);
    TestCalc(CALC_SUCCESS, "9 ^ 1",pow(9, 1), __LINE__);
    TestCalc(CALC_SUCCESS, "1 ^ 1",pow(1, 1), __LINE__);

	/* integrate with all operators */
    TestCalc(CALC_SUCCESS, "(-3) ^ 1", pow(-3, 1), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ (-1)", pow(3, -1), __LINE__);
    TestCalc(CALC_SUCCESS, "(-3) ^ 2 * (3 - 1)", pow(-3, 2) * (2), __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ (2 ^ (84-83))", pow(3, (pow (2, 84 - 83))), __LINE__);
    TestCalc(CALC_SUCCESS, "-0.15 ^ 44 + 3", -pow(0.15, 44) + 3, __LINE__);
    TestCalc(CALC_SUCCESS, "-0.15 ^ 43 + 3", -pow(0.15, 43) + 3, __LINE__);
    TestCalc(CALC_SUCCESS, "3 * 4.2 ^ -4 / 13", 3.0 * pow(4.2, -4) / 13, __LINE__);
    TestCalc(CALC_SUCCESS, "3 * -4.2 ^ 4 / 13", 3.0 * -pow(4.2, 4) / 13, __LINE__);
    TestCalc(CALC_SUCCESS, "3 ^ (-10) * 4 - (3 + 4 + 5)",pow(3, -10) * 4 - (3 + 4 + 5), __LINE__);
    TestCalc(CALC_SUCCESS, "3.1 + 4.1 * 5.1 + 6.1 ^ 4",3.1 + 4.1 * 5.1 + pow(6.1, 4), __LINE__);
    TestCalc(CALC_SUCCESS, "3.1 + 4.1 * 5.1 + 6.1 ^ -4",3.1 + 4.1 * 5.1 + pow(6.1, -4), __LINE__);
    TestCalc(CALC_SUCCESS, "3.1 + 4.1 * 5.1 + 6.1 ^ (-4)",3.1 + 4.1 * 5.1 + pow(6.1, -4), __LINE__);
    TestCalc(CALC_SUCCESS, "0 ^ 4 * 3 / 2",pow(0, 4) * 3.0 / 2, __LINE__);
    TestCalc(CALC_SUCCESS, "((8 * 3) ^ -1) * ((3.3 ^ 4) + 8)",pow(8 * 3, -1) * (pow(3.3, 4) + 8), __LINE__);


	/* FIXME - implemntation defined, some might do it differently */
	expected = CALC_SYNTEX_ERROR;
	TestRtnStatus(expected, "0 ^ 3 ^ ) ", __LINE__);
	TestRtnStatus(expected, "9 - 4 ^ ) ", __LINE__);
	TestRtnStatus(expected, "9 ^ 3( ", __LINE__);
	TestRtnStatus(expected, "9) ^ 5", __LINE__);
	TestRtnStatus(expected, "-14 ^ (3 - 3 * (5 + 5 ^ 1 )))", __LINE__);
	TestRtnStatus(expected, "(((^)))", __LINE__);
	TestRtnStatus(expected, "(((-14.3 ^^ 5 * 2) ", __LINE__);
	TestRtnStatus(expected, "-14.3 ^^ 5 ", __LINE__);
	TestRtnStatus(expected, "(-5) / 1 ^ (-3) / 4(", __LINE__);
	TestRtnStatus(expected, "(-^5) + 1 / (-3) / (4)", __LINE__);
	
	
	expected = CALC_MATH_ERROR;
	TestRtnStatus(expected, "0 ^ -1", __LINE__);
	TestRtnStatus(expected, "(4 - 4) ^ -4", __LINE__);
	TestRtnStatus(expected, "(0 ^ ((3 - 2 - 1) - 1))", __LINE__);
	TestRtnStatus(expected, "(5 * 0) ^ (5 * 5 * -1)", __LINE__);
	TestRtnStatus(expected, "(-14 + 14) ^ (3 * 3 - (5 * 5))", __LINE__);
	TestRtnStatus(expected, "(((0 ^ -5)))", __LINE__);
	TestRtnStatus(expected, "(((-14.3 + 14.3) ^ (5 * 2 - 11))) ", __LINE__);
	TestRtnStatus(expected, "4 + 4 + 4 + 4 + 4 + (2 * 2 - 4 / 4 - 3) ^ (3 - 5)", __LINE__);
	TestRtnStatus(expected, "3 / (3 ^ 2 - 9)", __LINE__);
	TestRtnStatus(expected, "3 / (0 ^ - 9)", __LINE__);
	
	
	ShowResetStatus();
	

/*****************************************************************************/


	
	free(element_1);
	free(element_2);
	free(element_3);
	free(element_4);
	return 0;
}

static int TestCalc(calc_status_t expected_status,
			 char *str, double expected, int line)
{
	int err = 0;
	
	err += TestResValue(expected, str, line);
	err += TestRtnStatus(expected_status, str, line);
	
	return err;
}

static int TestResValue(double expected, char *str, int line)
{
	double test_double = 0.0;
	int res = 0;
	Calc(str, &test_double);
	
	res = CompareDouble(expected,test_double , line);
	if (0 != res)
	{
		printf(RED"Failed achieving correct result:\n");
		printf("expected : %f , got : %f, input : %s\n"RESET,
		expected, test_double, str); 
	}

	return res;
	
}

static int TestRtnStatus(calc_status_t expected_status, char *str, int line)
{
	double d = 0.0;
	int res = 0;
	static char *enums[] = {"CALC_SUCCESS", "CALC_SYNTEX_ERROR",
						    "CALC_MATH_ERROR", "CALC_ALLOC_FAILED"}; 
	calc_status_t ret_status = Calc(str, &d);
	
	res = CompareIntSilently(expected_status, ret_status, line);
	if (0 != res)
	{
		printf(RED "Failed retrieve correct status:\n");
		printf("expected : %s , got : %s, input : %s\n" RESET, 
		enums[expected_status],	enums[ret_status], str);
	}

	return res;
}

static int ActionFunc3(void *data, void *param)
{
	if(NULL == data)
	{
		return 1;
	}
	
	*(int *)data += *(int *)param;
	
	return 0;	
}

static int ActionFunc4(void *data, void *param)
{
	(void)data, (void)param;
	return 1;
}

static int ArrMin(int arr[], size_t size)
{
	size_t i = 0;
	int min_value = arr[0];
	
	for (i = 1; i < size; ++i)
	{
		min_value = arr[i] < min_value ? arr[i] : min_value; 
	}
	
	return min_value;
}

static int ArrMax(int arr[], size_t size)
{
	size_t i = 0;
	int max_value = arr[0];
	
	for (i = 1; i < size; ++i)
	{
		max_value = arr[i] > max_value ? arr[i] : max_value; 
	}
	
	return max_value;
}

static void InitIntArrRandom(int arr[], size_t from, size_t to)
{
	size_t i = 0;
	int lut[MAX_RANGE - MIN_RANGE] = {0};
	
	for (i = from; i < to; ++i)
	{	
		arr[i] = (rand() % (MAX_RANGE - MIN_RANGE )) + MIN_RANGE;
		while (1 == lut[arr[i] - MIN_RANGE])
		{
			arr[i] = (rand() % (MAX_RANGE - MIN_RANGE )) + MIN_RANGE;
		}
		lut[arr[i] - MIN_RANGE] = 1;	
	}
}

static void InitArrRandomEven(int arr[], size_t from, size_t to)
{
	size_t i = 0;
	int lut[MAX_RANGE - MIN_RANGE] = {0};
	
	for (i = from; i < to; ++i)
	{	
		arr[i] = (((rand() % (MAX_RANGE - MIN_RANGE )) + MIN_RANGE) / 2) * 2;
		while (1 == lut[arr[i] - MIN_RANGE])
		{
			arr[i] = (rand() % (MAX_RANGE - MIN_RANGE )) + MIN_RANGE;
		}
		lut[arr[i] - MIN_RANGE] = 1;	
	}
}

static void InitIntArr(int arr[], size_t from, size_t to)
{
	size_t i = 0;
	for (i = from; i <= to; ++i)
	{
		arr[i] = (int)i;
	}
}

static int CmpFunc(const void *lhs,const void *rhs)
{
	return *(int *)lhs - *(int *)rhs;
}

static int ActionFunc(void *tree_data, void *user_params)
{
	*(int *)tree_data += *(int *)user_params; 
	return 0;
}

static int ActionFunc2(void *tree_data, void *user_params)
{
	static size_t i = 0;
	int result = 0;
	
	if (20 == i)
	{
		i = 0;
	}
	
	*(int *)tree_data += *(int *)user_params, ++i;
	
	if (20 == i)
	{
		result = (int)i;
	}
	
	return result;
}


static void PrintIntArrs(int *exp_arr ,int *result_arr, size_t size)
{
	size_t i = 0;
	
	printf(BLUE "expected:\n" RESET);
	for (i = 0; i < size; ++i)
	{
		printf(BLUE " %d, " RESET , exp_arr[i] );	
	}
	
	printf(BLUE "\ngot:\n" RESET);
	for (i = 0; i < size; ++i)
	{
		printf(BLUE " %d, " RESET , result_arr[i] );	
	}
	
	printf("\n");
}

static void SizeTExpected(size_t *expected , size_t *result)
{
	
	if ((NULL == expected || NULL == result) && (result != expected))
	{
		if (NULL == result)
		{
			printf(RED "(expected : %lu , got : NULL)\n" RESET , *expected);	
			return;
		}
		else
		{
			printf(RED "(expected : NULL , got : %lu)\n" RESET , *result);
			return;
		}
	}	
	
	if ((expected == NULL) && (expected == result))
	{
		return;
	}
	
	if (*expected != *result)
	{
		printf(RED "(expected : %lu , got : %lu)\n" RESET , *expected , *result);
		return;
	}	
}


static void CompareInt(int expected, int result, int line)
{
	int err = 0;
	
	test_num += 1;
/*	if (0 == test_num)*/
/*	{*/
/*		test_num = 1;*/
/*	}*/
		
	err = CompareIntSilently(expected, result, line);

	if(!err && PRINT)
	{
		printf(GREEN "expected: %d , result: %d\n"
			   			RESET, expected, result);		
	}
}

static int CompareDouble(double expected, double result, int line)
{
	int err = 0, status = 0;
	test_num += 1;
	
	err = (expected > (result +  PREC) || expected < (result - PREC));
	
	if (err)
	{	
		++(error);
		printf(RED "Error in test %lu , line: %d\n" RESET, test_num , line);
	}
	
	status = err;
	return status;
}

static int CompareIntSilently(int expected, int result, int line)
{
	int err = 0, status = 0;
	test_num += 1;
	
	if (0 == test_num)
	{
		test_num = 1;
	}
		
	err = (expected != result);
	
	if (err && PRINT)
	{	
		++(error);
		printf(RED "Error in test %lu , line: %d\n" RESET, test_num , line);
		printf(RED "expected: %d , result: %d\n"
			   RESET, expected, result);
	}
	
	status = err;
	return status;
}

static int CompareSsizeT(ssize_t expected, ssize_t result, int line)
{
	size_t err = 0;
	int status = 0;
	test_num += 1;
		
	err = expected != result;
	
	if (err)
	{	
		++(error);
		printf(RED "Error in test %lu , line: %d\n" RESET, test_num , line);
		printf(RED "expected: %ld , result: %ld\n"
			   RESET, expected, result);
		status = -1;
				
	}
	else
	{
		printf(GREEN "expected: %ld , result: %ld\n"
			   RESET, expected, result);
	}
	
	return status;
}

static int CompareSizes(size_t expected, size_t result, int line)
{
	size_t err = 0;
	int status = 0;
	test_num += 1;
		
	err = expected != result;
	
	if (err)
	{	
		++(error);
		printf(RED "Error in test %lu , line: %d\n" RESET, test_num , line);
		printf(RED "expected: %lu , result: %lu\n"
			   RESET, expected, result);
		status = 1;
	}
	else
	{
		printf(GREEN "expected: %lu , result: %lu\n"
			   RESET, expected, result);
	}
	
	return status;
}

static int CompareSizesSilently(size_t expected, size_t result, int line)
{
	size_t err = 0;
	int status = 0;
	test_num += 1;
		
	err = expected != result;
	
	if (err)
	{	
		++(error);
		printf(RED "Error in test %lu , line: %d\n" RESET, test_num , line);
		printf(RED "expected: %lu , result: %lu\n"
			   RESET, expected, result);
		status = 1;
	}
	
	return status;
}

static int CompareSSizesSilently(ssize_t expected, ssize_t result, int line)
{
	size_t err = 0;
	int status = 0;
	test_num += 1;
		
	err = expected != result;
	
	if (err)
	{	
		++(error);
		printf(RED "Error in test %lu , line: %d\n" RESET, test_num , line);
		printf(RED "expected: %ld , result: %ld\n"
			   RESET, expected, result);
		status = 1;
	}
	
	return status;
}


static void IntExpected(int *expected , int *result)
{
	
	if ((NULL == expected || NULL == result) && (result != expected))
	{
		if (NULL == result)
		{
			printf(RED "(expected : %d , got : NULL)\n" RESET , *expected);	
			return;
		}
		else
		{
			printf(RED "(expected : NULL , got : %d)\n" RESET , *result);
			return;
		}
	}	
	
	if ((expected == NULL) && (expected == result))
	{
		return;
	}
	
	if (*expected != *result)
	{
		printf(RED "(expected : %d , got : %d)\n" RESET , *expected , *result);
		return;
	}	
}

static int CompareResults(void *expected, void *result, size_t element_size, int line)
{
	size_t err = 0;
	int status = 0;
	
	test_num += 1;
	if (test_num == 0)
	{
		test_num = 1;
	}
		
	if (NULL == expected || NULL == result)
	{
		err = (expected != result);
	}
		
	else
	{
		err = memcmp(expected, result, element_size);
	}
	if (err)
	{	
		++(error);
		printf(RED "Error in test %ld , line: %d\n" RESET, test_num , line);		
	}
	expected = element_size + (char *)expected;
	result =   element_size + (char *)	result;	
	
	err ? (status = 1) : (status = 0);
	
	return status; 
}


static void ShowResetStatus()
{
	if (error)
	{
		printf( RED "%ld errors\n\n" RESET , error);
		error = 0;
	}
	else
	{
		printf( GREEN "Success in %ld tests\n\n" RESET , test_num);
		test_num = 0;
	}
}

static ssize_t SlowAndSteadySearch(int arr[], size_t size, int target)
{
	size_t i = 0;
	
	for (i = 0; i < size && arr[i] != target; ++i)
	{
		;
	}
	
	return (arr[i] == target) ? (ssize_t)(i) : (ssize_t)(-1);
}

static void PrintName(const char *name ,int line)
{
	PrintLine(line);
	printf("%s:\n" ,name);
}

static void PrintLine(int line)
{
	printf(BLUE "line %d\n" RESET ,line);
}

static void PrintSizeT(size_t t)
{
	printf("%lu\n" , t);
}

static size_t SizeAllignedToWordSize(size_t size)
{
	return (size % WORD_SIZE == 0) ? size 	 :  
	( size + (WORD_SIZE - (size % WORD_SIZE)) );
}


