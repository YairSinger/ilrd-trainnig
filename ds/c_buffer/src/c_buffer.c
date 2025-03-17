#include <assert.h>
#include <stdlib.h> 	/* malloc, free		*/ 
#include <stdio.h>	 	/* fputs, stderr    */ 
#include <string.h> 	/* memmove 			*/
#include "c_buffer.h"

#define MIN(a,b) (a)<(b)?(a):(b)

 
struct c_buffer
{
#ifndef	NDEBUG
	size_t magic_number;
#endif
	size_t capacity;
	size_t size;
	size_t front;
	size_t rear;
	char buffer[1];
};


/********************************/

c_buffer_t *CBufCreate(size_t capacity)
{
	size_t padding = sizeof(c_buffer_t) - offsetof(c_buffer_t,buffer);
	c_buffer_t *c_buffer = (c_buffer_t *)malloc
							(sizeof(c_buffer_t) + capacity - padding);
#ifndef	NDEBUG
	 c_buffer->magic_number = 0xdabb1e;
#endif
	c_buffer->capacity = capacity;
	c_buffer->size = 0;
	c_buffer->front = 0;
	c_buffer->rear = 0;
	return c_buffer;
}


/*********************************/

void CBufDestroy(c_buffer_t *buffer)
{
	assert(NULL != buffer);
	
#ifndef	NDEBUG
	buffer->magic_number = 0x00;
#endif
	buffer->capacity = 0;
	buffer->size = 0;
	buffer->front = 0;
	buffer->rear = 0;
	free(buffer);
}


/***************************************/

size_t CBufFreeSpace(const c_buffer_t *buffer)
{
	assert(NULL != buffer);
	
	return buffer->capacity - buffer->size;
}	


/****************************************/

size_t CBufBufsiz(const c_buffer_t *buffer)
{
	assert(NULL != buffer);
	
	return buffer->size;
}


/*****************************************/

int CBufIsEmpty(const c_buffer_t *buffer)
{
	assert(NULL != buffer);
	
	return (buffer->size == 0);
}


/*****************************************/

ssize_t CBufWrite(c_buffer_t *buffer, const void *src, size_t count)
{
	ssize_t writen_res = 0;
	size_t space_to_end = 0; 
	
	assert(NULL != buffer);
	assert(NULL != src);
	
#ifndef	NDEBUG
	if (buffer->magic_number != 0xdabb1e)
	{
		return -1;
	}
#endif
	
	space_to_end = buffer->capacity - buffer->rear;
	count = MIN(count,CBufFreeSpace(buffer)); /*shrink count to free space*/
	writen_res = count;
	
	if (count >= space_to_end) 
	{
		memcpy((buffer->buffer + buffer->rear),src, space_to_end);
		buffer->size += space_to_end;
		buffer->rear = 0;
		count -= space_to_end;
		src = (char *) src + space_to_end; 
		
	}
	
	memcpy((buffer->buffer + buffer->rear),src, count);
	buffer->size += count;
	buffer->rear += count;
	
	return writen_res;
}


/***********************************************/

ssize_t CBufRead(c_buffer_t *buffer, void *dest, size_t count)
{
	ssize_t read_res = 0;
	size_t space_to_end = 0; 
	
	assert(NULL != buffer);
	assert(NULL != dest);
	
#ifndef	NDEBUG
	if (buffer->magic_number != 0xdabb1e)
	{
		return -1;
	}
#endif
	space_to_end = buffer->capacity - buffer->front;
	count = MIN(count,buffer->size); /*shrink count to free space*/
	read_res = count;

	if (count >= space_to_end)
	{
		memcpy(dest,(buffer->buffer + buffer->front), space_to_end);
		buffer->size -= space_to_end;
		buffer->front = 0;
		count -= space_to_end;
		dest = (char *) dest + space_to_end;
	}
	
	memcpy(dest,(buffer->buffer + buffer->front), count);
	buffer->size -= count;
	buffer->front += count;
	
	return read_res;

}
