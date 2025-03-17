#include <stddef.h>
#include <stdio.h>
#include <string.h> /*strncpy, strcmp */
#include <stdlib.h> /*malloc, free */
#include <sys/types.h> /*pid_t*/
#include <sys/wait.h> /*wait*/
#include <unistd.h>	/*fork*/

#include <unistd.h>  /*Header file for sleep(). man 3 sleep for details. */
#include <pthread.h> 

#define NUM_OF_THREADS 30000
#define NUM_OF_THREADS_2 15



int arr[NUM_OF_THREADS];
int sum_of_dividors[NUM_OF_THREADS];
size_t ex4_input_num = 12345678910;

void *InsertIndexToArr(void*index)
{
	int i = *((int *)index);
	arr[i] = i;
	pthread_exit(NULL);
}




int *Exe1(void)
{
	size_t i = 0;
	pthread_t tid = 0;
	int status = 0;
	int local_arr[NUM_OF_THREADS] = {0};

	
	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		local_arr[i] = i;
		while (0 != (status = pthread_create(&tid, NULL, InsertIndexToArr, (void *)&local_arr[i])))
		{
			/*waiting for thread to terminate and join*/	
		}
		
		pthread_detach(tid); 
	}
	
	return arr;
}

static void *SumOfDividors(void*index)
{
	size_t thread_index = *((size_t *)index);
	size_t range = ex4_input_num / NUM_OF_THREADS_2;
	size_t i = 0;
	
	 
	 for (i = 1 + (range * thread_index); i <= (thread_index + 1) * range; ++i)
	 {
 		if (0 == ex4_input_num % i)
 		{
 			sum_of_dividors[thread_index] += i;
 		}
	 }
	 return NULL;
}

size_t Exe4(void)
{
	size_t i = 0;
	pthread_t tid[NUM_OF_THREADS_2] = {0};
	int status = 0;
	size_t total_sum_of_dividors = 0;
	size_t local_arr[NUM_OF_THREADS_2] = {0};
	
	for (i = 0; i < NUM_OF_THREADS_2; ++i)
	{
		local_arr[i] = i;
		while (0 != (status = pthread_create(&tid[i], NULL, SumOfDividors, &local_arr[i])))
		{
			/*waiting for thread to terminate and join*/	
		}
	}

	for (i = 0; i < NUM_OF_THREADS_2; ++i)
	{
		pthread_join(tid[i], NULL); /*TODO status check*/
	}

	
	
	for (i = 0; i < NUM_OF_THREADS_2; ++i)
	{
		total_sum_of_dividors += sum_of_dividors[i];
	}
	
	return total_sum_of_dividors;
}


size_t Exe5(void)
{
	size_t i = 0;
	size_t total_sum_of_dividors = 0;

	for (i = 1 ; i <= ex4_input_num; ++i)
	{
 		if (0 == ex4_input_num % i)
 		{
 			total_sum_of_dividors += i;
 		}
	}
	return total_sum_of_dividors;
}
