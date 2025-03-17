#include <assert.h>
#include <stddef.h> /*size_t */
#include <limits.h> /*CHAR_BIT */
#include <stdio.h> /*FILE * */
#include "../include/bit_array.h"

#define ARRAY_BIT_SIZE sizeof(bit_arr_t) * CHAR_BIT

bit_arr_t BitArrSetOn(bit_arr_t arr,size_t bit_index)
{
	return (arr | ((size_t)1 << bit_index));
}

bit_arr_t BitArrSetoff(bit_arr_t arr,size_t bit_index)
{
	return (arr & ~((size_t) 1 << bit_index));
}

bit_arr_t BitArrSetBit(bit_arr_t arr, size_t bit_index, unsigned int bool)
{
	return (bool == 0 ? 
	BitArrSetoff(arr,bit_index): BitArrSetOn(arr,bit_index)) ;
}

bit_arr_t BitArrSetAll(bit_arr_t arr)
{
	return (0xffffffffffffffff | arr);
}

bit_arr_t BitArrResetAll(bit_arr_t arr)
{
	return (0x0000000000000000 & arr);
}

unsigned int BitArrGetVal(bit_arr_t arr, size_t bit_index)
{
	return ((arr >> bit_index) & 1);
}

bit_arr_t BitArrFlip(bit_arr_t arr, size_t bit_index)
{
	return (arr ^ ((size_t) 1 << bit_index));	
}

bit_arr_t BitArrMirror(bit_arr_t arr)
{
	bit_arr_t result = 0, mask = 1, i = 0;
	
	for (; i < ARRAY_BIT_SIZE; ++i)
	{
		result <<= 1;
		result |= (mask & arr);
		arr >>= 1;
	}
	
	return result;
}



bit_arr_t BitArrRotateRight(bit_arr_t arr, size_t n)
{
	size_t n_mod = n % 64;
	return ((arr >> (n_mod)) | (arr << (ARRAY_BIT_SIZE - n_mod)));	 
}

bit_arr_t BitArrRotateLeft(bit_arr_t arr, size_t n)
{
	size_t n_mod = n % 64 ;
	return ((arr << (n_mod)) | (arr >> (ARRAY_BIT_SIZE - n_mod)));	 
}


size_t BitArrCountOn(bit_arr_t arr)
{
	arr = (arr & 0x5555555555555555) + ((arr >>  1) & 0x5555555555555555); 
    arr = (arr & 0x3333333333333333) + ((arr >>  2) & 0x3333333333333333); 
    arr = (arr & 0x0f0f0f0f0f0f0f0f) + ((arr >>  4) & 0x0f0f0f0f0f0f0f0f); 
    arr = (arr & 0x00ff00ff00ff00ff) + ((arr >>  8) & 0x00ff00ff00ff00ff); 
    arr = (arr & 0x0000ffff0000ffff) + ((arr >> 16) & 0x0000ffff0000ffff); 
    arr = (arr & 0x00000000ffffffff) + ((arr >> 32) & 0x00000000ffffffff); 
    
    return arr;
}

size_t BitArrCountOff(bit_arr_t arr)
{
	return (ARRAY_BIT_SIZE - BitArrCountOn(arr));
}

char *BitArrToString(bit_arr_t  arr, char *str)
{
	size_t i = 0;
	
	assert(NULL != str);
	
	for (; i < ARRAY_BIT_SIZE ; ++i, arr >>=1)
	{
		str[ARRAY_BIT_SIZE -i-1] = 48 + (arr & (bit_arr_t) 1);
	}
	str[ARRAY_BIT_SIZE] = '\0';
	return str;
}

int WriteMirrorLut()
{
	bit_arr_t i = 0;
	bit_arr_t result_holder = 0;
	FILE *f = fopen("mirror_LUT", "w");
	
	if (NULL == f)
	{
		FILE *f = fopen("mirror_LUT", "w");
		if (NULL == f)
		{
			fputs("falied to open file\n", stderr);
			return -1;
		}
	}
	
	for (i = 0 ; i < 200 ; ++i)
	{
		result_holder = BitArrMirror(i);
		if (0 == fwrite(&result_holder,sizeof(bit_arr_t),1,f))
		{
			fputs("falied to write to the file\n", stderr);
			return -1;
		}	
		
	}
	if (EOF == fclose(f))
	{
		fputs("falied to close file\n", stderr);
		return -1;
	}
	return 0;
}

bit_arr_t ReadMirrorLut(const bit_arr_t value_to_mirror)
{
	
	bit_arr_t result_holder = 0;
	FILE *f = fopen("mirror_LUT", "r");
	
	if (NULL == f)
	{
		FILE *f = fopen("mirror_LUT", "r");
		if (NULL == f)
		{
			fputs("falied to open file\n", stderr);
			return 0;
		}
	}
	if (-1 == fseek(f,sizeof(bit_arr_t) * value_to_mirror, 0))/*find element*/ 
	{
		fputs("falied to seek  file\n", stderr);
		return 0;
	}
	
	if (0 == fread(&result_holder,sizeof(bit_arr_t),1,f))
	{
		fputs("falied to read  file\n", stderr);
		return 0;
		
	}
	
	rewind (f);
	
	if (EOF == fclose(f))
	{
		fputs("falied to close file\n", stderr);
		return 0;
	}
	return result_holder;
}
