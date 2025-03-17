#include <stdio.h>


int IsSumFound(int *sorted, size_t size, int sum,int index[2])
{
	int i = 0, j = size-1;
	for (;i <= j;++i)
	{
	
		if ((sorted[i] + sorted[j]) == sum)
		{
			index[0] = i;
			index[1] = j;
			return 1;
		}
	
		for(;(sorted[i] + sorted[j]) > sum ; --j)
		{
			/*empty loop*/
		}	
	}
	return 0;
}

	
	
		
	
	




int main (void) 
{
	int sorted[] = {2, 4, 7, 12, 14};
	int indexs[2] = {0};
	
	
	printf("result of sum 11 is %d indexes %d, %d\n", IsSumFound(sorted, 5, 11, indexs));
printf("result of sum 26 is %d indexes %d, %d\n", IsSumFound(sorted, 5, 26, indexs));

return 0;
}

