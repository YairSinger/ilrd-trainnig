#include <assert.h>
#include <stddef.h> /*size_t */
#include <limits.h> /*CHAR_BIT */
#include "../include/bit_array.h"


int main()
{
	
 	




	return 0;
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
	if (EOF == fclose(f)
	{
		fputs("falied to close file\n", stderr);
		return -1;
	}
	return 0;
}

bit_arr_t ReadMirrorLut(const bit_arr_t value_to_mirror)
{
	bit_arr_t i = 0;
	bit_arr_t result_holder = 0;
	mirror_str[65] = {\'\0'};
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
	if (-1 == fseek(f,sizeof(bit_arr_t) * value_to_mirror, SEEK_SET)
	{
		fputs("falied to seek  file\n", stderr);
		return 0;
	}
	
	if (0 == fread(&result_holder,sizeof(bit_arr_t),1,f))
	{
		fputs("falied to read  file\n", stderr);
		return 0;
		
	}
	
	if (EOF == fclose(f)
	{
		fputs("falied to close file\n", stderr);
		return 0;
	}
	return result_holder;
}
