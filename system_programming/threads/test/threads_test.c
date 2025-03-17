#include <stdlib.h> /*malloc*/
#include <stdio.h>
#include <time.h>
#include "threads.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"


#define NUM_OF_THREADS 15
void TestExe1();
void TestExe4();
void TestExe5();

int main()
{
	/*TestExe1();*/	
	TestExe4();
	/*TestExe5();*/

	return 0;
}

void TestExe1()
{
	int *array = NULL;
	size_t i = 0;
	time_t start, end; 
	int fails = 0;
		
	start = time(NULL);
	array = Exe1();
	end = time(NULL);
	
	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		if (i != array[i])
		{
			++fails; 
			printf(RED"Index %lu is %lu\n"RESET_COLOR, i, array[i]);
			;
		}		
	}
	if (0 ==fails)
	{
		printf(GREEN"Exe1 Pass. finished in %ld [sec] whith %lu threads\n"RESET_COLOR, end - start, i);
	}
}

void TestExe4()
{
	time_t start, end;
	size_t result = 0;
	
	start = time(NULL);
	result = Exe4();
	end = time(NULL);
	
	if (1286608554 != result)
	{
		printf(RED"Failed to calculate sum of dividors. returend %lu\n"RESET_COLOR, result);
		
	}
	else
	{
		printf(GREEN"Exe4 Pass. finished in %ld [sec] whith multithreads\n"RESET_COLOR, end - start);
	}
}

void TestExe5()
{
	time_t start, end;
	size_t result = 0;
	
	start = time(NULL);
	result = Exe5();
	end = time(NULL);
	/*22222222056*/
	if (22222222056 != result)
	{
		printf(RED"Failed to calculate sum of dividors. returend %lu\n"RESET_COLOR, result);
		
	}
	else
	{
		printf(GREEN"Exe5 Pass. finished in %ld [sec] with 1 thread\n"RESET_COLOR, end - start);
	}
	
	
}


