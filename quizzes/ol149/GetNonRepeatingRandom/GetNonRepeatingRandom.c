#include <stdio.h>
#include <stdlib.h> /*srand */
#include <time.h>

#define MAX_RAND 100

size_t GetNonRepeatingRandom()
{
	size_t i = 0;
	static int lut[MAX_RAND] = {0};
	static int count = 1;
	size_t rand_i = 0;
	
	srand(time(NULL));
	rand_i = rand() % MAX_RAND;
	
	for (i = rand_i; lut[i] == 1 ; i = (i + 1) % MAX_RAND)
	{
		/*empty loop*/
	}
	
	if (0 == lut[i])
	{
		lut[i] = 1;
		return i;
	}
	else
	{
		for(i = 0; i < MAX_RAND; ++i)
		{
			lut[i] = 0;
		}
		
		return rand_i ;
	}
}

int main()
{
	int lut[MAX_RAND] = {0};
	size_t i = 0, j = 0;
	
	
	for (i = 0 ; i <300; ++i)
	{
		j =  GetNonRepeatingRandom();
		printf("%lu,",j);
		lut[j] += 1; 
	}
	for (i = 0 ; i < MAX_RAND; ++i)
	{
		if (1 != lut[i])
		{
			printf("index %lu with %d\n",i, lut[i]);
		}
	}
	
	
	return 0;
}
