  #include <stddef.h>

#ifndef __STRINGS_H__
#define __STRINGS_H__

char *StrCpy(char *dest, const char *src);
char *StrNCpy(char *dest, const char *src, size_t n);
int StrNCmp(const char *s1, const char *s2, size_t n);
int StrCaseCmp(const char *s1, const char *s2);
char *StrChr(const char *s, int c);
char *StrDuup(const char *s);
char *StrNcat(char *dest, const char *src, size_t n);
char *StrCat(char *dest, const char *src);
char *StrStr(const char *haystack, const char *needle);
size_t StrSpn(const char *s, const char *accept);
size_t StrLen(char * string);
int StrCmp(char *str1, char * str2);


	
	


#endif /*__STRINGS_H__*/
