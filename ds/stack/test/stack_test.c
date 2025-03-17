#include <stdio.h>
#include <assert.h>
#include <string.h> /*strcmp */
#include "stack.h"


typedef struct football_card
{
	char player_name[10];
	int shirt_no;
}football_card_t;


void Stack_insert(stack_t *stack, int *data)
{
	int peek = 0; 
	if (StackIsEmpty(stack))
	{
		StackPush(stack, data);
	}
	else
	{
		StackPeek(stack, &peek);
		if (*data >= peek)
		{
			StackPop(stack);
			Stack_insert(stack, data);
			StackPush(stack, &peek);
		}
		else
		{
			StackPush(stack, data);	
		}
	}
}

void TestStackInsert(void)
{
	stack_t *st = StackCreate(10, sizeof(int));
	int fails = 0;
	int arr[] = {7,5,2,1,0};
	size_t i = 0;
	int temp = 0;
	int insert[] = {-1, 6,9,7};
	if(NULL == st )
	{
		return;
	}

	for(i = 0; i < 5; ++i)
	{
		StackPush(st,&arr[i]);
	}

	printf("before insert\n");
	for(i = 0; i < 5; ++i)
	{
		StackPeek(st,&temp);
		printf("%d,", temp);
		StackPop(st);

	}

	for(i = 0; i < 5; ++i)
	{
		StackPush(st,&arr[i]);
	}

	for (i = 0; i < 4; ++i)
	{
		Stack_insert(st, &insert[i]);
	}

	printf("\nafter insert\n");

	for(i = 0; i < 9; ++i)
	{
		StackPeek(st,&temp);
		printf("%d,", temp);
		StackPop(st);

	}

	StackDestroy(st);
	
}

int main(void)
{
	/*football_card_t ronaldo = {"Ronaldo", 20};
	football_card_t mesi;
	size_t card_size = sizeof(ronaldo);
	void *cards_stack = StackCreate(50, card_size);
	
	printf("%d\n",StackIsEmpty(cards_stack));
	
	StackPush(cards_stack, &ronaldo);
	printf("%d\n",StackIsEmpty(cards_stack));
	printf("size %lu\n",StackSize(cards_stack));
	StackPeek(cards_stack,&mesi);
	printf("Mesi's shirt no %d\n", mesi.shirt_no);
	StackPop(cards_stack);
	printf("Is empty status %d\n",StackIsEmpty(cards_stack));
	printf("size %lu\n",StackSize(cards_stack));
	printf("capacity %lu elements\n", StackCapacity(cards_stack));
	StackDestroy((stack_t *)cards_stack);*/
	TestStackInsert();

	
	return 0;
}

