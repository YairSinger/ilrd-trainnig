#include <stdio.h>


void Bursa( int prices[], int size)
{
	int i = 0;
	int max = prices[0], max_i = 0;
	int cur_min = prices[0], cur_min_i = 0;
	int op_min = prices[0], op_min_i = 0;
	
	for(i = 0; i < size; ++i)
	{
		if((max <= prices[i]) ||((prices[i]-op_min) > (max-cur_min)))
		{
			max = prices[i];
			max_i = i;
		}
		
		if ((cur_min > prices[i]) && ( i < max_i))
		{
		cur_min = prices[i];
		cur_min_i = i;
		}
		
		if (op_min > prices[i])
		{
			op_min = prices[i];
			op_min_i = i;
		}
	}
	
	if ((op_min < cur_min) && (op_min_i < max_i))
	{
		cur_min = op_min;
		cur_min_i = op_min_i;
	}
	
	printf("the lowest price index is: %d, highest is: %d, and prifit  is %d\n", cur_min_i, max_i, max-cur_min);
}
			
int main()
{
	int pricess[] = {6, 12, 3, 5, 1, 4, 9, 2};
	Bursa(pricess, 8);
  
  	return 0;
}

