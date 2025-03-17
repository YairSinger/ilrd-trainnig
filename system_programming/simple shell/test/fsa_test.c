#include <stdlib.h> /*malloc*/
#include <stdio.h>
#include "fsa.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

void TestFsaInit();
void TestFsaAlloc();
void TestFsaSuggestSize();

int main()
{
	TestFsaInit();
	TestFsaAlloc();
	TestFsaSuggestSize();

	return 0;
}

void TestFsaInit()
{
	size_t pool_size = 24;
	void *pool = malloc(pool_size);
	fsa_t *fsa = FsaInit(pool, pool_size, 8);
	size_t fails_counter = 0;
		
	if (NULL == fsa)
	{
		++fails_counter ;
		printf(RED"Test 1 FsaInit FAILED returned null ptr\n"RESET_COLOR);
	}
	printf("%lu\n",FsaCountFree(fsa));
	if ( 2 != FsaCountFree(fsa))
	{
		++fails_counter ;
		printf(RED"Test 2 FsaInit FAILED FsaCountFree %lu vs 2 expected\n"RESET_COLOR, FsaCountFree(fsa));
	}
	free(pool);
	
	pool_size = 26;
	pool = malloc(pool_size);
	fsa = FsaInit((void *)((char *)pool + 2), pool_size - 2, 8);
	if ( 1 != FsaCountFree(fsa))
	{
		++fails_counter ;
		printf(RED"Test 3 FsaInit FAILED while pool addres was unalligned %lu vs 1 expected\n"RESET_COLOR, FsaCountFree(fsa));
	}
	free(pool);
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test FsaInit PASSED\n"RESET_COLOR);
	}
	
		
		
}


void TestFsaAlloc()
{
	size_t pool_size = 80;
	void *pool = malloc(pool_size);
	
	void *alocs[10] = {NULL};
	fsa_t *fsa = FsaInit(pool, pool_size, 8);
	size_t fails_counter = 0;
	size_t i = 0;
	
	for (i = 0; i < 9 ; ++i)
	{
		if ( (9 - i) != FsaCountFree(fsa))
		{
			++fails_counter ;
			printf(RED"Test 1 FsaAlloc FAILED FsaCountFree %lu vs %lu expected\n"RESET_COLOR, FsaCountFree(fsa), (9 - i));
		}
	
		alocs[i] = FsaAlloc(fsa);
	}
	
	if ( (9 - i) != FsaCountFree(fsa))
		{
			++fails_counter ;
			printf(RED"Test 1 FsaAlloc FAILED FsaCountFree %lu vs %lu expected\n"RESET_COLOR, FsaCountFree(fsa), (9 - i));
		}
		
	for (i = 8; i > 0 ; --i)
	{
		FsaFree(fsa, alocs[i]);

		if ( (9 - i) != FsaCountFree(fsa))
		{
			++fails_counter ;
			printf(RED"Test 1 FsaAlloc FAILED at free FsaCountFree %lu vs %lu expected\n"RESET_COLOR, FsaCountFree(fsa), (9 - i));
		}
	
	}
	
	FsaFree(fsa, alocs[i]);
	if (9 != FsaCountFree(fsa))
		{
			++fails_counter ;
			printf(RED"Test 1 FsaAlloc FAILED at free FsaCountFree %lu vs %lu expected\n"RESET_COLOR, FsaCountFree(fsa), (9 - i));
		}
	
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test FsaAlloc&Free PASSED\n"RESET_COLOR);
	}
	free(pool);
}

void TestFsaSuggestSize()
{
	size_t pool_size = 0;
	size_t block_size = 8;
	size_t free_blocks = 0;
	size_t num_of_blocks = 4;
	void *pool =NULL;
	fsa_t *fsa = NULL;
	size_t fails_counter = 0;
	
	pool_size = FsaSuggestSize( block_size, num_of_blocks);
	pool = malloc(pool_size );
	fsa = FsaInit(pool, pool_size, block_size);
	free_blocks = FsaCountFree(fsa); 
	
	if (num_of_blocks > free_blocks)
		{
			++fails_counter ;
			printf(RED"Test 1 FsaSuggestSize FAILED. block_size %lu  and num_of_blocks  %lu resulted %lu\n"RESET_COLOR, block_size, num_of_blocks, free_blocks);
			
		}
	free(pool);
	
	block_size = 3;
	pool_size = FsaSuggestSize( block_size, num_of_blocks);
	pool = malloc(pool_size );
	fsa = FsaInit(pool, pool_size, block_size);
	free_blocks = FsaCountFree(fsa);
	
	if (num_of_blocks > free_blocks)
		{
			++fails_counter ;
			printf(RED"Test 2 FsaSuggestSize FAILED. block_size %lu  and num_of_blocks  %lu resulted %lu\n"RESET_COLOR, block_size, num_of_blocks, free_blocks);
			
		}
	free(pool);
	
	block_size = 10;
	pool_size = FsaSuggestSize( block_size, num_of_blocks);
	pool = malloc(pool_size );
	fsa = FsaInit(pool, pool_size, block_size);
	free_blocks = FsaCountFree(fsa);
	
	if (num_of_blocks > free_blocks)
		{
			++fails_counter ;
			printf(RED"Test 3 FsaSuggestSize FAILED. block_size %lu  and num_of_blocks  %lu resulted %lu\n"RESET_COLOR, block_size, num_of_blocks, free_blocks);
			
		}
	free(pool);
	
	block_size = 8;
	num_of_blocks = 1;
	pool_size = FsaSuggestSize( block_size, num_of_blocks);
	pool = malloc(pool_size );
	fsa = FsaInit(pool, pool_size, block_size);
	free_blocks = FsaCountFree(fsa); 
	
	if (num_of_blocks > free_blocks)
		{
			++fails_counter ;
			printf(RED"Test 4 FsaSuggestSize FAILED. block_size %lu  and num_of_blocks  %lu resulted %lu\n"RESET_COLOR, block_size, num_of_blocks, free_blocks);
			
		}
	free(pool);
	
	
		
	if (0 == fails_counter)
	{
		printf(GREEN"Test FsaSuggestSize PASSED\n"RESET_COLOR);
	}

}
