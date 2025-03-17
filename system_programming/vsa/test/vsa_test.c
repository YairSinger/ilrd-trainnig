#include <stdio.h>
#include <stdlib.h>

#include "vsa.h"

#define GREEN "\033[32;7m"
#define RED "\033[31;7m"
#define DEFAULT "\033[0m"

#define WORD_SIZE sizeof(void *)
#define POOL_SIZE 150

void TestInitAlignment()
{
	size_t error_count = 0;
	char pool[POOL_SIZE] = {0};
	void *block = NULL;
	vsa_t *vsa = VsaInit(pool + 3, POOL_SIZE);
	
	printf("Test struct and first alloc alignment: ");	
	
	if (0 != ((size_t)vsa) % WORD_SIZE)
	{
		++error_count;
		printf(RED"VSA should be aligned with word. \n"DEFAULT);
	}
	
	block = VsaAlloc(vsa, WORD_SIZE);
	
	if (0 != ((size_t)block) % WORD_SIZE)
	{
		++error_count;
		printf(RED"Allocated block should be aligned with word. \n"DEFAULT);
	}
	
    if (0 == error_count)
	{
		printf(GREEN"\t\tPASS\n"DEFAULT);
	}
}


void TestAllocFreeEntire()
{
	size_t error_count = 0;
	size_t largest_block = 0;
	char pool[POOL_SIZE] = {0};
	void *block = NULL;
	vsa_t *vsa = VsaInit(pool, POOL_SIZE);
	
	printf("Test allocating and freeing entire pool: ");	
	
	largest_block = VsaLargestBlock(vsa);
	
	block = VsaAlloc(vsa, largest_block);
	
	if (0 != VsaLargestBlock(vsa))
	{
		++error_count;
		printf(RED"Largest block size after allocating all pool should be 0. \n"DEFAULT);
	}
	
	VsaFree(block);
	if (largest_block != VsaLargestBlock(vsa))
	{
		++error_count;
		printf(RED"Largest block size after freeing should be entire pool. \n"DEFAULT);
	}
		
	
    if (0 == error_count)
	{
		printf(GREEN"\tPASS\n"DEFAULT);
	}
}



void TestAllocDefragmentation()
{
	size_t error_count = 0;
	size_t largest_block = 0;
	char pool[POOL_SIZE] = {0};
	void *allocations[] = {NULL, NULL, NULL};
	vsa_t *vsa = VsaInit(pool, POOL_SIZE);
	
	printf("Test allocatin defragmentation: ");	

	largest_block = VsaLargestBlock(vsa);
		
	allocations[0] = VsaAlloc(vsa, 3);
	if (NULL == allocations[0])
	{
		++error_count;
		printf(RED"Allocation failed. \n"DEFAULT);
	}
	
	if (0 != ((size_t)allocations[0]) % WORD_SIZE)
	{
		++error_count;
		printf(RED"Allocated first block 0 should be aligned with word. \n"DEFAULT);
	}
	
	allocations[1] = VsaAlloc(vsa, 44);
	if (NULL == allocations[1])
	{
		++error_count;
		printf(RED"Allocation failed. \n"DEFAULT);
	}
	
	if (0 != ((size_t)allocations[1]) % WORD_SIZE)
	{
		++error_count;
		printf(RED"Allocated middle block 1 should be aligned with word. \n"DEFAULT);
	}
	
	allocations[2] = VsaAlloc(vsa, 12);
	if (NULL == allocations[2])
	{
		++error_count;
		printf(RED"Allocation failed. \n"DEFAULT);
	}
	
	if (0 != ((size_t)allocations[2]) % WORD_SIZE)
	{
		++error_count;
		printf(RED"Allocated last block 2 should be aligned with word. \n"DEFAULT);
	}
	
	VsaFree(allocations[0]);
	VsaFree(allocations[1]);
	VsaFree(allocations[2]);
	
	allocations[0] = VsaAlloc(vsa, largest_block);
	if (NULL == allocations[0])
	{
		++error_count;
		printf(RED"Defragment failed, should be enough space in memory. \n"DEFAULT);
	}
	
	if (0 != ((size_t)allocations[0]) % WORD_SIZE)
	{
		++error_count;
		printf(RED"Allocated block should be aligned with word. \n"DEFAULT);
	}
	
    if (0 == error_count)
	{
		printf(GREEN"\t\tPASS\n"DEFAULT);
	}
}


void TestLargestDefragmentation()
{
	size_t error_count = 0;
	size_t largest_block = 0;
	size_t size = 0;
	char pool[POOL_SIZE] = {0};
	void *allocations[] = {NULL, NULL, NULL};
	vsa_t *vsa = VsaInit(pool, POOL_SIZE);
	
	printf("Test LargestBlock defragmentation: ");	

	largest_block = VsaLargestBlock(vsa);
		
	allocations[0] = VsaAlloc(vsa, 7);
	if (NULL == allocations[0])
	{
		++error_count;
		printf(RED"Allocation failed. \n"DEFAULT);
	}
	
	if (0 != ((size_t)allocations[0]) % WORD_SIZE)
	{
		++error_count;
		printf(RED"Allocated first block 0 should be aligned with word. \n"DEFAULT);
	}
	
	allocations[1] = VsaAlloc(vsa, 23);
	if (NULL == allocations[1])
	{
		++error_count;
		printf(RED"Allocation failed. \n"DEFAULT);
	}
	
	if (0 != ((size_t)allocations[1]) % WORD_SIZE)
	{
		++error_count;
		printf(RED"Allocated middle block 1 should be aligned with word. \n"DEFAULT);
	}
	
	allocations[2] = VsaAlloc(vsa, 30);
	if (NULL == allocations[2])
	{
		++error_count;
		printf(RED"Allocation failed. \n"DEFAULT);
	}
	
	if (0 != ((size_t)allocations[2]) % WORD_SIZE)
	{
		++error_count;
		printf(RED"Allocated last block 2 should be aligned with word. \n"DEFAULT);
	}
	
	VsaFree(allocations[0]);
	VsaFree(allocations[1]);
	VsaFree(allocations[2]);
	
	size = VsaLargestBlock(vsa);
	if (size != largest_block)
	{
		++error_count;
		printf(RED"Defragment failed, should be enough space in memory. \n"DEFAULT);
		printf("got: %ld, expected: %ld \n", size, largest_block);
	}
	
	if (0 != ((size_t)allocations[0]) % WORD_SIZE)
	{
		++error_count;
		printf(RED"Allocated block should be aligned with word. \n"DEFAULT);
	}
	
    if (0 == error_count)
	{
		printf(GREEN"\t\tPASS\n"DEFAULT);
	}
}



int main()
{
	TestInitAlignment();
	TestAllocFreeEntire();
	TestAllocDefragmentation();
	TestLargestDefragmentation();
	/*
	*/
	return 0;
}
