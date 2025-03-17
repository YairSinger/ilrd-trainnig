#include <stdio.h>


void Bursa( int arr[], size_t size)
{
	size_t i = 0, max_i = 0, cu_min_i = 0, op_min_i = 0;
	int max = arr[0], cu_min = arr[0], op_min = arr[0];
	
	
	for(i = 0; i < size; ++i)
	{
		if((arr[i] >= max) || ((arr[i] - op_min) > (max-cu_min)))
		{
			max = arr[i];
			max_i = i;
		}
		
		
		if (arr[i] < op_min)
		{
			op_min = arr[i];
			op_min_i = i;
		}
	}
	
	if ((op_min < cu_min) && (op_min_i < max_i))
	{
		cu_min = op_min;
		cu_min_i = op_min_i;
	}
	
	printf("the lowest price index is: %ld, highest is: %ld, and prifit  is %d\n", cu_min_i, max_i, max-cu_min);
	
	return;
}
			
int main()
{
	int arrs[] = {6, 15, 3, 5, 1, 4, 9, 2};
	Bursa(arrs, 8);
  
  	return 0;
}

