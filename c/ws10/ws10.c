
#include <assert.h> /*assert*/
#include <stddef.h> /*size_t */
#include <string.h> /*strlen */
#include <stdio.h> /*printf */
#include "ws10.h"

#define ZERO_OFFSET 48



static size_t CountDigitsByBase (int num, int base);
static char RepresentationByBase(int num, int base);
static int CharValue(int ch,int base);
static int BaseInPower(int power, int base);



char *IntToString(int num, char *str, int base)
{
	int counter = 0;
	size_t digits = CountDigitsByBase(num, base);
	size_t i = 0;
	
	assert(NULL != str);
	if ( 2 > base || 36 < base )
	{
		return NULL;
	}
	
	if (0 == num)
	{
		str[0] = '0';
		return str;
	}
	
	if (num < 0 )
	{
		str[0] = '-';
		str[digits+1] = '\0';
		num *= -1;
		++i;
	}
	else
	{
		str[digits] = '\0';
		--digits; 
	}	
	
	for (;num > 0;--digits, num /= base, ++counter)
	{
		str[digits] = RepresentationByBase((num % base),base);
	}
	
	return str;
}

int StringToInt(const char *str, int base)
{
	int len = strlen(str);
	int flag = 0;
	int dig_no = 0;
	int result = 0;
	int converted_value = 0;
	int is_positive = 1;
	
	if ('-' == str[0])
	{
		is_positive = -1;
		
	}
	
	for (; len > 0; --len, ++dig_no)
	{
		converted_value = CharValue(str[len-1],base);/*base representation of char */
		if (-1 == converted_value)
		{
			flag = len-2; 
			converted_value = 0;
		} 
		
		result += (converted_value*BaseInPower(dig_no, base));
	}
	
	while (0 < flag)
	{
	 --flag;	
	 result /= 10;
	}
	
	return (result * is_positive);
}

void PrintLettersFrom2StrOnly( unsigned char *str1, size_t size1,unsigned char *str2, size_t size2, unsigned char *str3, size_t size3)
{
	unsigned char ch_lut[256] = {'\0'};
	size_t i = 0;
	assert(NULL != str1);
	assert(NULL != str2);
	assert(NULL != str3);
	
	printf("letters that appear only in str1 & str2 are:\n");
	for (i = 0;i < size1; ++i, ++str1)
	{
		ch_lut[*str1] = *str1; 
	}
	
	for (i = 0;i < size3; ++i, ++str3)
	{
		ch_lut[*str3] = '\0'; 
	}
	
	for (i = 0;i < size2; ++i, ++str2)
	{
		if ('\0' != ch_lut[*str2])
		{
			printf("%c ",*str2);
			ch_lut[*str2] = '\0'; 
		} 
	}
	printf("\n");
}

int IsLittelEndian(void)
{
	int num = 1;
	int *num_p = &num;
	
	return (*((char *)num_p));
	
}
/*************************************************************/
static size_t CountDigitsByBase (int num, int base)
{
	int i = 0;
	
	for (; 0 != num; num /= base, ++i)
	{
	 /*empty loop */	
	}
	return i;
}

static char RepresentationByBase(int num, int base)
{
	
	
	static char chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b','c','d','e','f','g', 'h' , 'i', 'j', 'k','l','m', 'n','o', 'p', 'q', 'r','s', 't', 'u', 'v', 'w', 'x' ,'y', 'z'};		
	
	
	if (base <= 10)
	{
		return (num + ZERO_OFFSET);
	}
	else
	{
		 return chars[num];
	}
}

static int CharValue(int ch,int base)
{
	
	static char base36[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b','c','d','e','f','g', 'h' , 'i', 'j', 'k','l','m', 'n','o', 'p', 'q', 'r','s', 't', 'u', 'v', 'w', 'x' ,'y', 'z'};	
	int i = 0;
	 
	for (i = 0; i < 37 && base36[i] != ch ; ++i)
	{
	 	/*empty loop */
	}
	if (i >= base) 
	{
		return -1;
	}
	
	return i;
}

static int BaseInPower(int power, int base)
{
	int result = 1;
	for (; power > 0 ; result *= base, --power)
	{
	/*empty loop*/
	}
	return result; 
}
