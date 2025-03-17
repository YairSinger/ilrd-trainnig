
#include <stdio.h> 		/*printf */
#include <assert.h> 
#include <string.h>  /*strlen*/
#include <stdlib.h>	 /*malloc*/

int FlipOrderOfWords(char* str)
{
	char *cpy = NULL, *runner = NULL;
	char word[100] = {'\0'};
	int i = 0;
	size_t len = strlen(str);
	
	runner = str;
	
	cpy = (char*) malloc (sizeof(char) *(len + 1));
	if (cpy == NULL)
	{	
		return 1;
	}
	*(cpy+len+1) = '\0';
	cpy = cpy+len;
	 
	for ( ; *runner != '\0'; ++runner)
	{
		for(i = 0; *runner != ' ' && *runner != '\0'; ++i, ++runner)
		{
			word[i] = *runner;
		}
		
		if ('\0' == *runner)
		{
			break;
		}
		else
		{
			word[i] = ' ';
		}
		
		for ( ; i >= 0 ; --i, --cpy)
		{
			*cpy = word [i];
			word[i] = '\0';	
		}
	}
	
	strcpy(str, cpy);
	free (cpy);
	return 0;
}

int main()
{
	char str[] = "This will test my function";
	
	
	
	printf("before:  %s\n", str);
	FlipOrderOfWords(str);
	printf("after:  %s\n", str);
	
	return 0;
}
