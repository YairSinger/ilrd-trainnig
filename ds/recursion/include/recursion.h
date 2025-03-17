/***********************************************************
*PROJECT: recursions
*
*WRITER: Yair Singer
*
*REVIEWER: Avi Gueta
*
*STATUS: resent review
*
*DATE: 13/09/2023
***********************************************************/
/******************
* Version: 1.1 	  *
*******************/
#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>
#include "stack.h"

typedef struct node
{
	int *data;
	struct node *next;
}node_t;

unsigned long GetnFibonacciElementIterative(unsigned int n);

unsigned long Fib(unsigned int n);

unsigned long FibTail(unsigned int n);

size_t StrLen(const char *s);

int StrCmp(const char *s1, const char *s2);

char *StrCpy(char *dest, const char *src);

char *StrCat(char *dest, const char *src);

char *StrStr(const char *haystack,const char *needle);

node_t *FlipListRec(node_t *head);

void SortStackRec(stack_t *stack_ptr);

#endif /* __RECURSION_H__ */
