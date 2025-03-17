#include <stdio.h> 	/* printf, size_t		*/
#include <string.h> /* memcmp 				*/
#include <stdlib.h> /* malloc , free, rand, srand			*/
#include <time.h> /* time , clock */

#include "sort.h" 		/* to fill  			*/
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red 	  */
#define GREEN   "\033[32m"      /* Green */
#define BLUE 	"\033[34m"      /* Blue   */

#define WORD_SIZE sizeof(size_t)
#define MAX_RANGE  5000
#define MIN_RANGE  1
#define MAX_RADIX_RANGE 5000
#define MIN_RADIX_RANGE 1

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

size_t error = 0, test_num = 0;



int main()
{
	size_t element_size = 0, exp = 0, result = 0, i = 0,
		   size = 0, size_1 = 0, size_2 = 0, i_flag = 0;
	int int_result = 0, int_exp = 0, param = 0, status = 0, line = 0, is_sorted = 0;
	void *result_ptr = NULL, *expected_ptr = NULL;
	void *element_1 = (void *)malloc(100);
	void *element_2 = (void *)malloc(100);
	void *element_3 = (void *)malloc(100);
	void *element_4 = (void *)malloc(100);
	int *l_arr = NULL, *r_arr = NULL;
	
	
	static int test_arr_1[] = {-9, 3, 1, -18, 0, 0, 0, 5, 2 };
	static int exp_arr_1[]  = {-18, -9, 0, 0, 0, 1, 2, 3, 5 };
	
	static int test_arr_2[] = {0, -1, 0, -1, 0, -1, 0, -1, 0 };
	static int exp_arr_2[]  = {-1, -1, -1, -1, 0, 0, 0, 0, 0 };
	
	static int test_arr_3[] = {-9, 3, 1, -18, 0, 0, 0, 5, 2 ,5 };
	static int exp_arr_3[]  = {-18, -9, 0, 0, 0, 1, 2, 3, 5, 5 };
	
	static int test_arr_4[] = {-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10 };
	static int exp_arr_4[]  = {-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10 };
	
	static int test_arr_5[] = { 22111, 22110, 22109, 22108, 22107, 22106, 22105, 22104};
	static int exp_arr_5[]  = { 22104, 22105, 22106, 22107, 22108, 22109, 22110, 22111};
	
	static int test_arr_1_2[] = {-9, 3, 1, -18, 0, 0, 0, 5, 2 };
	static int exp_arr_1_2[]  = {-18, -9, 0, 0, 0, 1, 2, 3, 5 };
	
	static int test_arr_2_2[] = {0, -1, 0, -1, 0, -1, 0, -1, 0 };
	static int exp_arr_2_2[]  = {-1, -1, -1, -1, 0, 0, 0, 0, 0 };
	
	static int test_arr_3_2[] = {-9, 3, 1, -18, 0, 0, 0, 5, 2 ,5 };
	static int exp_arr_3_2[]  = {-18, -9, 0, 0, 0, 1, 2, 3, 5, 5 };
	
	static int test_arr_4_2[] = {-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10 };
	static int exp_arr_4_2[]  = {-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10 };
	
	static int test_arr_5_2[] = { 22111, 22110, 22109, 22108, 22107, 22106, 22105, 22104};
	static int exp_arr_5_2[]  = { 22104, 22105, 22106, 22107, 22108, 22109, 22110, 22111};
	
	
	static int radix_test_1[] = {1234567, 2234567, 9918273, 7584920 , 9012936 , 1029385};
	static int radix_exp_1[] =  {1029385, 1234567, 2234567, 7584920, 9012936, 9918273};
	
	static int dup_arr_1[] = {-9, 3, 1, -18, 0, 0, 0, 5, 2 };
	static int dup_arr_2[] = {0, -1, 0, -1, 0, -1, 0, -1, 0 };
	static int dup_arr_3[] = {-9, 3, 1, -18, 0, 0, 0, 5, 2 ,5 };
	static int dup_arr_4[] = {-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10 };
	static int dup_arr_5[] = { 22111, 22110, 22109, 22108, 22107, 22106, 22105, 22104};
	
	
/* for testing several optios */	
/*	static int dup_arr_1[] = {9, 3, 1, 18, 1, 1, 1, 5, 2 };*/
/*	static int dup_arr_2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1 };*/
/*	static int dup_arr_3[] = {9, 3, 1, 18, 1, 1, 1, 5, 2 ,5 };*/
/*	static int dup_arr_4[] = {5,4,3,2,1,1,1,2,3,4,5,6,7,8,9,10 };*/
/*	static int dup_arr_5[] = { 22111, 22112, 22119, 22148, 22137, 22156, 22185, 22194};*/
	
	static int test_int[5000] = {0};


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
	(void)size;
	(void)size_1;
	(void)size_2;
	(void)i_flag;
	(void)int_result;
	(void)int_exp;
	(void)param;
	(void)expected_ptr;
	srand(time(NULL));	
/*****************************************************************************/	

	
	
	PrintName("Bubble Sort" , __LINE__);
	size = sizeof(test_arr_1)/sizeof(int);
	l_arr = exp_arr_1, r_arr = test_arr_1;
	BubbleSort(r_arr ,size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}
	
	size = sizeof(test_arr_2)/sizeof(int);
	l_arr = exp_arr_2, r_arr = test_arr_2;
	BubbleSort(r_arr ,size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}
	
	size = sizeof(test_arr_3)/sizeof(int);
	l_arr = exp_arr_3, r_arr = test_arr_3;
	BubbleSort(r_arr ,size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}
	
	size = sizeof(test_arr_4)/sizeof(int);
	l_arr = exp_arr_4, r_arr = test_arr_4;
	BubbleSort(r_arr ,size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}
	
	size = sizeof(test_arr_5)/sizeof(int);
	l_arr = exp_arr_5, r_arr = test_arr_5;
	BubbleSort(r_arr ,size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}
	
	
	size = 5000;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = rand() % MAX_RANGE + MIN_RANGE;
	}
	
	begin = clock();
	BubbleSort(test_int ,size), line = __LINE__;
	end = clock();
	printf("time : %ld\n" , end - begin);
	/* test sort */
	for (is_sorted = 1, i = 1; i < size && 1 == is_sorted; ++i)
	{
		if (test_int[i - 1] > test_int[i])
		{
			is_sorted = 0;
		}
	}
	
	/* make sure that iteration was completed */
	int_exp = 1;
	int_result = (size == i);
	status = CompareResults(&int_exp, &int_result, sizeof(int), __LINE__);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}	
	
	int_exp = 1;
	status = CompareResults(&int_exp, &is_sorted, sizeof(int), line);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}
	
	
	ShowResetStatus();
	
	
	
	
	
