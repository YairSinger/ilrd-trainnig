#include <stdio.h>
#include <assert.h>
#include "fsa.h"

#define WORD_ALLIGNED_SIZE(size) ((size % WORD_SIZE) == 0) ? \
							size : \
							size + WORD_SIZE - (size % WORD_SIZE)

#define WORD_ALLIGNED_ADD(ptr) (((size_t)ptr % WORD_SIZE) == 0) ?\
							ptr : \
							(size_t *)((size_t)ptr + WORD_SIZE - ((size_t)ptr % WORD_SIZE))\


struct fsa
{
	size_t next_free_offset;
};

size_t FsaSuggestSize(size_t block_size, size_t num_of_blocks)
{
		
	assert (0 != block_size);
	assert (0 != num_of_blocks);

	block_size = WORD_ALLIGNED_SIZE(block_size);
	return  (num_of_blocks * block_size) + sizeof(fsa_t) + WORD_SIZE - 1;
}
/*fsa_t *FsaInit(void *pool_ptr, size_t pool_size, size_t block_size)
{
	fsa_t *fsa = (fsa_t*)pool_ptr;
	char *runner = NULL;
	size_t aligned_block_size = (block_size % sizeof(size_t) == 0) ? 
								block_size:
								block_size/sizeof(size_t)

	if(sizeof(fsa_t)> pool_size)
	{
		return NULL;
	}


}*/

fsa_t *FsaInit(void *pool_ptr, size_t pool_size, size_t block_size)
{
	size_t *runner = NULL;
	size_t overhead_size = sizeof(fsa_t);
	size_t comulative_offset = 0;			/*offset from pool_ptr */
	fsa_t *fsa = (fsa_t *)pool_ptr;
	
	assert(NULL != pool_ptr);
	assert(0 != block_size);
		
	block_size = WORD_ALLIGNED_SIZE(block_size);
	runner = (size_t *)((size_t)pool_ptr + overhead_size);
	runner = WORD_ALLIGNED_ADD(runner); 	/*first block in alligned address*/
	pool_size -= (size_t) ((char *)runner - (char *)pool_ptr);
	comulative_offset = (size_t)((char *)runner - (char *)pool_ptr) + block_size;
	
	fsa->next_free_offset = (size_t)((char *)runner - (char *)pool_ptr);
	
	
	
	while(pool_size  >= (2 * block_size))
	{
		*runner = comulative_offset;
		comulative_offset += block_size;
		runner = (size_t *)((char *)runner + block_size);
		pool_size -= block_size;
	
	}
	
	*runner = (size_t)0;
	return fsa;	

}



void *FsaAlloc(fsa_t *fsa)
{
	void *allocated_block = NULL;
	assert(NULL != fsa);
	
	if ((size_t) 0 == fsa->next_free_offset) /*no free blocks to allocate*/
	{
		return NULL;
	}
	
	allocated_block = (void *) ((char *)fsa + fsa->next_free_offset); 
	
	fsa->next_free_offset =*((size_t *) allocated_block);
	
	
	return allocated_block;

}

size_t FsaCountFree(const fsa_t *fsa)
{
	size_t count = 0;
	char *runner = NULL;

	assert (NULL != fsa);
	
	runner = (char *)fsa;	
	while ((size_t) 0 != *runner)
	{
		runner = (char *)fsa + *((size_t *)runner);
		++count;
	}
	
	return count;
}

void FsaFree(fsa_t *fsa, void *free_ptr)
{
	
	assert(NULL != free_ptr);
	
	*((size_t *)free_ptr) = fsa->next_free_offset;
	fsa->next_free_offset = (size_t)((char *) free_ptr - ((char *) fsa));
	
}
	
