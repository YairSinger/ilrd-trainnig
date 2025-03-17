#include <stddef.h> /*size_t */
#include <limits.h> /*INT_MAX */
#include <stdio.h> /*printf */

long *SumIntPairsToLongs(int ints[], size_t num_of_elelments)
{
		
	long *longs = (long *) ints;
	
	while(num_of_elelments > 0 )
	{
		*((long *) ints) = (long) *ints +  *(ints + 1);
		
		num_of_elelments -=2;
		ints +=2;
	}
	
	return longs;
}

int main()
{
	int arr[6] = {1,0,20,-5,INT_MAX,INT_MAX};
	long res[3] = {1,15,4294967294};
	long *longs = SumIntPairsToLongs(arr, 6);
	size_t  i = 0;
	int fails = 0;
	
	for (i = 0; i < 3; ++i)
	{
		if (longs[i] != res[i])
		{
			++fails;
			printf("failed, %ld vs %ld expected\n", longs[i], res[i]);
		}
	}
	
	if (fails == 0)
	{
		printf("passed\n");
	}
	return 0;
}