/*****************************************************************************/	
	
	
	
	
	PrintName("Bubble Sort Generic" , __LINE__);
	size = sizeof(test_arr_1_2)/sizeof(int);
	l_arr = exp_arr_1_2, r_arr = test_arr_1_2;
    GenericBubbleSort(r_arr, sizeof(int), size, &CmpFunc);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(test_arr_2_2)/sizeof(int);
	l_arr = exp_arr_2_2, r_arr = test_arr_2_2;
    GenericBubbleSort(r_arr, sizeof(int), size, &CmpFunc);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(test_arr_3_2)/sizeof(int);
	l_arr = exp_arr_3_2, r_arr = test_arr_3_2;
    GenericBubbleSort(r_arr, sizeof(int), size, &CmpFunc);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}
	
	size = sizeof(test_arr_4_2)/sizeof(int);
	l_arr = exp_arr_4_2, r_arr = test_arr_4_2;
    GenericBubbleSort(r_arr, sizeof(int), size, &CmpFunc);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}
	
	size = sizeof(test_arr_5_2)/sizeof(int);
	l_arr = exp_arr_5_2, r_arr = test_arr_5_2;
    GenericBubbleSort(r_arr, sizeof(int), size, &CmpFunc);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}
	
	
	
	
	size = 5000;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = rand() % MAX_RANGE + MIN_RANGE;
	}

	begin = clock();
    GenericBubbleSort(test_int, sizeof(int), size, &CmpFunc), line = __LINE__;
	end = clock();
	printf("time : %ld\n" , end - begin);
	/* test sort */
	for (is_sorted = 1, i = 1; i < size && 1 == is_sorted; ++i)
	{
		if (test_int[i - 1] > test_int[i])
		{
			is_sorted = 0;
		}
	}
	
	/* make sure that iteration was completed */
	int_exp = 1;
	int_result = (size == i);
	status = CompareResults(&int_exp, &int_result, sizeof(int), __LINE__);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}	
	
	int_exp = 1;
	status = CompareResults(&int_exp, &is_sorted, sizeof(int), line);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}
	ShowResetStatus();
	
	
	
	
	
