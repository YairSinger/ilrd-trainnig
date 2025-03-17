size_t SearchCircularSortedArray(int *arr, size_t size, int target)
{

	int start = 0;
	int end = len - 1;
	int mid = 0;
	
	while (start <= end)
	{
		mid = (end + start) / 2;
		
		if (arr[mid] == target)
		{
			return mid;
		}
		else if (arr[mid] < target && arr[end] >= target )
		{
			start = mid;
		}
		else
		{
			end = mid;
		}
	
	}
	
	return -1;
	
}
