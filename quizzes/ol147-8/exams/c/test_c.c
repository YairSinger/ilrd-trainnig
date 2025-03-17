#include <stdio.h>  /* printf */
#include <string.h> /* memcmp */
#include <stddef.h>
#include <assert.h>



#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"



int FlipDigitsInNum(int num);
char MirrorByte(char byte);
int FlipBit(int val, unsigned int n);
size_t CountSetBits(char byte);
char RotateLeft(char byte, unsigned int nbits);
void SwapPointers(int **ptr_a, int **ptr_b);
size_t StrLen(char *str);
int Strcmp (const char *str1, const char *str2);
char *Strcpy(char *dest, const char *src);
char *Strncpy (char *dest, const char *src, unsigned int n);
char *Strcat(char *dest, const char *src);
unsigned long GetnFibonacciElement(unsigned int n);
void IntToString(int num, char *dest);
int MultiplyBy8(int num);


int main()
{
	int a = 5, b = 3, z = -2934;
	int *pa = &a, *pb = &b;
	char str[] = "sfdhvfb";
	char *str2 = "ssvhvfb";
	char str3[11] = {'\0'};
	char str4[11] = {'\0'};
	char str5[11] = "abba";
	char str6[11] = "abba";
	char dest[10] = {'\0'};
	
	
	if(4 != FlipDigitsInNum(4) || 567 != FlipDigitsInNum(765) || -1 != FlipDigitsInNum(-10))
	{
		printf(RED"FlipDigitsInNum FAILED %d, %d, %d\n"RESET_COLOR,FlipDigitsInNum(4),FlipDigitsInNum(765),FlipDigitsInNum(-10));
	}
	else
	{
		printf(GREEN"FlipDigitsInNum PASSED\n"RESET_COLOR);
	}

	if(20 != MirrorByte(40))
	{
	printf(RED"MirrorByte FAILED %d\n"RESET_COLOR,MirrorByte(40));
	}
	else
	{
		printf(GREEN"MirrorByte PASSED\n"RESET_COLOR);
	}
	

	if(5 != FlipBit(7, 1) || 6 != FlipBit(7, 0) )
	{
	printf(RED"FlipBit FAILED %d, %d\n"RESET_COLOR,FlipBit(7, 1), FlipBit(7, 0));
	}
	else
	{
		printf(GREEN"FlipBit PASSED\n"RESET_COLOR);
	}
	

	if(3 != CountSetBits(50) || 8 != CountSetBits((char)255) || 5 != CountSetBits((signed char)-20))
	{
	printf(RED"CountSetBits FAILED %lu, %lu\n"RESET_COLOR,CountSetBits(50), CountSetBits((char)255));
	}
	else
	{
		printf(GREEN"CountSetBits PASSED\n"RESET_COLOR);
	}
	

	if(14 != RotateLeft(7, 1) || 64 != RotateLeft((char) 16, 2))
	{
	printf(RED"RotateLeft FAILED %d, %d\n"RESET_COLOR,RotateLeft((char) 7, 1), RotateLeft((char) 16, 2));
	}
	else
	{
		printf(GREEN"RotateLeft PASSED\n"RESET_COLOR);
	}
	
	printf("before pointers swap %d, %d\n", *pa, *pb); 
	SwapPointers(&pa, &pb);
	printf("after pointers swap %d, %d\n", *pa, *pb); 
	

	if(StrLen(str) != strlen(str) || StrLen(str2) != strlen(str2))
	{
	printf(RED"StrLen FAILED \n"RESET_COLOR);
	}
	else
	{
		printf(GREEN"StrLen PASSED\n"RESET_COLOR);
	}
	
	if(Strcmp(str, str2) != strcmp(str, str2) || Strcmp(str, str) != strcmp(str, str))
	{
	printf(RED"strcmp FAILED \n"RESET_COLOR);
	}
	else
	{
		printf(GREEN"strcmp PASSED\n"RESET_COLOR);
	}
	
	Strcpy(str3,str2);
	strcpy(str4,str2);
	if(0 != Strcmp(str3, str4))
	{
	printf(RED"strcpy FAILED %s vs %s expected\n"RESET_COLOR, str3,  str4);
	}
	else
	{
		printf(GREEN"strcpy PASSED\n"RESET_COLOR);
	}
	Strncpy (str3, str, 4);
	strncpy (str4, str, 4);
	
	if(0 != Strcmp(str3, str4))
	{
	printf(RED"strncpy FAILED %s vs %s expected\n"RESET_COLOR, str3,  str4);
	}
	else
	{
		printf(GREEN"strncpy PASSED\n"RESET_COLOR);
	}
	
	Strcat(str5, str);
	strcat(str6, str);
	if(0 != Strcmp(str6, str6))
	{
	printf(RED"strcat FAILED %s vs %s expected\n"RESET_COLOR, str5,  str6);
	}
	else
	{
		printf(GREEN"strcat PASSED\n"RESET_COLOR);
	}
	

	if(0 != GetnFibonacciElement(0) || 2 != GetnFibonacciElement(3))
	{
	printf(RED"GetnFibonacciElement FAILED %lu  for 0 and %lu for 3 expected\n"RESET_COLOR, GetnFibonacciElement(0),  GetnFibonacciElement(3));
	}
	else
	{
		printf(GREEN"GetnFibonacciElement PASSED\n"RESET_COLOR);
	}
	
	IntToString(z,dest);
	if(0 != Strcmp(dest, "-2934"))
	{
	printf(RED"IntToString FAILED %s vs %s expected\n"RESET_COLOR, dest,  "-2934");
	}
	else
	{
		printf(GREEN"IntToString PASSED\n"RESET_COLOR);
	}
	
	
	if(24 != MultiplyBy8(3))
	{
	printf(RED"MultiplyBy8 FAILED \n"RESET_COLOR);
	}
	else
	{
		printf(GREEN"MultiplyBy8 PASSED\n"RESET_COLOR);
	}
	return 0;
}
/****************************************/
/****************************************/
/****************************************/
/****************************************/