/*****************************************************************************/	
	
	
	PrintName("Selection Sort" , __LINE__);
	

	size = sizeof(dup_arr_1)/sizeof(int);
	for (i = 0; i < size; ++i)
	{
		test_int[i] = dup_arr_1[i];
	}
	l_arr = exp_arr_1, r_arr = test_int;
    SelectionSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_2)/sizeof(int);
	l_arr = exp_arr_2;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = l_arr[i];
	}
	r_arr = test_int;
	SelectionSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_3)/sizeof(int);
	l_arr = exp_arr_3;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = l_arr[i];
	}
	r_arr = test_int;
    SelectionSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_4)/sizeof(int);
	l_arr = exp_arr_4;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = l_arr[i];
	}
	r_arr = test_int;
    SelectionSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_5)/sizeof(int);
	l_arr = exp_arr_5;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = l_arr[i];
	}
	r_arr = test_int;
    SelectionSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = 5000;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = rand() % MAX_RANGE + MIN_RANGE;
	}
	
	begin = clock();
    SelectionSort(test_int, size), line = __LINE__;
	end = clock();
	printf("time : %ld\n" , end - begin);
	/* test sort */
	for (is_sorted = 1, i = 1; i < size && 1 == is_sorted; ++i)
	{
		if (test_int[i - 1] > test_int[i])
		{
			is_sorted = 0;
		}
	}
	
	/* make sure that iteration was completed */
	int_exp = 1;
	int_result = (size == i);
	status = CompareResults(&int_exp, &int_result, sizeof(int), __LINE__);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}	
	
	int_exp = 1;
	status = CompareResults(&int_exp, &is_sorted, sizeof(int), line);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}


	ShowResetStatus();
	
	
/*****************************************************************************/	
	
	
	PrintName("Insertion Sort" , __LINE__);
	size = sizeof(dup_arr_1)/sizeof(int);
	for (i = 0; i < size; ++i)
	{
		test_int[i] = dup_arr_1[i];
	}
	l_arr = exp_arr_1, r_arr = test_int;
    InsertionSort(r_arr, size), line = __LINE__;
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), line );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_2)/sizeof(int);
	l_arr = exp_arr_2;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = l_arr[i];
	}
	r_arr = test_int;
    InsertionSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_3)/sizeof(int);
	l_arr = exp_arr_3;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = l_arr[i];
	}
	r_arr = test_int;
    InsertionSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_4)/sizeof(int);
	l_arr = exp_arr_4;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = l_arr[i];
	}
	r_arr = test_int;
    InsertionSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_5)/sizeof(int);
	l_arr = exp_arr_5;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = l_arr[i];
	}
	r_arr = test_int;
    InsertionSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}
	
	size = 5000;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = rand() % MAX_RANGE + MIN_RANGE;
	}
	begin = clock();
    InsertionSort(test_int, size), line = __LINE__;
	end = clock();
	printf("time : %ld\n" , end - begin);
	/* test sort */
	for (is_sorted = 1, i = 1; i < size && 1 == is_sorted; ++i)
	{
		if (test_int[i - 1] > test_int[i])
		{
			is_sorted = 0;
		}
	}
	
	/* make sure that iteration was completed */
	int_exp = 1;
	int_result = (size == i);
	status = CompareResults(&int_exp, &int_result, sizeof(int), __LINE__);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}	
	
	int_exp = 1;
	status = CompareResults(&int_exp, &is_sorted, sizeof(int), line);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}
	ShowResetStatus();
	
	
