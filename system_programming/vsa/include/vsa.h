/*********************************
* Group: OL 147-148 	 		 
* Project: Variable Size Allocator  
* Version: 1.0.0   		 		 
* Student: Yair singer   		 
* Reviewer: Maor Halevy 		 
* Status:  re-sent	 		 
*						 		 
* Date: 	6.9.23      		 
**********************************/



#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t;

/*
@Description: Initializes the memory area requested
              by the user, according to a     given
              size and a valid pointer which may be 
              used up to that size. 
@Return value: pointer to vsa_t, NULL on failure.
@Notes: pool_ptr has to be different than NULL.
        pool_size has to be greater than 24 bytes.
@Time Complexity: O(1).
*/
vsa_t *VsaInit(void *pool_ptr, size_t pool_size);

/*
@Description: Search for an appropriate block of the
              requested size inside the  vsa    data 
              strucute. If one has been found  It'll
              be returned. If no such  memory  block
              exist, the function will return   NULL. 
@Return value: pointer to a memory block, 
               NULL on failure.
@Notes: vsa has to be different than   NULL.
        n_bytes should be greater than zero.
@Time Complexity: O(n).
*/
void *VsaAlloc(vsa_t *vsa, size_t n_bytes);

/*
@Description: return the size of  the largest   block 
              available within the  given vsa pointer.
              If no free blocks have  lefts, 0   will
              be returned.
@Return value: the size of the largest avaialbe block,
               0 if there are no avaialbe blocks.
@Notes: vsa has to be different than   NULL.
@Time Complexity: O(n).
*/
size_t VsaLargestBlock(vsa_t *vsa);

/*
@Description: dealocate a block of memory. the memory
              address given  as an argument has to be
              the return  value of a previous call to
              the VsaAlloc function.
@Return value: none.
@Notes: block_to_free has to be the return value of 
        a previous call to  the  VsaAlloc  function.
@Time Complexity: O(1).
*/
void VsaFree(void *block_to_free);

#endif /*__VSA_H__*/
