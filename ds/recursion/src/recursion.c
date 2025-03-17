#include <assert.h>
#include <stdlib.h> /*calloc */
#include "recursion.h"

static unsigned long FibTailHelper(unsigned int n, unsigned int a, unsigned int b)
{
	if (0 == n)
	{
		return a;
	}
	else 
	{
		return FibTailHelper(n-1, b, a+b);
	}
}

unsigned long FibTail(unsigned int n)
{
	return FibTailHelper(n,0, 1);
}


unsigned long GetnFibonacciElementIterative(unsigned int n)
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
/*================ Fib ========================*/
unsigned long Fib(unsigned int n)
{
	if (n == 1)
	{
		return 1;
	}
	
	if (n == 0)
	{
		return 0;
	}
	
	return(Fib(n-1) + Fib(n-2));
}


/*================ StrLen ========================*/
size_t StrLen(const char *s)
{
	if ('\0' == *s)
 	{
 		return 0;
 	}
 	else
 	{
 		return (1 + StrLen(s + 1));
 	}
}


/*================ StrCmp ========================*/
int StrCmp(const char *s1, const char *s2)
{
	if (*s2 != *s1 || '\0' == *s1)
 	{
 		return (*s1 - *s2);
 	}
 	else
 	{
 		return StrCmp(s1 + 1, s2 + 1);
 	}

}


/*================ StrCpy ========================*/
char *StrCpy(char *dest, const char *src)
{
	if ('\0' == *src)
 	{
 		*dest = *src;
 		return dest;
 	}
 	else
 	{
 		*dest = *src;
 		return StrCpy(dest + 1, src + 1);
 	}
}


/*================ StrCat ========================*/
char *StrCat(char *dest, const char *src)
{
	if('\0' == *dest)
	{
		return StrCpy(dest, src);
	}
	else
	{
		return (StrCat(dest + 1, src) - 1);
	}	
}


/*================ StrStr ========================*/
char *StrStr(const char *haystack,const char *needle)
{
	if('\0' == *haystack)
	{
		return NULL;
	}
	
	if(*haystack == *needle && (0 == StrCmp(haystack,needle)) )
	{
		return (char *)haystack;
	}		
	else
	{
		return StrStr(haystack + 1, needle);
	}
}


/*================ SortStackRec (with static InsertSortedStack) ========================*/
static void InsertSortedStack(stack_t *stack_ptr, const void *element)
{
	int temp = 0;
	
	if(StackIsEmpty(stack_ptr))
	{
		StackPush(stack_ptr, element);
	}
	else
	{
		StackPeek(stack_ptr, (void *)&temp);
		if (temp <= *((int *)element))
		{
			StackPush(stack_ptr, element);
		}
		else
		{
			StackPop(stack_ptr);
			InsertSortedStack(stack_ptr, element);
			StackPush(stack_ptr, (void *)&temp); 
		}
	}

}

void SortStackRec(stack_t *stack_ptr)
{
	int temp = 0;
	
	if(!StackIsEmpty(stack_ptr))
	{
		StackPeek(stack_ptr, (void *)&temp);
		StackPop(stack_ptr);
		SortStackRec(stack_ptr);
		InsertSortedStack(stack_ptr, &temp);
	}
}

/*================ FlipListRec ========================*/


node_t *FlipListRec(node_t *head)
{
	node_t *res = NULL;
	if(NULL == head || NULL == head->next)
	{
		return head;
	}
	res = FlipListRec(head->next);
	head->next->next = head;
	head->next = NULL;
	return res;
}