/*****************************************************************************/	
	
	
	PrintName("Counting Sort" , __LINE__);
	size = sizeof(dup_arr_1)/sizeof(int);
	for (i = 0; i < size; ++i)
	{
		test_int[i] = dup_arr_1[i];
	}
	l_arr = exp_arr_1, r_arr = test_int;
    CountingSort(r_arr, size), line = __LINE__;
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), line );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_2)/sizeof(int);
	l_arr = exp_arr_2;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = dup_arr_2[i];
	}
	r_arr = test_int;
    CountingSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_3)/sizeof(int);
	l_arr = exp_arr_3;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = dup_arr_3[i];
	}
	r_arr = test_int;
    CountingSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_4)/sizeof(int);
	l_arr = exp_arr_4;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = dup_arr_4[i];
	}
	r_arr = test_int;
    CountingSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = sizeof(dup_arr_5)/sizeof(int);
	l_arr = exp_arr_5;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = dup_arr_5[i];
	}
	r_arr = test_int;
    CountingSort(r_arr, size);
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), __LINE__ );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}
	
	size = 5000;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = rand() % MAX_RANGE + MIN_RANGE;
	}
	begin = clock();
    CountingSort(test_int, size), line = __LINE__;
	end = clock();
	printf("time : %ld\n" , end - begin);
	/* test sort */
	for (is_sorted = 1, i = 1; i < size && 1 == is_sorted; ++i)
	{
		if (test_int[i - 1] > test_int[i])
		{
			is_sorted = 0;
		}
	}
	
	/* make sure that iteration was completed */
	int_exp = 1;
	int_result = (size == i);
	status = CompareResults(&int_exp, &int_result, sizeof(int), __LINE__);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}	
	
	int_exp = 1;
	status = CompareResults(&int_exp, &is_sorted, sizeof(int), line);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}
	ShowResetStatus();
		
	
	
/*****************************************************************************/	

	PrintName("Radix Sort" , __LINE__);
	size = sizeof(radix_test_1)/sizeof(int);
	for (i = 0; i < size; ++i)
	{
		test_int[i] = radix_test_1[i];
	}
	l_arr = radix_exp_1, r_arr = test_int;
    RadixSort(r_arr, size), line = __LINE__;
	status = CompareResults(l_arr, r_arr ,size * sizeof(int), line );
	if (0 != status)
	{
		PrintIntArrs(l_arr, r_arr, size);
	}

	size = 5000;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = rand() % MAX_RADIX_RANGE + MIN_RADIX_RANGE;
	}
	begin = clock();
    RadixSort(test_int, size), line = __LINE__;
	end = clock();
	printf("time : %ld\n" , end - begin);
	/* test sort */
	for (is_sorted = 1, i = 1; i < size && 1 == is_sorted; ++i)
	{
		if (test_int[i - 1] > test_int[i])
		{
			is_sorted = 0;
		}
	}
	
	/* make sure that iteration was completed */
	int_exp = 1;
	int_result = (size == i);
	status = CompareResults(&int_exp, &int_result, sizeof(int), __LINE__);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}	
	
	int_exp = 1;
	status = CompareResults(&int_exp, &is_sorted, sizeof(int), line);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}

	ShowResetStatus();
	
	
/*****************************************************************************/	

	PrintName("Qsort" , __LINE__);	
	size = 5000;
	for (i = 0; i < size; ++i)
	{
		test_int[i] = rand() % MAX_RANGE + MIN_RANGE;
	}
	begin = clock();
    QSort(test_int, size , sizeof(int), &CmpFunc), line = __LINE__;
	end = clock();
	printf("time : %ld\n" , end - begin);
	/* test sort */
	for (is_sorted = 1, i = 1; i < size && 1 == is_sorted; ++i)
	{
		if (test_int[i - 1] > test_int[i])
		{
			is_sorted = 0;
		}
	}
	
	/* make sure that iteration was completed */
	int_exp = 1;
	int_result = (size == i);
	status = CompareResults(&int_exp, &int_result, sizeof(int), __LINE__);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}	
	
	int_exp = 1;
	status = CompareResults(&int_exp, &is_sorted, sizeof(int), line);
	if (1 == status)
	{
		IntExpected(&int_exp, &is_sorted);
	}	

	ShowResetStatus();
	
	free(element_1);
	free(element_2);
	free(element_3);
	free(element_4);
	return 0;
}



static int CmpFunc(const void *lhs,const void *rhs)
{
	return *(int *)lhs - *(int *)rhs;
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


