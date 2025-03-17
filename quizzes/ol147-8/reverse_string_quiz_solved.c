#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

void FlipLower(char *str)
{
	char temp = '\0';
	size_t ln = strlen(str)-1, n = ln/2;
	char *str_end = (str + ln);
	
	assert(NULL != str);
	
	for (;0 < n ; n--, str++,str_end--)
	{
		temp = *str;
		*str = tolower(*str_end);
		*str_end = tolower(temp);
	}
	
	*str = tolower(*str);
	
}

void TF(int num)
{
	int i = 1;
	int flag = 0;
	for (i = 1; i <= num; ++i)
	{
		if (0 == (i % 3))
		{
			printf("%s", "T");
			flag = 1;
		}
		if (0 == (i % 5))
		{
			printf("%s", "F");
			flag = 1;
		}
		if (!flag)
		{
			printf("%d", i);
		}
		flag = 0;
	}
	printf("\n\n");
}

int main()
{
	char str[] = "ABCDEFG";
	int num = 15;

	FlipLower(str);
	printf("%s\n", str);
	
	
		TF(num);
	

	return 0;

}	
