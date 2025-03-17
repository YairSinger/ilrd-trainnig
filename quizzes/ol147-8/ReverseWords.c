#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>



char* ReverseWordsOrder(char *str)
{
	size_t i = 0, word_len = 0;
	size_t str_len = strlen(str);
	char *reveresed_str = (char *) calloc (str_len , sizeof(char));
	
	if (NULL == reveresed_str)
	{
		fputs("failed to alocate memory\n", stderr);
		return str;
	}
	
	reveresed_str[str_len] = '\0';
	
	while (str[i] != '\0')
	{
		for (word_len = 0;
		 str[i + word_len] != '\0' && str[i + word_len] != ' ';
		  ++word_len)
		 {
		  /*empty loop */
		 }
		 strncpy(reveresed_str + str_len - i - word_len, str + i, word_len);
		 i += word_len;
		 
		 if (str[i] == ' ')
		 {
		 	++i;
		 	reveresed_str[str_len - i] = ' ';
		 }
		 
	}
	
	return reveresed_str;
}

int main()
{
	
	char str[] = "Test my function";
	char *result = ReverseWordsOrder(str);
	int i = 0;
	printf("before: %s\n", str);
	
	

	printf("after: %s\n", result);
	for (i = 0; i < 17; ++i)
	{
		printf("%c", *(result+i));
	}


	return 0;

}	
