/*#include <stdio.h> 	/* printf */
/*#include <stdlib.h> /*srand */
/*#include <time.h> 	/*clock_t, clock() */
/*#include "sort.h"
/*#include "stack.h" /*stack_sort */


/*#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

#define RAND_SIZE 10000
#define RAND_RANGE 10000


static void printArray(int array[], int size)
{
	size_t i = 0;
	
  for (i = 0; i < size; ++i) 
  {
    printf("%d,  ", array[i]);
  }
  printf("\n");
}


int AscendingInts(const void *lsv, const void *rsv)
{
	return *((int *)rsv) - *((int *)lsv);		
}




void TestSortingFunc(void (*sort_func)(int *arr, size_t length), char *sort_func_name);
void TestLinearSortingFunc(int (*sort_func)(int arr[], size_t length), char *sort_func_name);
void TestQSort();
void TestStackSort();

int main()
{
	
	
	/*TestSortingFunc(InsertionSort, "InsertionSort");
	TestSortingFunc(BubbleSort, "BubbleSort");
	TestSortingFunc(SelectionSort, "SelectionSort");
	TestSortingFunc(HeapSort, "HeapSort");
	
	TestLinearSortingFunc(CountingSort, "CountingSort");
	TestLinearSortingFunc(RadixSort, "RadixSort");
	TestLinearSortingFunc(MergeSort, "MergeSort");*/
	/*TestSortingFunc(QuickSortQuize, "QuickSortQuize");
	/*TestQSort();*/
	/*TestStackSort();*/
	
	
	/*return 0;
}

/********************/

/*void RandomInput(int arr[], unsigned int seed)
{	
	size_t i = 0;
	srand(seed);
	for (i = 0; i< RAND_SIZE; ++i)
	{
		arr[i] = rand() % RAND_RANGE;
	
	}
}

int IsArraySorted(int arr[], size_t length)
{
	size_t i = 1;
	
	for(i = 1; i < length; ++i)
	{
		if (arr[i-1] > arr[i])
		{
			return 0;
		}
	}
	
	return 1;
}

double AverageTime(double arr[], size_t size)
{
	double avg = 0;
	size_t i = 0;
	for(i = 0; i < size; ++i)
	{
		avg += arr[i];
	}
	
	return avg / size;
}

void TestSortingFunc(void (*sort_func)(int *arr, size_t length), char *sort_func_name)
{
	int arr[RAND_SIZE] = {0};
	int seeds[3] = {2,3,10};
	double cpu_time_used[3] = {0};
	size_t i = 0;
	size_t fails_counter = 0;
	clock_t start, end;
    
    
	for (i = 0; i < 3; ++i)
	{
		
		RandomInput(arr, seeds[i]);
		
		start = clock();		
		sort_func(arr, RAND_SIZE);
		end = clock();
		
		
		if (!IsArraySorted(arr,RAND_SIZE))
		{ 
			++fails_counter ;
			printf(RED"Test 1 %s FAILED \n"RESET_COLOR,sort_func_name);
		}
		
		cpu_time_used[i] = 1000 * ((double) (end - start)) / CLOCKS_PER_SEC;
	}
	
	if (0 == fails_counter)
 	{
 		printf(GREEN"Test %s, PASSED\n",sort_func_name);
		printf("Average time for %s is %f [micro-sec]\n\n"RESET_COLOR, sort_func_name, AverageTime(cpu_time_used, 3));
	}
	
}


static void RandomLimitedInput(int arr[], unsigned int seed,size_t upper_limit)
{	
	size_t i = 0;
	srand(seed);
	for (i = 0; i< RAND_SIZE; ++i)
	{
		arr[i] = (rand() % upper_limit);
	
	}
}

static void PrintArray(int arr[], size_t length)
{
	size_t i = 0;
	for (i = 0; i < length; ++i)
	{
		printf(" %d, ",arr[i]);
	}
	printf("\n\n");
}

void TestLinearSortingFunc(int (*sort_func)(int arr[], size_t length), char *sort_func_name)
{
	int arr[RAND_SIZE] = {0};
	int seeds[3] = {2,3,10};
	double cpu_time_used[3] = {0};
	size_t i = 0;
	int status = 0;
	size_t fails_counter = 0;
	clock_t start, end;
    
    
	for (i = 0; i < 3; ++i)
	{
		RandomLimitedInput(arr, seeds[i],10000);
					
		start = clock();
		status = sort_func(arr, RAND_SIZE);
		end = clock();
		
				
		if (0 != status)
		{ 
			++fails_counter ;
			printf(RED"Test 1 %s FAILED. Function returned status 1 \n"RESET_COLOR,sort_func_name);
		}
		
		if (!IsArraySorted(arr,RAND_SIZE))
		{ 
			++fails_counter ;
			printf(RED"Test 2 %s FAILED. Result array is not sorted.\n"RESET_COLOR,sort_func_name);
		}
		
		cpu_time_used[i] = 1000* ((double) (end - start)) / CLOCKS_PER_SEC;
	}
	
	if (0 == fails_counter)
 	{
 		printf(GREEN"Test %s, PASSED\n",sort_func_name);
		printf("Average time for %s is %f [micro-sec]\n\n"RESET_COLOR, sort_func_name, AverageTime(cpu_time_used, 3));
	}
	
}

void TestQSort()
{
	int arr[RAND_SIZE] = {0};
	int seeds[3] = {2,3,10};
	double cpu_time_used[3] = {0};
	size_t i = 0;
	int status = 0;
	size_t fails_counter = 0;
	clock_t start, end;
    
    
	for (i = 0; i < 3; ++i)
	{
		RandomLimitedInput(arr, seeds[i],10000);
					
		start = clock();
		QSort((void *)arr, RAND_SIZE - 1, sizeof(int), AscendingInts);
		end = clock();
		

		if (!IsArraySorted(arr,RAND_SIZE))
		{ 
			++fails_counter ;
			printf(RED"Test 2 QSort FAILED. Result array is not sorted.\n"RESET_COLOR);
		}
		
		cpu_time_used[i] = 1000* ((double) (end - start)) / CLOCKS_PER_SEC;
	}
	
	if (0 == fails_counter)
 	{
 		printf(GREEN"Test ,QSort, PASSED\n"RESET_COLOR);
		printf("Average time for , QSort is %f [micro-sec]\n\n"RESET_COLOR, AverageTime(cpu_time_used, 3));
	}
	
}
/*
void TestStackSort()
{
	int arr[RAND_SIZE] = {0};
	int result[RAND_SIZE] = {0};
	int seeds[3] = {2,3,10};
	double cpu_time_used[3] = {0};
	size_t i = 0;
	size_t j = 0;
	int status = 0;
	stack_t *stack = StackCreate(RAND_SIZE, sizeof(int));
	size_t fails_counter = 0;
	clock_t start, end;
    
    if(NULL == stack)
    {
    	return;
    }
    
	for (i = 0; i < 3; ++i)
	{
		
		RandomLimitedInput(arr, seeds[i],10000);
		printf("before sort\n");
		printArray(arr, RAND_SIZE);
		
		for (j = 0; j < RAND_SIZE; ++j)
		{
			StackPush(stack, &arr[j]); 
		}
					
		start = clock();
		stack = SortStack(stack);
		end = clock();
		
		for (j = 0; j < RAND_SIZE; ++j)
		{
			StackPeek(stack, &result[j]);
			StackPop(stack);  
		}		
			StackDestroy(stack);
			
		printf("after sort\n");
		
		printArray(result, RAND_SIZE);
		if (!IsArraySorted(result,RAND_SIZE))
		{ 
			++fails_counter ;
			printf(RED"Test 2 SortStack FAILED. Result array is not sorted.\n"RESET_COLOR);
		}
		
		cpu_time_used[i] = 1000* ((double) (end - start)) / CLOCKS_PER_SEC;
	}
	
	if (0 == fails_counter)
 	{
 		printf(GREEN"Test ,SortStack, PASSED\n"RESET_COLOR);
		printf("Average time for , SortStack is %f [micro-sec]\n\n"RESET_COLOR, AverageTime(cpu_time_used, 3));
	}
	
}

*/

