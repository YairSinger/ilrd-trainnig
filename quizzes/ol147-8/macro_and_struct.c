#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define TO_LOWER(a) (a) >= 'A' && (a) <= 'Z' ? ((a) + ('a' -'A')) : (a)
#define MAX2(a,b) (a) > (b) ? (a) : (b)
#define MAX3(a,b,c) MAX2(c,MAX2(a,b))
#define OFFSET(s,f) &((size_t)(s).(f)) - &((size_t)(s))

union a
{
	int a;
	char s;
	
};

int main()
{
	char a = 'A';
	char b = '2';
	union a structy;
	
	printf("%c\n", TO_LOWER(a));
	printf("%c\n", TO_LOWER(b));
	printf("%d\n", MAX3(1,2,3));
	printf("%d\n", MAX3(3,2,1));
	printf("%d\n", MAX3(1,3,2));
	printf("%lu\n", sizeof(structy));


	return 0;

}	
