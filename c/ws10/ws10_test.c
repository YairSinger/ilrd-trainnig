#include <stdio.h>  /*printf*/

#include "ws10.h"


int TestIntToStr(void);

int main()
{
	int a = 5391, Base_no = 17;
	char s_str[32] = {'\0'};
	char str2[32] = "5419B19";
	unsigned char str3[] = {'&', '8', ' ', '\0', '!'};
	unsigned char str4[] = {'5', ' ', '\0', '!', '8', '8', '8', '8' };
	unsigned char str5[] = {'\0' , '0', '\0'};
	
	
		
		
		IntToString(a, s_str,Base_no);
		printf("%d on base of  %d is %s\n",a, Base_no,  s_str);
			
	  	
		printf("string to int: %s on base of  %d is  %d \n",str2, 10, StringToInt(str2,10));
  	
  	
  	/*ex 2*/
  	 
  	PrintLettersFrom2StrOnly( str3, 5, str4, 8, str5, 3);
  	
  	/*ex 3*/
  	if (IsLittelEndian())
  	{
  		printf("This machine is Little-endian\n");
  	}
  	else
  	{
  		printf("This machine is  NOT Little-endian\n");
  	}
  	
  	/*ex 4 */
  	if (IS_LITTLE_ENDIAN)
  	{
  		printf("This machine is Little-endian\n");
  	}
  	else
  	{
  		printf("This machine is  NOT Little-endian\n");
  	}
  	
  	TestIntToStr();
  	return 0;
}

int TestIntToStr(void)
{
	int array[] ={0,1,-1,10,11};
	char result[32] = {'\0'};
	char result_ref[32] ={'\0'};
	int i = 0, j = 0;
	
	/*base10 tests*/
	for (i = 0; i < 5; ++i)
	{
		sprintf(result_ref, "%d",array[i]);
		IntToString(array[i], result, 10);
		for (j = 0; j < 3; ++j)
		{
			if (result[j] != result_ref[j])
			{
				printf("failed base 10 comperison\n");
				return 1;
			}
		}
	}
	printf("passed base 10 comperison\n");
	
	
	
	return 0;
}
	
	 