#include <stdio.h>
#include <string.h>

/* Function signature for GenericBubbleSort*/
void GenericBubbleSort(void *arr, size_t elem_size, size_t length, int (*cmp_func)(const void *lhs, const void *rhs));

/* Integer comparison function*/
int int_cmp(const void *lhs, const void *rhs) {
    return (*(int *)lhs) - (*(int *)rhs);
}

/* String comparison function (compare by string length)*/
int str_cmp(const void *lhs, const void *rhs) {
    return strlen(*(char **)lhs) - strlen(*(char **)rhs);
}

/* Test function for GenericBubbleSort*/
void test_generic_bubble_sort() {
    /* Test with an array of integers*/
    int int_arr[] = {5, 2, 8, 1, 3};
    size_t int_elem_size = sizeof(int);
    size_t int_length = sizeof(int_arr) / sizeof(int);
	size_t i;
	char *str_arr[] = {"apple", "banana", "cherry", "date", "fig"};
    size_t str_elem_size = sizeof(char *);
    size_t str_length = sizeof(str_arr) / sizeof(char *);
	
    GenericBubbleSort(int_arr, int_elem_size, int_length, int_cmp);

    /* Check if the array is sorted*/
    for (i = 1; i < int_length; ++i) {
        if (int_arr[i] < int_arr[i - 1]) {
            printf("Bubble sort failed for integers\n");
            return;
        }
    }

    /* Test with an array of strings*/
   
    GenericBubbleSort(str_arr, str_elem_size, str_length, str_cmp);

    /* Check if the array is sorted*/
    for (i = 1; i < str_length; ++i) {
        if (str_cmp(&str_arr[i], &str_arr[i - 1]) < 0) {
            printf("Bubble sort failed for strings\n");
            return;
        }
    }

    printf("All test cases passed!\n");
}

int main() {
    test_generic_bubble_sort();
    return 0;
}