int FlipDigitsInNum(int n)
{
	int sign = 0, temp = 0 , res = 0;
		
	sign = n > 0 ? 1 : -1;
	n = n > 0 ? n : -1 * n;
	
	while(n != 0)
	{
		temp = n % 10;
		n /= 10;
		res *= 10;
		res += temp;
	}
	
	return (res * sign);
}

char MirrorByte(char byte)
{
	char num = byte;
	
	num = (num & 0xF0) >> 4 | (num & 0x0F) << 4;
	num = (num & 0xCC) >> 2 | (num & 0x33) << 2;
	num = (num & 0xAA) >> 1 | (num & 0x55) << 1; 
	
	return num;	
}

int FlipBit(int val, unsigned int n)
{
	int mask = 1;
	mask <<= n;
	return val ^ mask;
}
	
size_t CountSetBits(char num)
{
	
	num = (num & 0x55) + ((num >> 1) & 0x55); 
    num = (num & 0x33) + ((num >> 2) & 0x33); 
    num = (num & 0x0F) + ((num >> 4) & 0x0F);
        
    return (size_t)num;
}

char RotateLeft(char byte, unsigned int nbits)
{
	return ((byte >> (8-nbits)) | (byte << nbits));
}

void SwapPointers(int **ptr_a, int **ptr_b)
{
	int *temp = *ptr_a;
	*ptr_a = *ptr_b;
	*ptr_b = temp;
}

size_t StrLen(char *str)
{
	size_t counter = 0;
	while (*str != '\0')
	{
		++counter;
		++str;
	}
	
	return counter;
}
int Strcmp (const char *str1, const char *str2)
{
	while (*str1 == *str2 && *str1 != '\0')
	{
		++str1;
		++str2;
	}
	
	return (*str1-*str2);
}

char *Strcpy(char *dest, const char *src)
{
	char *dest_run = dest;
	
	while(*src != '\0')
	{
		*dest_run =  *src;
		++dest_run;
		++src;
	}
	
	*dest_run = '\0';
	return dest;
}

char *Strncpy (char *dest, const char *src, unsigned int n)
{
	char *dest_run = dest;
	while(*src != '\0' && n > 0)
	{
		*dest_run = *src;
		++src;
		++dest_run;
		--n;
	}
	while (n > 0)
	{
		*dest_run = '\0';
		--n;
	}
	return dest;
}

char *Strcat(char *dest, const char *src)
{
	char *dest_r = dest + strlen(dest);
	
	return Strcpy(dest_r, src);
}

unsigned long GetnFibonacciElement(unsigned int n)
{
	size_t i = 1;
	unsigned long prev = 0, res = 1, temp = 0;
	
	if (0 == n)
	{
		return 0;
	}
	
	while (i < n)
	{
		temp = res;
		res += prev;
		prev = temp;
		++i;
	}
	
	return res;
}

void IntToString(int num, char *dest)
{
	int len = 0, sign = 0;
	char temp[12] = {'\0'};
	char *temp_run = temp;
	
	if (num < 0)
	{
		num = -1 * num;
		sign = -1;
	}
	while(num != 0)
	{
		*temp_run = (num % 10) + '0' ;
		num /= 10;
		++temp_run;
	}
	
	temp_run = '\0';
	len = strlen(temp);
	if (-1 == sign)
	{
		*dest ='-';
		++dest;
	}
	
	while (len > 0)
	{
		*dest = temp[len - 1];
		--len;
		++dest;
	}
	*dest = '\0';
	
}

int MultiplyBy8(int num)
{
	return (num << 3);
}

void Swap1(int *a, int *b)
{
	assert(a != b);
	
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void swap2(int *a, int *b)
{
	assert(a != b);
	
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void swap3(int *a, int *b)
{
	int temp = *a;
	
	*a = *b;
	*b = temp;
}

