#include <stdlib.h>
#include <stdio.h>

void oneMilChars (char c)
{
	static int lut[256] ={0};
	int max_occ = 0;
	int i = 0;
	
	if (c != '0')
	{
		lut[(int)c] += 1;
	}
	else
	{
		for (i = 0; i < 256; ++i)
		{
			if(lut[i] >= max_occ)
			{
				max_occ = lut[i];
				lut[i] = 0;
			}
		}
		printf("max occour char is %d\n", max_occ);
		
	}
}

size_t CountBitSet (long num)
{
	num = (num & 0x5555555555555555) +
	 ((num >> 1) & 0x5555555555555555); 
    num = (num & 0x3333333333333333) + ((num >> 2) & 0x3333333333333333); 
    num = (num & 0x0F0F0F0F0F0F0F0F) + ((num >> 4) & 0x0F0F0F0F0F0F0F0F);
    num = (num & 0x00FF00FF00FF00FF) + ((num >> 8) & 0x00FF00FF00FF00FF);
    num = (num & 0x0000FFFF0000FFFF) + ((num >> 16) & 0x00FF00FF0000FFFF);
     num = (num & 0x00000000FFFFFFFF) + ((num >> 32) & 0x00000000FFFFFFFF);
     
     return (size_t) num;
    
}


int main()
{
	char arr[9] = {'2','5','5','5','0','1','1','5','0'};
	size_t i = 0;
	
	for(i = 0; i < 9; ++i)
	{
		oneMilChars(arr[i]);
	}
	
	
	if (8 == CountBitSet(11150))
	{
		printf("passed\n");
	}
	
	return 0;
}

    
