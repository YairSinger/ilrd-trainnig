/*******************************************************************************************
* PROJECT: C ws2 strings
* BY: Yair Singer
* REVIWER: Zayd Abu Snina
*
********************************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *StrCpy(char *dest, const char *src)
{
	char * dest_holder = dest;

	assert(NULL != dest);
	assert(NULL != src);
	
	while (*src != '\0')
	{
		*dest = *src;
		++dest;
		++src;
	}
	
	
	*dest = '\0';
	return dest_holder;
	 
	

}

char *StrNCpy(char *dest, const char *src, size_t n)
{

	
	char * dest_holder = dest;

	assert(NULL != dest);
	 assert(NULL != src);
	
	while (*src != '\0' && 0 < n)
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	while (0 < n)
	{
		*dest = '\0';
		++dest;
		n--;
	}
	*dest = '\0';
	return dest_holder;
	
}

int StrNCmp(const char *s1, const char *s2, size_t n)
{
	assert(NULL != s1);
	assert(NULL != s2);
	
	while ('\0' != *s1 && *s1 == *s2 && 0 < n)
	{
		++s1;
		++s2;
		--n;
	}
	return (*s1 - *s2);
}

int StrCaseCmp(const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);
	while ('\0' != *s1 && tolower(*s1) == tolower(*s2))
	{
		++s1;
		++s2;
	}
	return (tolower(*s1) - tolower(*s2));

}

char *StrChr(const char *s, int c) 
{
	assert(NULL != s);
	
	for(; '\0' != *s; ++s)
	{
		if (*s == c) 
		{
			return (char *)s;
		}
	}
		
	 	return NULL;
}

char *StrDuup(const char *s)
{
	
	char *arr = NULL;
	assert(NULL != s);
	arr = (char *)malloc(sizeof(char) * strlen(s)+1);
	return StrCpy(arr, s);
	
}

char *StrNcat(char *dest, const char *src, size_t n)
{
	size_t dest_len = 0;
    size_t i;
    
    assert(NULL != dest);
    assert(NULL != src);
    
    dest_len = strlen(dest);

    for (i = 0; i < n && src[i] != '\0'; i++)
    {
    	dest[dest_len + i] = src[i];
    }
    
    dest[dest_len + i] = '\0';

    return dest;

}

char *StrCat(char *dest, const char *src)
{
	size_t len = strlen(src);
	assert(NULL != dest);
	assert(NULL != src);
	return StrNcat(dest, src, len);
		
}

char *StrStr(const char *haystack, const char *needle)
{
	size_t i = 0;
	assert(NULL != haystack);
	assert(NULL != needle);
	
	while ('\0' != *(haystack+i))
	{
		if (NULL != StrChr(haystack + i, needle[0]))
		{	
			if (0 == StrNCmp(haystack + i, needle, strlen(needle)))
			{
				return (char *)(haystack + i);
			}
		}
		
		++i;
		
	}
	
	return NULL;
}





size_t StrSpn(const char *s, const char *accept)
{
	size_t i = 0;
	
	
	assert (NULL != s);
	assert(NULL != accept);
	
	while ('\0' != *s && StrChr(accept,  *s))
	{
		++i;
		++s;
	}
	
	return i;
}

size_t StrLen( const char * string)
{
	size_t i = 0;
	assert(string != NULL);
	
	for (i = 0; string[i] != '\0' ; i++);
	return i;
		
}

int StrCmp(char *str1, char * str2)
{

	assert(str1 != NULL);
	assert(str2 != NULL);
	while(*str1 != '\0' && *str1 == *str2) 
	{
    
	    	str1++;
		str2++;
	 
	}

	return (*str1 - *str2);
}



