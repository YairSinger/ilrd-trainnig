#include <stdio.h> 	/* printf */
#include <stdlib.h> /*srand */
#include <time.h> 	/*clock_t, clock() */
#include "mt_count_sort.h"


#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

#define RAND_SIZE 100000
#define RAND_RANGE 100000
#define NUM_OF_WORDS 985084
#define NUM_OF_COPIES 6


void printArray(int array[], int size)
{
	size_t i = 0;
	
  for (i = 0; i < (size_t)size; ++i) 
  {
    printf("%d,  ", array[i]);
  }
  printf("\n");
}

void printArrayChar(char array[], size_t size)
{
	size_t i = 0;
	
  for (i = 0; i < (size_t)size; ++i) 
  {
    printf("%c", array[i]);
  }
  printf("\n");
}


int AscendingInts(const void *lsv, const void *rsv)
{
	return *((int *)rsv) - *((int *)lsv);		
}




void TestLinearSortingFunc(int (*sort_func)(int arr[], size_t length, size_t num_of_threads), char *sort_func_name);
void SortingLinxDictLetters(int (*sort_func)(char arr[], size_t length, size_t num_of_threads), char *sort_func_name);

void TestQSort();
void TestStackSort();


int main()
{	
	TestLinearSortingFunc(MultiThreadsCountingSort, "MultiThreadsCountingSort"); /*ec 1*/
    printf("\n\n\n");
	/*TestLinearSortingFunc(MultiThreadsCountingSort2, "MultiThreadsCountingSort2");*/

    
    SortingLinxDictLetters(MultiThreadsCountingSortChars, "MultiThreadsCountingSortChars");/*ex 2*/

		
	return 0;
}

void RandomInput(int arr[], unsigned int seed)
{	
	size_t i = 0;
	srand(seed);
	for (i = 0; i < RAND_SIZE; ++i)
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

int IsArraySortedChar(char arr[], size_t length)
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

void TestLinearSortingFunc(int (*sort_func)(int arr[], size_t length, size_t num_of_threads), char *sort_func_name)
{
	int arr[RAND_SIZE] = {0};
	int seeds[3] = {2,3,10};
	double cpu_time_used[3] = {0};
	size_t i = 0;
	int status = 0;
    size_t threads[] = {1, 2, 4 ,8, 16};
    size_t j = 0;
	size_t fails_counter = 0;
	clock_t start, end;
    
    for (j = 0; j < 5; ++j)
    {
        for (i = 0; i < 4; ++i)
        {
            RandomLimitedInput(arr, seeds[i],RAND_RANGE);
            /*printArray(arr, RAND_SIZE);*/
                        
            start = clock();
            status = sort_func(arr, RAND_SIZE, threads[j]);
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
               /* printArray(arr, RAND_SIZE);*/
            }
            
            cpu_time_used[i] = 1000* ((double) (end - start)) / CLOCKS_PER_SEC;
        }
        
        if (0 == fails_counter)
        {
            printf(GREEN"Test %s, PASSED, for %lu threads\n",sort_func_name, threads[j]);
            printf("Average time for %s is %f [micro-sec]\n\n"RESET_COLOR, sort_func_name, AverageTime(cpu_time_used, 3));
        }
    }
}



void SortingLinxDictLetters(int (*sort_func)(char arr[], size_t length, size_t num_of_threads), char *sort_func_name)
{
	int arr[RAND_SIZE] = {0};
	int seeds[3] = {2,3,10};
	double cpu_time_used[3] = {0};
	size_t i = 0;
	int status = 0;
    size_t threads[] = {1, 2, 4 ,8, 16};
    size_t j = 0, k = 0, l = 0;
	size_t fails_counter = 0;
	clock_t start, end;
    size_t dictionary_size = NUM_OF_COPIES * NUM_OF_WORDS;
    char words[NUM_OF_COPIES * NUM_OF_WORDS] = {'\0'};
    FILE *fp = fopen("/usr/share/dict/words", "r");

    for(l = 0, k = 0; l < NUM_OF_WORDS; ++l)
    {
        fseek(fp, 0, SEEK_SET);

        for (; k < dictionary_size && EOF != words[k]; ++k, words[k] = fgetc(fp))
        {
            if('\n' == words[j])
            {
                words[k] = fgetc(fp);
            }
        }
    }
	fclose(fp);    
    
    for (j = 0; j < 5; ++j)
    {
        for (i = 0; i < 3; ++i)
        {
                
            start = clock();
            status = sort_func(words, NUM_OF_WORDS, threads[j]);
            end = clock();
            
            /*printArrayChar(words, NUM_OF_WORDS); */       
            if (0 != status)
            { 
                ++fails_counter ;
                printf(RED"Test 1 %s FAILED. Function returned status 1 \n"RESET_COLOR,sort_func_name);
            }
            
            if (!IsArraySortedChar(words,NUM_OF_WORDS))
            { 
                ++fails_counter ;
                printf(RED"Test 2 %s FAILED. Result array is not sorted.\n"RESET_COLOR,sort_func_name);
                /*printArray(arr, RAND_SIZE);*/
            }
            
            cpu_time_used[i] = 1000* ((double) (end - start)) / CLOCKS_PER_SEC;
        }
        
        if (0 == fails_counter)
        {
            printf(GREEN"sorting dictionary Test %s, PASSED, for %lu threads\n",sort_func_name, threads[j]);
            printf("Average time for %s is %f [micro-sec]\n\n"RESET_COLOR, sort_func_name, AverageTime(cpu_time_used, 3));
        }
    }
}