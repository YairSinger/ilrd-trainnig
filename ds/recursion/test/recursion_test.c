#include <stdio.h>  /* printf */
#include <string.h> /*	strlen, strcmp, strcpy, strcat, strstr */
#include "recursion.h"
#include <time.h> 	/*clock_t, clock() */

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

void TestSorteStack();
void TestFlipNodes();
void CompereFibTimes();

int main()
{
	char *str = "test 13 chars";
	char *str1 = "test 1";
	char *str2 = "";
	char str3[10] = {'\0'};
	char str4[25] = "before and ";
	
	
	CompereFibTimes();
	
	if(0 != GetnFibonacciElementIterative(0) || 2 != GetnFibonacciElementIterative(3))
	{
		printf(RED"GetnFibonacciElementIterative FAILED %lu  for 0 and %lu for 3 expected\n"RESET_COLOR, GetnFibonacciElementIterative(0),  GetnFibonacciElementIterative(3));
	}
	else
	{
		printf(GREEN"GetnFibonacciElement PASSED\n"RESET_COLOR);
	}
	
	if(0 != Fib(0) || 2 != Fib(3))
	{
		printf(RED"Fib FAILED %lu  for 0 and %lu for 3 expected\n"RESET_COLOR, Fib(0),  Fib(3));
	}
	else
	{
		printf(GREEN"Fib PASSED\n"RESET_COLOR);
	}
	
	if(strlen(str) != StrLen(str) || strlen(str2) != StrLen(str2))
	{
		printf(RED"StrLen FAILED %lu  for 13 and %lu for 0 expected\n"RESET_COLOR, StrLen(str),  StrLen(str2));
	}
	else
	{
		printf(GREEN"StrLen PASSED\n"RESET_COLOR);
	}
	
	if(strcmp(str, str1) != StrCmp(str, str1))
	{
		printf(RED"StrCmp FAILED resulted %d vs %d expected \n"RESET_COLOR,StrCmp(str, str1),strcmp(str, str1));
	}
	if(strcmp(str, str) != StrCmp(str, str))
	{
		printf(RED"StrCmp FAILED resulted %d vs %d expected \n"RESET_COLOR,StrCmp(str, str1),strcmp(str, str1));
	}
	else
	{
		printf(GREEN"StrCmp PASSED\n"RESET_COLOR);
	}
	
	StrCpy(str3, str1);
	if(0 != strcmp(str3, str1))
	{
		printf(RED"StrCpy FAILED resulted %s vs %s expected \n"RESET_COLOR, str3, str1);
	}
	else
	{
		printf(GREEN"StrCpy PASSED\n"RESET_COLOR);
	}
	
	StrCat(str4, str1);
	if(0 != strcmp(str4, "before and test 1"))
	{
		printf(RED"StrCat FAILED resulted %s vs before and test 1 expected \n"RESET_COLOR, str4);
	}
	else
	{
		printf(GREEN"StrCat PASSED\n"RESET_COLOR);
	}
	
	if(strstr(str4, "est 1") != StrStr(str4, "est 1") || strstr(str4, "est 1yf") != StrStr(str4, "est 1yf") )
	{
		printf(RED"StrStr FAILED %s vs %s expected\n"RESET_COLOR,  StrStr(str4, "est 1"),  strstr(str4, "est 1"));
	}
	else
	{
		printf(GREEN"StrStr PASSED\n"RESET_COLOR);
	}
	
	TestSorteStack();
	TestFlipNodes();
	return 0;
}


