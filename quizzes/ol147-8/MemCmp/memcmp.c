#include <stdio.h>
#include <stdlib.h>

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"


#define WORD_SIZE sizeof(size_t)



int MemCmp(const void *src, const void *dest, size_t n)
{
	char *src1 = (char *)src;
	char *dest1 = (char *)dest;
	size_t i = 0;
	
	while(n > 0 && (0 != ((size_t)src1 & (WORD_SIZE -1))))
	{
		if(*src1 != *dest1)
		{
			return (int)(*src1 - *dest1);
		}
		
		--n;
		++src1;
		++dest1;
	}
	
	while(n > WORD_SIZE)
	{
		if(*((size_t *)src1) != *((size_t *)dest1))
		{
			for (i = 0; i < WORD_SIZE; ++dest1, ++src1)
			{
				if(*src1 != *dest1)
				{
					return (int)(*src1 - *dest1);
				}
			}
		}
		
		n -= WORD_SIZE;
		src1 += WORD_SIZE;
		dest1 += WORD_SIZE;
	}
	
	while(n > 0)
	{
		if(*src1 != *dest1)
		{
			return (int)(*src1 - *dest1);
		}
		--n;
	}
	
	return 0;
}

int main()
{
	char src[12] = "destdeyf";
	char dest[12] = "destdeyfj";
	size_t fails_counter = 0;
	size_t i = 0;
	
	

	
	
	if (0 != MemCmp((const void *)(src + 2), (const void *)(dest + 2), 6))
	{
		++fails_counter;
		printf("failed 1\n");
		
	}
	
	
	
	if (0 <= MemCmp((const void *)(src + 2), (const void *)(dest + 2), 9))
	{
		++fails_counter;
		printf("failed 2\n");
		
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN" PASSED\n"RESET_COLOR);
	}
	
	return 0;
}
