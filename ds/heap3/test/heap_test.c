
/* ----------------------------------------------------------
 * Filename:    heap_test.c
 * Author:      Shahar Molina
 * Reviewer:	Yael Hava
 * Date:        15.11.2023
 * Course:      OL-149
 * Description:	Test unit for library
 * ----------------------------------------------------------
 */
/*---Includes---*/
#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

#include "testing_unit.h" /* testing unit API */
#include "heap.h" /* Heap API */


/*---Functions Declerations---*/
static int CreateDestroy(void);
static int PushPopPeekTest(void);
static int RemoveTest(void);
static int RemoveTest(void);

static int IntCmpFunc(const void *a, const void *b);
static int IntMatchFunc(void *element, const void *base_data);

/*---Program---*/
int main(void)
{
	CreateDestroy();
	PushPopPeekTest();
	RemoveTest();
	RemoveTest();

    return 0;
}

/*---Functions Definitions---*/
static int CreateDestroy(void)
{
	heap_t *heap = HeapCreate(IntCmpFunc);
	if (!heap)
	{
		return -1;
	}

	TestExpected("CreateDestroy - IsEmpty", HeapIsEmpty(heap), 1);
	TestExpected("CreateDestroy- Size", HeapSize(heap), 0);

	HeapDestroy(heap);

	return 0;
}

static int PushPopPeekTest(void)
{
	int status = 0;
    int a = 4;
    int b = 10;
    int c = 12;
    int d = 3;
    int e = 2;
    int f = 20;

	heap_t *heap = HeapCreate(IntCmpFunc);
	if (!heap)
	{
		return -1;
	}

	status = HeapPush(heap, &a);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}

	status = HeapPush(heap, &b);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}

    TestExpected("PushPopPeek1 - Peek1", *(int *)HeapPeek(heap), 10);
	TestExpected("PushPopPeek1 - IsEmpty", HeapIsEmpty(heap), 0);
	TestExpected("PushPopPeek1 - Size", HeapSize(heap), 2);

    status = HeapPush(heap, &c);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}

	status = HeapPush(heap, &d);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}

	TestExpected("PushPopPeek2 - Peek2", *(int *)HeapPeek(heap), 12);
	TestExpected("PushPopPeek2 - Size", HeapSize(heap), 4);

	status = HeapPush(heap, &e);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}

	status = HeapPush(heap, &f);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}

	TestExpected("PushPopPeek3 - Peek3", *(int *)HeapPeek(heap), 20);
	TestExpected("PushPopPeek3 - Size", HeapSize(heap), 6);


	HeapPop(heap);
	TestExpected("PushPopPeek4", *(int *)HeapPeek(heap), 12);

	HeapPop(heap);
	TestExpected("PushPopPeek5", *(int *)HeapPeek(heap), 10);

	HeapPop(heap);
	TestExpected("PushPopPeek6", *(int *)HeapPeek(heap), 4);

	TestExpected("PushPopPeek4-6 - Size", HeapSize(heap), 3);

    HeapDestroy(heap);

	return 0;
}

static int RemoveTest(void)
{
    int a = 4;
    int b = 10;
    int c = 12;
    int d = 3;
    int e = 2;
    int f = 20;
	int status = 0;

	heap_t *heap = HeapCreate(IntCmpFunc);
	if (!heap)
	{
		return -1;
	}

	status = HeapPush(heap, &a);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}

	status = HeapPush(heap, &b);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}

    status = HeapPush(heap, &c);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}

	status = HeapPush(heap, &d);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}

	status = HeapPush(heap, &e);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}

	status = HeapPush(heap, &f);
	if (0 != status)
	{
		HeapDestroy(heap);
		return -1;
	}


	HeapRemove(heap, IntMatchFunc, &f);
	TestExpected("Remove1", *(int *)HeapPeek(heap), 12);
	TestExpected("Remove1 - Size", HeapSize(heap), 5);

	HeapRemove(heap, IntMatchFunc, &e);
	TestExpected("Remove2", *(int *)HeapPeek(heap), 12);
	TestExpected("Remove2 - Size", HeapSize(heap), 4);


	HeapRemove(heap, IntMatchFunc, &a);
	TestExpected("Remove3", *(int *)HeapPeek(heap), 12);
	TestExpected("Remove3 - Size", HeapSize(heap), 3);

	HeapDestroy(heap);

	return 0;
}

/*--- Service Functions ---*/
static int IntCmpFunc(const void *a, const void *b)
{
	return *(const int *)a - *(const int *)b;
}

static int IntMatchFunc(void *a, const void *b)
{
	return !IntCmpFunc(a, b);
}