void TestSorteStack()
{
	int array[10] = {0,1,1,2,3,4,5,6,7,9};
	int array1[10] = {1,-8,1,1,1,5,-8,-9,20,0};
	int array2[10] = {1,1,1,1,2,2,2,0,0,0};
	int buffer = 0;
	
	stack_t *stack = StackCreate(30, sizeof(int));
	size_t i = 0;
	
	for(i = 0; i < 10; ++i)
	{
		StackPush(stack, (const void *)(array + i));
	}
	
	printf("\nTestSorteStack first test\n");
	printf("before sort\n");
	
	for(i = 0 ;i < 10; ++i)
	{
		StackPeek(stack, &buffer);
		printf("%d,", buffer);
		StackPop(stack); 
	}
	
	for(i = 0; i < 10; ++i)
	{
		StackPush(stack, (const void *)(array + i));
	}
	
	
	/*for(i = 0; i < 3; ++i)
	{
		InsertSortedStack(stack, (const void *)(new_values + i));
	}*/
	
	SortStackRec(stack);
	
	printf("\nafter sort\n");
	
	for(i = 0; i < 10; ++i)
	{
		StackPeek(stack, &buffer);
		printf("%d,", buffer);
		StackPop(stack); 
	}
	
	for(i = 0; i < 10; ++i)
	{
		StackPush(stack, (const void *)(array1 + i));
	}
	
	printf("\nTestSorteStack second test\n");
	printf("before sort\n");
	
	for(i = 0 ;i < 10; ++i)
	{
		StackPeek(stack, &buffer);
		printf("%d,", buffer);
		StackPop(stack); 
	}
	for(i = 0; i < 10; ++i)
	{
		StackPush(stack, (const void *)(array1 + i));
	}
	
	SortStackRec(stack);
	
	printf("\nafter sort\n");
	
	for(i = 0; i < 10; ++i)
	{
		StackPeek(stack, &buffer);
		printf("%d,", buffer);
		StackPop(stack); 
	}
	
	for(i = 0; i < 10; ++i)
	{
		StackPush(stack, (const void *)(array2 + i));
	}
	
	printf("\nTestSorteStack third test\n");
	printf("before sort\n");
	
	for(i = 0 ;i < 10; ++i)
	{
		StackPeek(stack, &buffer);
		printf("%d,", buffer);
		StackPop(stack); 
	}
	for(i = 0; i < 10; ++i)
	{
		StackPush(stack, (const void *)(array2 + i));
	}
	
	SortStackRec(stack);
	
	printf("\nafter sort\n");
	
	for(i = 0; i < 10; ++i)
	{
		StackPeek(stack, &buffer);
		printf("%d,", buffer);
		StackPop(stack); 
	}
	
	StackDestroy(stack);

}


void TestFlipNodes()
{
	node_t list[6] = {0};
	node_t *head = NULL;
	node_t *head_holder = NULL;
	int arr[6] = {0,1,2,3,4,5};
	size_t i = 0;
 	
 	for(i = 0; i < 5; ++i)
 	{
 		list[i].data = &arr[i];
 		list[i].next = list + i + 1;
 	}
 		list[i].data = &arr[i];
 		list[i].next = NULL;
 	
 	head = &list[0];
 	head_holder = head;	
 	printf("\nlist before flip\n");
 	for(; head != NULL; head = head->next)
 	{
 		printf("%d,",*(head->data)); 	
 	}
 	
	head_holder = FlipListRec(head_holder); 		

	printf("\nlist after flip\n");
 	for(; head_holder != NULL; head_holder = head_holder->next)
 	{
 		printf("%d,",*(head_holder->data)); 	
 	}

}

void CompereFibTimes()
{
	clock_t start, end;
	double linar = 0, rec = 0, tail_rec = 0;
	unsigned long res = 0;
	unsigned int input = 30;
	
	start = clock();
	res = GetnFibonacciElementIterative(input); 
	end = clock();
	
	linar = 1000* ((double) (end - start)) / CLOCKS_PER_SEC;
	
	start = clock();
	res = Fib(input); 
	end = clock();
	
	rec = 1000* ((double) (end - start)) / CLOCKS_PER_SEC;
	
	start = clock();
	res = FibTail(input); 
	end = clock();
	
	tail_rec = 1000* ((double) (end - start)) / CLOCKS_PER_SEC;
	
	printf("For %d input:\niterative %f [sec]\nrecursion %f [sec]\nTail recursion %f [sec\n]", input, linar,rec,tail_rec);
}
	
