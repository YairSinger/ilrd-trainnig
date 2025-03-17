#include <stdlib.h> /*malloc*/
#include <string.h> /*strcmp, strncpy */
#include <stdio.h>
#include "vsa.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

void TestVsaInit();
void TestVsaAllocFree();


int main()
{
	TestVsaInit();
	TestVsaAllocFree();
	return 0;
}

void TestVsaInit()
{
	
	size_t pool_size = 80;
	void *pool_ptr = malloc (sizeof(pool_size));
	vsa_t *vsa = NULL;
	size_t fails_counter = 0;

	if (NULL == pool_ptr)
	{
		return;
	}
	
	vsa = VsaInit(pool_ptr, pool_size);
	
	if (NULL == vsa)
	{
		++fails_counter ;
		printf(RED"Test 1 VsaInit FAILED returned null ptr\n"RESET_COLOR);
	}
	
	#ifndef	NDEBUG
	if (56 != VsaLargestBlock(vsa))
	{
		++fails_counter ;
		printf(RED"Test 2 VsaInit FAILED largest block  resulted %lu vs 56 expected\n"RESET_COLOR,VsaLargestBlock(vsa));
	}
	#endif
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test VsaInit PASSED\n"RESET_COLOR);
	}
	free (pool_ptr);

}

void TestVsaAllocFree()
{
	
	size_t pool_size = 32;
	void *blocks[5] ={NULL};
	char str1[8] = "abcdefg";
	char str2[9] = {'\0'};
	void *pool_ptr = malloc (sizeof(pool_size));
	vsa_t *vsa = NULL;
	size_t i = 0;
	size_t fails_counter = 0;

	vsa = VsaInit(pool_ptr, pool_size);
	
	#ifndef	NDEBUG
	if (8 != VsaLargestBlock(vsa))
	{
		++fails_counter ;
		printf(RED"Test 1 VsaAlloc FAILED largest block  resulted %lu vs 8 expected\n"RESET_COLOR,VsaLargestBlock(vsa));
	}
	#endif

	blocks[0] = VsaAlloc(vsa, 8);
	strncpy((char *)blocks[0], str1,8);
	
	if (0 != strcmp((char *)blocks[0],str1))
	{
		++fails_counter ;
		printf(RED"Test 2 VsaAlloc FAILED to allocate 8 bytes\n"RESET_COLOR);
	}
	#ifndef	NDEBUG
	if (0 != VsaLargestBlock(vsa))
	{
		++fails_counter ;
		printf(RED"Test 3 VsaAlloc FAILED to update next block  resulted %lu vs 0 expected\n"RESET_COLOR,VsaLargestBlock(vsa));
	}
	#endif
	free (pool_ptr);
	pool_ptr = NULL;
	vsa = NULL;
	
	
	/*test multiple allocs largestblock */
	pool_size = 80;
	pool_ptr = malloc (sizeof(pool_size));
	vsa = VsaInit(pool_ptr, pool_size);
	blocks[i] = VsaAlloc(vsa, 8);
	#ifndef	NDEBUG
	if (32) != VsaLargestBlock(vsa))
	{
		++fails_counter ;
		printf(RED"Test 4 VsaAlloc FAILED to update after multiple alloc block  resulted %lu vs 8 expected\n"RESET_COLOR,VsaLargestBlock(vsa));
}
	#endif
		printf("alocation %lu, current free: %lu\n", i, VsaLargestBlock(vsa));		
	}
	
	
	VsaFree(blocks[2]);	
	if (32 != VsaLargestBlock(vsa))
	{
		++fails_counter ;
		printf(RED"Test 5 VsaAlloc FAILED to update after free resulted %lu vs 32 expected\n"RESET_COLOR,VsaLargestBlock(vsa));
	}	
	VsaFree(blocks[1]);	
	if (56 != VsaLargestBlock(vsa))
	{
		++fails_counter ;
		printf(RED"Test 6 VsaAlloc FAILED to update after free resulted %lu vs 56 expected\n"RESET_COLOR,VsaLargestBlock(vsa));
	}	
	VsaFree(blocks[0]);	
	if (80 != VsaLargestBlock(vsa))
	{
		++fails_counter ;
		printf(RED"Test 7 VsaAlloc FAILED to update after free resulted %lu vs 80 expected\n"RESET_COLOR,VsaLargestBlock(vsa));
	}	

	free (pool_ptr);
	pool_ptr = NULL;
	vsa = NULL;
	
if (0 == fails_counter)
	{
		printf(GREEN"Test VsaInit PASSED\n"RESET_COLOR);
	}
}
*/
