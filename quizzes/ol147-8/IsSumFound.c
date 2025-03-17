#include <stdio.h>


int IsSumFound(int *sorted, size_t size, int sum,int *index)
{
	int i = 0, j = (size-1);
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
	index[0] = -1;
	index[1] = -1;
	return 0;
}

	
int IsSumFound2(int *sorted, size_t size, int sum,int *index)
{
	int head = 0;
	int tail = size -1;
	
	while (head <= tail)
	{
		if (sum == sorted[head] + sorted[tail])
		{
			index[0] = head;
			index[1] = tail;
			return 1;
		}
		
		if (sum > sorted[head] + sorted[tail])
		{
			++head;
		}
		else if (sum < sorted[head] + sorted[tail])
		{
			--tail;
		}
	}
	
	index[0] = -1;
	index[1] = -1;
	return 0;
	
}	
	
	




int main (void) 
{
	int sorted[] = {2, 4, 7, 12, 14};
	int indexs[2] = {0};
	int result = IsSumFound2(sorted, 5, 11, indexs);
	
	
	printf("result of sum 11 is %d indexes %d, %d\n", result,indexs[0],indexs[1]);
	result = IsSumFound2(sorted, 5, 36, indexs);
	printf("result of sum 36 is %d indexes %d, %d\n", result,indexs[0],indexs[1]);

return 0;
}

