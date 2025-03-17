#include <stdio.h>
#include <string.h>
#define ASCII_SIZE 256


int FindChar(char *arr, size_t size, char c)
{
	int ascii_lut[ASCII_SIZE] = {0};
	size_t i = 0;
	
	for(i = 0; i < size; ++i)
	{
		ascii_lut[arr[i]] += 1;
	}
	
	return !!ascii_lut[(int)c];
}

int FindChar2(char *arr, size_t size, char c)
{
	char mask = c;
	int res = 0;
	size_t i = 0;
	
	for(i = 0; i < size; ++i)
	{
		res = (!(arr[i] ^ mask)) | res;
	}
	
	return res;
}

void ShiftRight(char *arr, size_t n)
{
	size_t start = 0;
	char temp = '\0';
	size_t end = strlen(arr) - 1;
	
	/*revers all string*/
	for(start = 0; start <= end ; ++ start, -- end)
	{
		temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
	}
	 /*revers first n chars*/
	for(start = 0, end = start + n - 1; start <= end ; ++ start, -- end)
	{
		temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
	}
		 /*revers other chars*/
	for(start = n, end = strlen(arr) - 1; start <= end ; ++ start, -- end)
	{
		temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
	}
}


int main()
{
	char str[] = "012345678";
	char str2[] = "0223456789";
	char str3[] = "0123456";
	size_t i = 0;	
	int fails = 0;
	
	if(1 != FindChar2(str, 9, '3') || 0 != FindChar2(str, 9, '9'))
	{
		++fails;
		printf("FindChar2 faild 1\n");
	}
	
	if(0 != FindChar2(str2, 9, '1'))
	{
		++fails;
		printf("FindChar2 faild 2\n");
	}
	
	if(1 != FindChar2(str3, 9, '3') || 0 != FindChar2(str3, 9, '7'))
	{
		++fails;
		printf("FindChar2 faild 3\n");
	}
	
	printf("before\n");
	for (i = 0; str[i] != '\0'; ++i)
	{
		printf("%c",str[i]);
	}
	
	ShiftRight(str, 3);
	printf("\nafter 3 shifts\n",str[i]);
	for (i = 0; str[i] != '\0'; ++i)
	{
		printf("%c",str[i]);
	}
	printf("\n\n");
	
	printf("before\n");
	for (i = 0; str2[i] != '\0'; ++i)
	{
		printf("%c",str2[i]);
	}
	
	ShiftRight(str2, 3);
	printf("\nafter 3 shifts\n",str2[i]);
	for (i = 0; str2[i] != '\0'; ++i)
	{
		printf("%c",str2[i]);
	}
	printf("\n\n");
	return 0;
	
}
