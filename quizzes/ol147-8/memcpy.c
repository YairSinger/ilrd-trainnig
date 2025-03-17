
#include <stdio.h> 		/*printf */
#include <assert.h> 
#include <string.h>  /*strlen*/
#include <stdlib.h>	 /*malloc*/

void Memcpy (void *dest, const void *src, size_t n)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	char *dest_run = (char *) dest;
	while (((src & 7) != 0) && (n > 0))
	{
		*dest_run = (char *) *src;
		dest_run =  dest_run + 1;
		src = (char *) src + 1;
		--n;
	}
	
	while (n >= WORD_SIZE)
	{
		*dest_run = (size_t *) *src; 
		src = (char *) src + sizeof(size_t);
		dest_run = dest_run + sizeof(size_t);
		n -= sizeof(size_t);
	}
	
	while (n > 0)
	{
		*dest_run = (char *) *src;
		dest_run =  dest_run + 1;
		src = (char *) src + 1;
		--n;
	}
	
	return dest;
}

int main()
{
	
	
	return 0;
}
