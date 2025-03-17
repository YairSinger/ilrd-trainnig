#include <stdio.h> 	/* printf, size_t		*/
#include <string.h> /* memcmp 				*/
#include <stdlib.h> /* malloc , free, rand, srand			*/
#include <time.h>   /* time , clock */
#include <sys/types.h> /* ssize_t*/

#include "avl.h" 		
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red 	  */
#define GREEN   "\033[32m"      /* Green */
#define BLUE 	"\033[34m"      /* Blue   */

#define WORD_SIZE sizeof(size_t)
#define MAX_RANGE  10
#define MIN_RANGE  0
#define PRINT 1
#define PRINT_ERR 1
#define GLOBAL_ARR_SIZE 5


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
static void CompareIntSilently(int expected, int result, int line);
static int ActionFunc(void *tree_data, void *user_params);
static int ActionFunc2(void *tree_data, void *user_params);
static int ActionFunc3(void *data, void *param);
static int ActionFunc4(void *data, void *param);
static int ActionFunc5(void *data, void *param);
static void InitArrRandomEven(int arr[], size_t from, size_t to);
static int CompareSSizesSilently(ssize_t expected, ssize_t result, int line);

size_t error = 0, test_num = 0;



int main()
{
	size_t element_size = 0, exp = 0, result = 0, i = 0, j = 0,
		   size = 0, size_1 = 0, size_2 = 0, i_flag = 0, loops = 0,
				loops2 = 0, i_2 = 0, arr_size = 0;
	int int_result = 0, int_exp = 0, param = 0, status = 0, line = 0,
		is_sorted = 0, is_found = 0;
	void *result_ptr = NULL, *expected_ptr = NULL;
	void *element_1 = (void *)malloc(100);
	void *element_2 = (void *)malloc(100);
	void *element_3 = (void *)malloc(100);
	void *element_4 = (void *)malloc(100);
	int *l_arr = NULL, *r_arr = NULL;
	avl_t *avl_1 = NULL, *avl_2 = NULL, *avl_3 = NULL;
		
	static int test_int[5000] = {0};
	static int test_int_2[5000] = {0};
	static int test_int_3[5000] = {0};

	ssize_t h_fac_1 = 0, h_fac_2 = 0, height = 0;
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
	(void)ActionFunc5;
	(void)InitIntArr;
	(void)InitIntArrRandom;
	(void)avl_1;
	(void)avl_2;
	(void)avl_3;
	(void)arr_size;
	srand(time(NULL));	
/*****************************************************************************/	
	
	
	
/*****************************************************************************/	
	
	PrintName("Create:", __LINE__);

	avl_1 = AVLCreate(CmpFunc), line = __LINE__;
	CompareIntSilently(1, avl_1 != NULL , line);
			
	AVLDestroy(avl_1);
	ShowResetStatus();
	
	
/*****************************************************************************/
	
/*****************************************************************************/	
	
	PrintName("Insert:", __LINE__);

	avl_1 = AVLCreate(CmpFunc), line = __LINE__;
	arr_size = GLOBAL_ARR_SIZE;
	InitIntArrRandom(test_int, 0 , arr_size);
	
	for (i = 0; i < arr_size; ++i)
	{
		AVLInsert(avl_1, &test_int[i]);
/*		printf("%d\n" , test_int[i]);*/
		CompareSizesSilently(i + 1, AVLCount(avl_1), line);
	}
	line = __LINE__ - 2;
	
	for (i = 0; i < arr_size; ++ i)
	{
		CompareIntSilently(test_int[i] ,
			 *(int *)AVLFind(avl_1, &test_int[i]), __LINE__);
	}
			
	AVLDestroy(avl_1);
	ShowResetStatus();
	
	
/*****************************************************************************/

/*****************************************************************************/	
	
	PrintName("Remove:", __LINE__);

	avl_1 = AVLCreate(CmpFunc), line = __LINE__;
	arr_size = GLOBAL_ARR_SIZE;
	InitIntArrRandom(test_int, 0 , arr_size);
	
	for (i = 0; i < arr_size; ++i)
	{
		AVLInsert(avl_1, &test_int[i]);
	}
	
/*	printf("***********Original tree:************\n");*/
/*	PrintTree(avl_1);		*/
	/* delete roots only */
	for (i = 0; i < arr_size; ++i)
	{
/*		printf("\n\nnode to be removed: %d\n" , test_int[i]);*/
		AVLRemove(avl_1, &test_int[i]);
/*		printf("\n\n\n ************* new tree: ***************\n");*/
/*		PrintTree(avl_1);*/
		CompareSizesSilently(arr_size - i - 1, AVLCount(avl_1), line);
		CompareIntSilently(1,
			 AVLFind(avl_1, &test_int[i]) == NULL, __LINE__);
	}
	


	/* insert again */	
	for (i = 0; i < arr_size; ++i)
	{
		AVLInsert(avl_1, &test_int[i]);
	}
	
/*	printf("***********Original tree:************\n");*/
/*	PrintTree(avl_1);*/
		
	for (i = 0; i < arr_size; ++i)
	{
/*		printf("\n\nnode to be removed: %d\n" , test_int[arr_size - 1 - i]);*/
		AVLRemove(avl_1, &test_int[arr_size - 1 - i]);
/*		printf("\n\n\n ************* new tree: ***************\n");*/
/*		PrintTree(avl_1);*/
		CompareSizesSilently(arr_size - i - 1, AVLCount(avl_1), line);
		CompareIntSilently(1,
			 AVLFind(avl_1, &test_int[arr_size - 1 - i]) == NULL, __LINE__);
	}		
	
			
	AVLDestroy(avl_1);
	ShowResetStatus();
	
	
/*****************************************************************************/

/*****************************************************************************/	
	
	PrintName("Find:", __LINE__);

	avl_1 = AVLCreate(CmpFunc), line = __LINE__;
	arr_size = GLOBAL_ARR_SIZE;
	InitIntArrRandom(test_int, 0 , arr_size);
	
	
	for (i = 0; i < arr_size; ++i)
	{
		AVLInsert(avl_1, &test_int[i]);
	}
	
	for (i = 0; i < arr_size; ++ i)
	{
		CompareIntSilently(test_int[i] ,
			 *(int *)AVLFind(avl_1, &test_int[i]), __LINE__);
	}
	
			
	AVLDestroy(avl_1);
	ShowResetStatus();
	
	
/*****************************************************************************/


/*****************************************************************************/	
	
	PrintName("For Each:", __LINE__);

	/* In Order**********************************/
	avl_1 = AVLCreate(CmpFunc), line = __LINE__;
	arr_size = /*GLOBAL_ARR_SIZE*/2;
	InitArrRandomEven(test_int, 0 , arr_size);
	memcpy(test_int_2, test_int, sizeof(int) * arr_size);	
	for (i = 0; i < arr_size; ++i)
	{
		AVLInsert(avl_1, &test_int[i]);
	}
	param = 1;
	int_result = AVLForEach(avl_1, IN_ORDER, ActionFunc3, &param);
	for (i = 0; i < arr_size; ++ i)
	{
		CompareIntSilently(test_int_2[i] + 1,
			 *(int *)AVLFind(avl_1, &test_int[i]), __LINE__);
	}
	
	
	int_result = AVLForEach(avl_1, IN_ORDER, ActionFunc4, &param), line = __LINE__;
	CompareIntSilently(1, int_result, line);		
	AVLDestroy(avl_1);
	
	
	
	/* Post Order **********************************************/
	avl_1 = AVLCreate(CmpFunc), line = __LINE__;
	arr_size = GLOBAL_ARR_SIZE;
	InitArrRandomEven(test_int, 0 , arr_size);
	memcpy(test_int_2, test_int, sizeof(int) * arr_size);
	
	for (i = 0; i < arr_size; ++i)
	{
		AVLInsert(avl_1, &test_int[i]);
	}
	param = 1;
	int_result = AVLForEach(avl_1, POST_ORDER, ActionFunc3, &param);
	for (i = 0; i < arr_size; ++ i)
	{
		CompareIntSilently(test_int_2[i] + 1,
			 *(int *)AVLFind(avl_1, &test_int[i]), __LINE__);
	}
			
			
	int_result = AVLForEach(avl_1, POST_ORDER, ActionFunc4, NULL), line = __LINE__;
	CompareIntSilently(1, int_result, line);
	AVLDestroy(avl_1);
	
	
	
	
	/* Pre Order **************************************************/
	
	avl_1 = AVLCreate(CmpFunc), line = __LINE__;
	arr_size = GLOBAL_ARR_SIZE;
	InitArrRandomEven(test_int, 0 , arr_size);
	memcpy(test_int_2, test_int, sizeof(int) * arr_size);
	
	for (i = 0; i < arr_size; ++i)
	{
		AVLInsert(avl_1, &test_int[i]);
	}
	param = 1;
	int_result = AVLForEach(avl_1, PRE_ORDER, ActionFunc3, &param);
	for (i = 0; i < arr_size; ++ i)
	{
		CompareIntSilently(test_int_2[i] + 1,
			 *(int *)AVLFind(avl_1, &test_int[i]), __LINE__);
	}
			
			
	int_result = AVLForEach(avl_1, PRE_ORDER, ActionFunc4, NULL), line = __LINE__;
	CompareIntSilently(1, int_result, line);
	AVLDestroy(avl_1);
	
	ShowResetStatus();
	
	
	
	
/*****************************************************************************/

/*****************************************************************************/	
	
	PrintName("Test Balancing:", __LINE__);

	avl_1 = AVLCreate(CmpFunc), line = __LINE__;
	arr_size = GLOBAL_ARR_SIZE;
	InitIntArr(test_int, 0 , arr_size);
	h_fac_1 = 1, h_fac_2 = 2;	
	
	for (height = 0, i = 0; i < arr_size; ++i)
	{
		AVLInsert(avl_1, &test_int[i]);
/*		printf("%d , " , test_int[i]);*/
		CompareSSizesSilently(height,AVLGetHeight(avl_1), __LINE__);
		if (AVLCount(avl_1) == (size_t)h_fac_1)
		{
			h_fac_1 += h_fac_2;
			h_fac_2 *= 2;	
			++height;
		}
		
	}
	
/* balancing is look pretty good, only need to check that on remove as well - and im good to go.*/
/* dont forget the advanced functions*/
/*	PrintTree(avl_1);*/
/*	for (i = 0; i < arr_size; ++ i)*/
/*	{*/
/*		CompareIntSilently(test_int[i] ,*/
/*			 *(int *)AVLFind(avl_1, &test_int[i]), __LINE__);*/
/*	}*/
	
			
	AVLDestroy(avl_1);
	ShowResetStatus();


	
	
/*****************************************************************************/

/*****************************************************************************/
	
	
	
	
	
	free(element_1);
	free(element_2);
	free(element_3);
	free(element_4);
	return 0;
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

static int ActionFunc5(void *data, void *param)
{
	AVLRemove((avl_t *)param, data);
	return 0;
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
	size_t err = 0;
	
	test_num += 1;
	if (0 == test_num)
	{
		test_num = 1;
	}
		
	err = memcmp(&expected, &result, sizeof(int));
	
	if (err)
	{	
		++(error);
		if (PRINT_ERR)
		{
			printf(RED "Error in test %lu , line: %d\n" RESET, test_num , line);
			printf(RED "expected: %d , result: %d\n"
				   RESET, expected, result);
		}		
	}
	else if (PRINT)
	{
		printf(GREEN "expected: %d , result: %d\n"
			   RESET, expected, result);
	}
}

static void CompareIntSilently(int expected, int result, int line)
{
	size_t err = 0;
	
	test_num += 1;
	if (0 == test_num)
	{
		test_num = 1;
	}
		
	err = memcmp(&expected, &result, sizeof(int));
	
	if (err)
	{	
		++(error);
		printf(RED "Error in test %lu , line: %d\n" RESET, test_num , line);
		printf(RED "expected: %d , result: %d\n"
			   RESET, expected, result);
				
	}
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


