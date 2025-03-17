#include <string.h>
#include "strings.h"
#include <stdio.h>
#include <stdlib.h>

void StrCpyTest();
void StrNCpyTest();
void StrNCmpTest();
void StrCaseCmpTest();
void StrChrTest();
void StrDuupTest();
void StrNcatTest();
void StrCatTest();
void StrStrTest();
void StrSpnTest();
void StrLenTest();
void StrCmpTest();
char *strdup(const char *s);
int strcasecmp(const char *s1, const char *s2);

int main()
{
	StrCpyTest();
	StrNCpyTest();
	StrNCmpTest(); 
	StrCaseCmpTest();
	StrChrTest();
	StrDuupTest();
	StrNcatTest();
	StrCatTest();
	StrStrTest();
	StrSpnTest();
	StrLenTest();
	StrCmpTest();
	return 0;

}




void StrCpyTest()
{
	char str1[] = "Test StrCpyTest";
	char str2[40] = {'\0'};
	
	printf(" StrCpy copeid string: \" %s \" \n ", StrCpy(str2, str1));
	printf("strcpy copeid string: \" %s \" \n \n", strcpy(str2, str1));
}


void StrNCpyTest()
{
	char str1[] = "Test StrCpyTest";
	char str2[30] = {'\0'};
	size_t n = 4;
	
	printf("StrNcmp copeid %lu chars string : \" %s \" \n ", n, StrNCpy(str2, str1, n));
	printf("strncmp copeid %lu string: \" %s \" \n\n", n  ,strncpy(str2, str1, n));
}
	
void StrNCmpTest()
{
	char str1[] = "first";
	char str2[] = "firstt";
	size_t n = 3;
	
	printf("testing %lu first chars in strings \n", n);
	printf("StrNCmp of \" %s \" AND \" %s \" results: \
	%d\n", str1, str2, StrNCmp(str1, str2, n));
	printf("strncmp of \" %s \" AND \" %s \" results: \
	%d\n\n", str1, str2, strncmp(str1, str2, n));
}


void StrCaseCmpTest()
{
	char str1[] = "one";
	char str2[] = "ONE";
	char str3[] = "ONEy";
	
	printf("StrCaseCmp of \" %s \" AND \" %s \" results: \
	%d\n", str1, str2, StrCaseCmp(str1, str2));
	
	printf("strcasecmp of \" %s \" AND \" %s \" results: \
	%d\n", str1, str2, strcasecmp(str1, str2));
	
	printf("StrCaseCmp of \" %s \" AND \" %s \" results: \
	%d\n", str2, str3, StrCaseCmp(str2, str3));
	
	printf("strcasecmp of \" %s \" AND \" %s \" results: \
	%d\n\n", str2, str3, strcasecmp(str2, str3));
}


void StrChrTest()
{
	char str1[] = "first";
	char c1 = 'r';
	char c2 = 'l';
	
	printf("StrChr of %c in %s results %c in the address %p\n" ,\
	c1, str1, *StrChr(str1, c1), StrChr(str1, c1));
	printf("strchr of %c in %s results %c in the address %p\n" ,\
	c1, str1, *strchr(str1, c1), strchr(str1, c1));
	
	printf("StrChr of %c in %s results the address %p\n" ,\
	c2, str1, StrChr(str1, c2));
	printf("strchr of %c in %s results the address %p\n\n" ,\
	c2, str1, strchr(str1, c2));
	
}

void StrDuupTest()
{
	char str1[] = "ab";
	char *str2 = "ab";
	char str3[] = "a";
	char *result_p = StrDuup(str1); 
	
	printf("StrDuup results %s \n", (char*)result_p);
	free(result_p);
	result_p = 0;
	
	result_p = strdup(str1);
	printf("strdup results %s \n", result_p);
	free(result_p);
	result_p = 0;
	
	
	result_p = StrDuup(str2);
	printf("StrDuup results %s  \n", result_p);
	free(result_p);
	result_p = 0;
	
	result_p = strdup(str2);
	printf("strdup results %s  \n", result_p);
	free(result_p);
	result_p = 0;
	
	result_p = StrDuup(str3);
	printf("StrDuup results %s  \n", result_p);
	free(result_p);
	result_p = 0;
	
	result_p = strdup(str3);
	printf("strdup results %s  \n\n", result_p);
	free(result_p);
	result_p = 0;
	
}

void StrNcatTest()
{
	char str1[] = "At the end.", str2[30] = "I will be,", str3[30] = "I will be,";
	size_t n = 6;

	printf("StrNcat results %s with: n = %lu\n" , StrNcat( str2 , str1, n), n);
	printf("strncat results %s with: n = %lu\n\n" , strncat( str3 , str1, n), n);

}

void StrCatTest()
{
	char str1[] = "At the end.", str2[30] = "I will be,", str3[30] = "I will be,";
	
	
	printf("Strcat results %s \n" , StrCat( str2 , str1));
	printf("strcat results %s \n\n" , strcat( str3 , str1));
}

void StrStrTest()
{
	char str1[] = "abcdefghi";
	char str2[] = "ghi";
	char str3[] = "jkl";
	
	printf("StrStr results first char of %s in %s is at %p\n", \
	str2, str1, StrStr(str1, str2));
	printf("strstr results first char of %s in %s is at %p\n", \
	str2, str1, strstr(str1, str2));
	
	
	printf("StrStr results first char of %s in %s is at %p\n", \
	str3, str1, StrStr(str1, str3));
	printf("strstr results first char of %s in %s is at %p\n\n", \
	str3, str1, strstr(str1, str3));
	

}



void StrSpnTest()
{
	
	char str1[] = "abcdefghil", str2[] = "ghbkl", str3[] = "klmn";
	
	printf("StrSpn found %lu bytes from prifix %s in %s\n",StrSpn(str2, str1), str2, str1);
	printf("strspn found %lu bytes from prifix %s in %s\n",strspn(str2, str1), str2, str1);
	printf("StrSpn found %lu bytes from prifix %s in %s\n",StrSpn(str3, str1), str3, str1);
	printf("strspn found %lu bytes from prifix %s in %s\n\n",strspn(str3, str1), str3, str1);
}

void StrLenTest()
{

	char str[] = "string";
	printf("length of:\" %s \" with StrLen %lu\n", str,  StrLen(str));
	printf("length of \" %s  \"with strlen %lu\n",str,  strlen(str));
	printf("TestStrLen passed\n\n");
}

void StrCmpTest()
{
	char str1[] = "string";
	char str2[] = "stringg";
	char str3[] = "string";
	printf("%s vs %s results %d\n", str1, str2, StrCmp(str1, str2));
	printf("%s vs %s results %d\n",str2, str1, StrCmp(str2, str1));
	printf("%s vs %s results %d\n", str1, str3, StrCmp(str1, str3));
	
	
}


