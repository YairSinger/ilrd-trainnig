
stack_t *SortStack(stack_t *unsorted)
{
	size_t stack_size = 0
	size_t sorted_size = 0;
	
	size_t moved = 0;
	stack_t *sorted = NULL; 
	
	int temp = 0;
	int *temp_ptr = &temp;
	
	int top = 0;
	int top_ptr = &top;
	int passed_value = 0;
	
	assert(NULL != unsorted);
	
	stack_size = StackSize(unsorted);
	sorted = StackCreate(stack_size, sizeof(int);
	
	if (NULL == sorted)
	{
		return NULL;
	}
	
	StackPeek(unsorted, (void *)temp_ptr);
	StackPop(unsorted);
	StackPush(sorted, const void *temp_ptr); 
	++sorted_size
	
	while (StackSize(sorted) < stack_size)
	{
		StackPeek(unsorted, temp_ptr);
		StackPop(unsorted); 
		
		StackPeek(sorted, top_ptr);
		while(temp > top)
		{
			passed_value = top;
			StackPop(sorted);
			StackPeek(sorted, top_ptr);
			StackPush(unsorted, &passed_value);
			++moved;
		}
		
		StackPush(sorted, temp_ptr);
		while(moved > 0)
		{
			StackPeek(unsorted, &passed_value);
			StackPop(unsorted); 
			StackPush(sorted, &passed_value);
			--moved;
		}
	}
	
	for (i = 0; i < stack_size; ++i)
	{
		StackPeek(sorted, &passed_value);
		StackPop(sorted);
		StackPush(unsorted, &passed_value);
	}
	
	StackDestroy(sorted);
	return unsorted;
}

