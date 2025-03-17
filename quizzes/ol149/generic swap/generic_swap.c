void GenericSwapPointers(void *ptr_1, void *ptr_2)
{
	*(size_t *)ptr_1 = *(size_t *)ptr_1 ^ *(size_t *)ptr_2;
	*(size_t *)ptr_2 = *(size_t *)ptr_1 ^ *(size_t *)ptr_2;
	*(size_t *)ptr_1 = *(size_t *)ptr_1 ^ *(size_t *)ptr_2;
}


int GenericValueSwap(void *ptr_1, void *ptr_2, size_t size)
{
	void *temp = malloc(sizeof(char) * size);
	
	if (NULL == temp)
	{
		return 1;
	}
	memcpy(temp, ptr_1, size);
	memcpy(ptr_1, ptr_2, size);
	memcpy(ptr_2, temp, size);
	
	free(temp);
	return 0;	
}
