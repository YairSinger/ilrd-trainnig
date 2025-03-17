
/*********************************
* Group: OL 147-148 	 		 *
* Project: Fixed Size Allocator  *
* Version: 1.0.0   		 		 *
* Student: Yair singer   		 *
* Reviewer: Noam Lazar	 		 *
* Status:  Approved 	 		 *
*						 		 *
* Date: 	31.8.23      		 *
**********************************/


#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

#define WORD_SIZE sizeof(size_t)

typedef struct fsa fsa_t;



/* O(1) */
size_t FsaSuggestSize(size_t block_size, size_t num_of_blocks);

/* O(n) */
fsa_t *FsaInit(void *pool_ptr, size_t pool_size, size_t block_size);

/* O(1) */
void *FsaAlloc(fsa_t *fsa);

/* O(n) */
size_t FsaCountFree(const fsa_t *fsa);

/* O(1) */
void FsaFree(fsa_t *fsa, void *free_ptr);

#endif /*__FSA_H__*/
