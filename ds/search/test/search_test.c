#include <stdio.h> 	/* printf */
#include <stdlib.h> /*srand */
#include <time.h> 	/*clock_t, clock() */
#include "search.h"


#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

#define RAND_SIZE 5000






void TestSearchingBinarySearch(ssize_t (*search_func)(int arr[], size_t length, int value_to_search), char *search_func_name);

void TestBinartSearch();

int main()
{
	TestSearchingBinarySearch(BinarySearch,"BinarySearch");
	TestSearchingBinarySearch(RecBinarySearch,"RecBinarySearch");
	TestSearchingBinarySearch(JumpSearch,"JumpSearch");
	TestSearchingBinarySearch(RecJumpSearch,"RecJumpSearch");
	
	return 0;
}

/********************/

int CmpFunc(const void * a, const void * b) 
{
    if (*(int*)a > *(int*)b)
    {
        return 1;
    }
    else if (*(int*)a < *(int*)b)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
void RandomInput(int arr[], unsigned int seed)
{	
	size_t i = 0;
	srand(seed);
	for (i = 0; i< RAND_SIZE; ++i)
	{
		arr[i] = (rand() % 10000);
	
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

/*
void TestBinartSearch()
{
	int arr[10] = {0,1,2,3,4,5,6,7,8,9};
	int res = 0;
	size_t fails_counter = 0;
	
	if(0 != BinarySearch(arr,10,0))
	{
		++fails_counter;
		printf(RED"BinarySearch FAILED \n"RESET_COLOR);
	}
	
	if (0 == fails_counter)
 	{
 		printf(GREEN"Test %s, PASSED\n","BinarySearch");
 	}

}
*/




void TestSearchingBinarySearch(ssize_t (*search_func)(int arr[], size_t length, int value_to_search), char *search_func_name)
{
	int arr5[RAND_SIZE] = {0};
	int seeds[3] = {2,3,10};
	double cpu_time_used[3] = {0};
	ssize_t search_result = 0;
	
	size_t i = 0;
	size_t fails_counter = 0;
	clock_t start, end;
    
    
	for (i = 0; i < 3; ++i)
	{
		
		RandomInput(arr5, seeds[i]);
		
		
		qsort((void *)arr5, RAND_SIZE, sizeof(int),CmpFunc);

				
		if (!IsArraySorted(arr5,RAND_SIZE))
		{ 
			++fails_counter ;
			printf(RED"sorting array FAILED \n"RESET_COLOR);
		}
		
		start = clock();
		search_result = search_func(arr5, RAND_SIZE, arr5[1000]);
		end = clock();
		cpu_time_used[i] = 1000 * ((double) (end - start)) / CLOCKS_PER_SEC;
		
		if (1000 != search_result)
		{ 
			++fails_counter ;
			printf(RED"search array FAILED to find exising int \n"RESET_COLOR);
		}
		search_result = search_func(arr5, RAND_SIZE, arr5[RAND_SIZE -1]);
		if ((RAND_SIZE -1) != search_result)
		{ 
			++fails_counter ;
			printf(RED"search array FAILED to find last element %lu \n"RESET_COLOR, search_result );
		}
		search_result = search_func(arr5, RAND_SIZE, 20000);
		if (-1 != search_result)
		{ 
			++fails_counter ;
			printf(RED"search array FAILED to return %lu index vs -1 expected and %d value\n"RESET_COLOR,search_result, arr5[search_result]);
		}
	}
	
	if (0 == fails_counter)
 	{
 		printf(GREEN"Test %s, PASSED\n","BinarySearch");
		printf("Average search time for %s is %f [micro-sec]\n\n"RESET_COLOR, search_func_name, AverageTime(cpu_time_used, 3));
	}
	
}


