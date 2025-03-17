/***********************************************************
*PROJECT: Word boundery optimization
*
*WRITER: Yair Singer
*
*REVIEWER: Zayd  Abu Snina
*
*STATUS: Approved
*
*DATE: 23.7.23
***********************************************************/
#include <assert.h>
#include <stddef.h> /* size_t */
#include <stdlib.h> /* calloc */
#include "ws9.h"



static size_t  ByteMoltipliedOnWordSize(char c)
{
	size_t result = 0, i = 0;
	
	
	for(; i < WORD_SIZE ; ++i)
	{
		result <<= BYTE_SIZE;
		result |= (size_t)c;
		
	}	
	
	return result;
}

void *Memset(void *s, int c, size_t n)
{
	char * s_runner = s;
	
	
	 assert(NULL != s);
	
	for (;((size_t)s % WORD_SIZE)!= 0 && n > 0; ++s_runner, --n)
		{
			*s_runner = (BYTE) c;
		}
	
	
	for (; n >= WORD_SIZE; n -= WORD_SIZE, s_runner += WORD_SIZE)
	{
		*((size_t *)s_runner) = ByteMoltipliedOnWordSize(c);
	}

	for (; n > 0; ++s_runner, --n)
	{
	 	*s_runner = (BYTE) c;
	}
	 
	return s;
}

void *Memcpy(void *dest, const void *src, size_t n)
{
	char *dest_runner = dest;
		
	assert(NULL != dest);
	assert(NULL != src);
	
	for(; n >= WORD_SIZE; 
	dest_runner = dest_runner + WORD_SIZE
	,src = ((char *) src) + WORD_SIZE, n -= WORD_SIZE)
	{
		*((size_t *)dest_runner) = *((size_t *) src);
	}
	
	for(; n > 0 ; 
	dest_runner = (dest_runner) + 1, src = ((char *) src) + 1, --n)
	{
		*(dest_runner) = *((char *) src);
	}
	
	return dest;
}

void *Memmove(void *dest, const void *src, size_t n)
{
			
	assert(NULL != dest);
	assert(NULL != src);
	
	/* if adresses are in overlap */
	if ((dest > src) && (((BYTE *)src + n) >  (BYTE *) dest))
	{
		for (dest = (BYTE *) dest + n, src = (BYTE *) src + n;
		n > 0; dest = ((BYTE *) dest - 1), src = ((BYTE *) src - 1), --n)
		{
			Memcpy(dest, src, 1);
		}
	}
	else
	{
		Memcpy(dest, src, n);
	}
	
	
	return dest;
}

