#include <stddef.h>
#include <stdio.h>
#include <string.h> /*strncpy, strcmp */
#include <stdlib.h> /*malloc, free */
#include <sys/types.h> /*pid_t*/
#include <sys/wait.h> /*wait*/
#include <unistd.h>	/*fork*/

#include <unistd.h>  /*Header file for sleep(). man 3 sleep for details. */
#include <pthread.h> 

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"




	size_t Exe6(void)
{
	size_t i = 0;
	size_t sum = 0;
    size_t ex4_input_num = 12345678910;

    #pragma omp parallel for reduction(+:sum) /*splits for loop to different multithreaded runs */
	for (i = 1 ; i <= ex4_input_num; ++i)
	{
 		if (0 == ex4_input_num % i)
 		{
 			sum += i;
 		}
	}
	return sum;
}


void TestExe6()
{
	time_t start, end;
	size_t result = 0;
	
	start = time(NULL);
	result = Exe6();
	end = time(NULL);
	
	if (22222222056 != result)
	{
		printf(RED"Failed to calculate sum of dividors. returend %lu\n"RESET_COLOR, result);
		
	}
	else
	{
		printf(GREEN"Exe4 Pass. finished in %ld [sec] whith multithreads\n"RESET_COLOR, end - start);
	}
}

int main ()
{
    TestExe6();


    return 0;
}