#include <stdio.h>
#include <string.h> /* strlen */
#include "stack.h"

void PrintTestPass();
void PrintTestFail();

int IsMatchPair(char c1, char c2)
{
	int is_match = 0;
	
	if (c1 == '(' && c2 == ')')
	{
		is_match = 1;
	}
	else if (c1 == '[' && c2 == ']')
	{
		is_match = 1;
	}
	else if (c1 == '{' && c2 == '}')
	{
		is_match = 1;
	}
	
	return is_match;
}

int CheckParenthases(char *str)
{
	char temp = '\0';
	int is_empty = 0;
	int is_balanced = TRUE;
	stack_t *st = StackCreate(strlen(str), sizeof(char));
	
	if (NULL == st)
	{
		return -1;
	}
	
	while ('\0' != *str && TRUE == is_balanced)
	{
		if ('(' == *str || '[' == *str || '{' == *str)
		{
			StackPush(st, (const void *)str);
		}
		else if (')' == *str || ']' == *str || '}' == *str)
		{			 
			StackPeek(st,(void *) &temp);
			
			if (!IsMatchPair(temp, *str))
			{
				is_balanced = FALSE;
			}
			
			StackPop(st);
		}
		
		++str;
	}
	
	if (StackIsEmpty(st))
	{
		is_empty = 1;
	}
	
	StackDestroy(st);
	return is_empty && is_balanced;
}

int main()
{

	char *str = "[{[()()]}]";
	char *str1 = "[[[])";
	char *str2 = "";
	
	printf("CHACK PARENTHESES\n");
	printf("test_case_balanced:      ");

	if(CheckParenthases(str) == 1)
	{
		PrintTestPass();
	}
	else
	{
		PrintTestFail();
	}
	
	printf("test_case_not_balanced:  ");
	if(CheckParenthases(str1) == 0)
	{
		PrintTestPass();
	}
	else
	{
		PrintTestFail();
	}
	
	printf("test_case_empty_string:  ");
	if(CheckParenthases(str2) == 1)
	{
		PrintTestPass();
	}
	else
	{
		PrintTestFail();
	}
	
	return 0;
}
void PrintTestPass()
{
	printf(" \033[1;32mPASS.\033[0m\n");
}


void PrintTestFail()
{
	printf(" \033[1;31mFAIL.\033[0m\n");	
}


