
#include <assert.h>
#include "vsa.h"

#define WORD_SIZE sizeof(size_t)

#define WORD_ALLIGNED_SIZE_DOWN(pool) (((pool) % WORD_SIZE) == 0) ?	\
									 	(pool) : 					\
								 		(pool) - (pool % WORD_SIZE) \
								 	
#define WORD_ALLIGNED_SIZE_UP(n_bytes) (((n_bytes) % WORD_SIZE) == 0) ?	\
										 (n_bytes) : 					\
								 		 (n_bytes) - (n_bytes % WORD_SIZE) + WORD_SIZE \

#define IS_VALID_HEADER_PTR(runner) (((size_t)((runner) - (char *)(&(vsa->first_header))) + (((b_header_t *)runner)->block_size) ) <= vsa->pool_size) 

#define IS_LAST_HEADER(runner)  (((size_t)((runner) - (char *)(&(vsa->first_header))) + (((b_header_t *)runner)->block_size) ) == vsa->pool_size) 

#define NEXT_HEADER(runner) ((runner) + sizeof(b_header_t) + (((b_header_t *)(runner))->block_size & ~1))

#define IS_BLOCK_FREE(runner) (((b_header_t *)(runner))->block_size & 1) == 0
#define ALLOCATED_BLOCK_SIZE(size) (size) + 1
#define FREE_BLOCK_SIZE(size) size - 1
#define TRUE 1
typedef struct block_header
{
	size_t block_size;
	
	#ifndef	NDEBUG
		size_t magic_number;
	#endif
	
}b_header_t;							
							
struct vsa
{
	size_t pool_size;
	b_header_t first_header;
};

/*increase block size of first free
 block by header and second free block*/
static char*DefragmentFreedBlocks(char *runner)
{
	size_t second_block_size = 0;
	char *sec = NULL;
	
	assert(NULL != runner);
	
	sec = NEXT_HEADER(runner);
	second_block_size = ((b_header_t *)sec)->block_size;
	((b_header_t *)runner)->block_size += sizeof(b_header_t) + second_block_size;
	
	return runner;
}


vsa_t *VsaInit(void *pool_ptr, size_t pool_size)
{
	vsa_t *vsa = NULL;
	
	assert(NULL != pool_ptr);
	if(sizeof(vsa_t) > pool_size)
	{
		return NULL;
	}
	
	while(0 != (((size_t)pool_ptr) % WORD_SIZE ))
	{
		pool_ptr = (void *)((char *)pool_ptr + 1);
		--pool_size;
	}
	
	pool_size -= sizeof(vsa_t);
	pool_size = WORD_ALLIGNED_SIZE_DOWN(pool_size); /*shrink end side to WORD_SIZE*/
	
	vsa = (vsa_t *)pool_ptr;	
	vsa->pool_size =pool_size;
	vsa->first_header.block_size = vsa->pool_size;
	#ifndef	NDEBUG
		vsa->first_header.magic_number = 0xCAFEB0BA;
	#endif
	return vsa;
}

size_t VsaLargestBlock(vsa_t *vsa)
{
	size_t largest_block = 0;
	int is_last_header = 0;
	char *runner = NULL;
	
	assert(NULL != vsa);
	
	runner = (char *) &vsa->first_header;
	
	
	
	while(TRUE != is_last_header && IS_VALID_HEADER_PTR(runner))
	{
		while(!IS_LAST_HEADER(runner) && IS_BLOCK_FREE(runner) &&
				 IS_VALID_HEADER_PTR(NEXT_HEADER(runner)) &&
				 IS_BLOCK_FREE(NEXT_HEADER(runner)))
		{
			runner = DefragmentFreedBlocks(runner);
		}
		
		if (IS_BLOCK_FREE(runner) && (((b_header_t *)runner)->block_size > largest_block))
		{
			largest_block = ((b_header_t *)runner)->block_size;
		}
		
		if (!IS_LAST_HEADER(runner))
		{
			runner = NEXT_HEADER(runner);
		}
		else
		{
			is_last_header = 1;
		}
		
	}

	return largest_block;
}

void *VsaAlloc(vsa_t *vsa, size_t n_bytes)
{
	size_t block_size_holder = 0;
	char *runner = NULL;
	void *alloc_ptr = NULL;
	int is_last_header = 0;
	assert(NULL != vsa);
	
	if( 0 == n_bytes)
	{
		return NULL;
	}
	
	runner = (char *) &(vsa->first_header);
	n_bytes = WORD_ALLIGNED_SIZE_UP(n_bytes);
	
	
	
	while(TRUE != is_last_header && IS_VALID_HEADER_PTR(runner))
	{
		if (IS_BLOCK_FREE(runner) && (((b_header_t *)runner)->block_size >= n_bytes))
		{
			alloc_ptr = (void *)(runner + sizeof(b_header_t));
			block_size_holder = ((b_header_t *)runner)->block_size;
			((b_header_t *)runner)->block_size = ALLOCATED_BLOCK_SIZE(n_bytes);
			
			/*create new header if needed */
			if(block_size_holder >= (n_bytes + sizeof(b_header_t))) 
			{
				runner = NEXT_HEADER(runner);
				((b_header_t *)runner)->block_size = 
							block_size_holder - n_bytes - sizeof(b_header_t);
				#ifndef	NDEBUG
					((b_header_t *)runner)->magic_number = 0xCAFEB0BA;
				#endif	
			}
			return alloc_ptr;
		}
		
		if (1 != is_last_header && IS_BLOCK_FREE(runner) &&
				 IS_VALID_HEADER_PTR(NEXT_HEADER(runner)) &&
				 IS_BLOCK_FREE(NEXT_HEADER(runner)))
		{
			runner = DefragmentFreedBlocks(runner);
		}
		else if (!IS_LAST_HEADER(runner))
		{
			runner = NEXT_HEADER(runner);
		}
		else
		{
			is_last_header = 1;
		}
	}
	
	return NULL;
}

void VsaFree(void *block_to_free)
{
	char *header = (char *)block_to_free - sizeof(b_header_t);
		
	
	if (NULL == block_to_free)
	{
		return;
	}
	
	#ifndef	NDEBUG
		if (((b_header_t *)header)->magic_number != 0xCAFEB0BA)
		{
			return;
		}
	#endif
	
	((b_header_t *)header)->block_size = FREE_BLOCK_SIZE(((b_header_t *)header)->block_size);
}
	 
