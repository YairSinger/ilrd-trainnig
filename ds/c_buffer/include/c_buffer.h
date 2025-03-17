/**************************
* Group: OL 147-148 	  *
* Project: CBuffer		  *
* Version: 1.0.0   		  *
* Student: Yair singer    *
* Reviewer: Adi	Telem	  *
* Status: pre-reviewed 	  *
*						  *
* Date: 	              *
**************************/


#ifndef __C_BUFFER_H__
#define __C_BUFFER_H__

#include <stddef.h> 	/* size_t  */
#include <sys/types.h>  /* ssize_t */

typedef struct c_buffer c_buffer_t;

/*
@Description: Dynamically allocates a circular buffer.
@Parameters:
			 1. [capacity] - size of cbuffer.
@Return value: Pointer to the cbuffer.
@Time Complexity: O(1)
@Notes: [capacity] must be non-zero.
*/
c_buffer_t *CBufCreate(size_t capacity);

/*
@Description: Deallocates a circular buffer.
@Parameters:
			 1. [buffer] - pointer to cbuffer.
@Return value: None.
@Time Complexity: O(1)
*/
void CBufDestroy(c_buffer_t *buffer);

/*
@Description: Returns the number of free bytes in the buffer.
@Parameters:
			 1. [buffer] - pointer to cbuffer.
@Return value: Free space of buffer.
@Time Complexity: O(1)
@Notes: buffer must be valid.
*/
size_t CBufFreeSpace(const c_buffer_t *buffer);

/*
@Description: Returns size of buffer.
@Parameters:
			 1. [buffer] - pointer to cbuffer.
@Return value: Size of buffer.
@Time Complexity: O(1)
@Notes: buffer must be valid.
*/
size_t CBufBufsiz(const c_buffer_t *buffer);

/*
@Description: Reads from circular buffer.
@Parameters:
			 1. [buffer] - pointer to cbuffer.
			 2. [dest] - a buffer to write data to.
			 3. [count] - amount of bytes to read.
@Return value: Amount of bytes succesfully read.
@Time Complexity: O(n)
@Notes: buffer and dest must be valid.
        Compiled in debug mode, returns -1 when 
        buffer is a non-null invalid pointer.
*/
ssize_t CBufRead(c_buffer_t *buffer, void *dest, size_t count);

/*
@Description: Write to a circular buffer.
@Parameters:
			 1. [buffer] - pointer to cbuffer.
			 2. [src] - a buffer to write data to.
			 3. [count] - amount of bytes to write.
@Return value: Amount of bytes succesfully written.
@Time Complexity: O(n)
@Notes: buffer and src must be valid.
        Compiled in debug mode, returns -1 when 
        buffer is a non-null invalid pointer.
*/
ssize_t CBufWrite(c_buffer_t *buffer, const void *src, size_t count);

/*
@Description: Checks if buffer is empty.
@Parameters:
			 1. [buffer] - pointer to cbuffer.
@Return value: True or false.
@Time Complexity: O(1)
@Notes: buffer must be valid.
*/
int CBufIsEmpty(const c_buffer_t *buffer);


#endif /* __C_BUFFER_H__ */
