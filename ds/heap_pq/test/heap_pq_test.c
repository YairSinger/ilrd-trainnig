
/* ----------------------------------------------------------
 * Filename:    heap_pqueue.c
 * Author:      Shahar Molina
 * Reviewer:	Yael Hava
 * Date:        15.11.2023
 * Course:      OL-149
 * Description:	Test unit for Priority Queue Library
 * ----------------------------------------------------------
 */
/*---Includes---*/
#include <ctype.h> /* tolower */
#include <stdio.h> /* printf */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "heap_pq.h" /* API for Priority queue */
#include "testing_unit.h" /* API for tests unit*/

typedef struct
{
	int id;
	int grade;
} grades_t;

/*---Macros---*/
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

/*---Functions Declerations---*/
static void CreateDestroyTests(void);
static void IsEmptyClearTest(void);
static void EnqueueDequeueCountTest(void);
static void PeekTest(void);
static void EraseStructTest(void);

static int AscendingIntCmp(const void *base_val, const void *cmp_to);
static int CompareStudentsByFirstName(const void *student1, const void *student2);
static int MatchStudentsByFirstName(const void * student_v, void * first_name_v);
static int DecendingIntCmp(const void *base_val, const void *cmp_to);


/*---Program---*/
int main(void)
{
    CreateDestroyTests();
	IsEmptyClearTest();
	EnqueueDequeueCountTest();
	PeekTest();
	EraseStructTest();

	PrintTestResults();

	return 0;
}

/*---Functions Definitions---*/
static void CreateDestroyTests(void)
{
	pqueue_t *pq = PQCreate(AscendingIntCmp);
	if (NULL == pq)
	{
		printf(RED "Test: Create and Destroy - FAILED!\n" RESET);
	}

	PQDestroy(pq);
	printf(GREEN "Test: Create and Destroy - PASSED!\n" RESET);
}

static void IsEmptyClearTest(void)
{
	int element = 2;
	pqueue_t *pq = PQCreate(AscendingIntCmp);
	if (NULL == pq)
	{
		printf(RED "PQ Creation - FAILED!\n" RESET);
	}

	TestExpected("IsEmptyClearTest1", PQIsEmpty(pq), 1);
	PQEnqueue(pq, &element);
	TestExpected("IsEmptyClearTest2", PQIsEmpty(pq), 0);
	PQClear(pq);
	TestExpected("IsEmptyClearTest3", PQIsEmpty(pq), 1);

	PQDestroy(pq);
}

static void EnqueueDequeueCountTest(void)
{
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;
	int element5 = 5;
	pqueue_t *pq = PQCreate(AscendingIntCmp);
	if (NULL == pq)
	{
		printf(RED "PQ Creation - FAILED!\n" RESET);
	}

	PQEnqueue(pq, &element1);
	PQEnqueue(pq, &element3);
	PQEnqueue(pq, &element4);
	PQEnqueue(pq, &element2);
	PQEnqueue(pq, &element5);

	TestExpected("Count1", PQSize(pq), 5);

	TestExpected("EnqueueDequeueCountTest1", *(int *)PQDequeue(pq),
	             element5);
	TestExpected("EnqueueDequeueCountTest2", *(int *)PQDequeue(pq),
	             element4);
	TestExpected("EnqueueDequeueCountTest3", *(int *)PQDequeue(pq),
	             element3);
	TestExpected("EnqueueDequeueCountTest4", *(int *)PQDequeue(pq),
	             element2);
	TestExpected("EnqueueDequeueCountTest4", *(int *)PQDequeue(pq),
	             element1);
	TestExpected("Count2", PQSize(pq),
	             0);

	PQDestroy(pq);
}


static void PeekTest(void)
{
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;
	int element5 = 5;
	pqueue_t *pq = PQCreate(DecendingIntCmp);
	if (NULL == pq)
	{
		printf(RED "List Creation - FAILED!\n" RESET);
	}

	PQEnqueue(pq, &element1);
	PQEnqueue(pq, &element3);
	PQEnqueue(pq, &element4);
	PQEnqueue(pq, &element2);
	PQEnqueue(pq, &element5);

	TestExpected("PeekTest1", *((int *)PQPeek(pq)),
	             element1);
	PQDequeue(pq);

	TestExpected("PeekTest2", *((int *)PQPeek(pq)),
	             element2);
	PQDequeue(pq);

	TestExpected("PeekTest3", *((int *)PQPeek(pq)),
	             element3);
	PQDequeue(pq);

	TestExpected("PeekTest4", *((int *)PQPeek(pq)),
	             element4);
	PQDequeue(pq);

	TestExpected("PeekTest5", *((int *)PQPeek(pq)),
	             element5);
	PQDequeue(pq);

	PQDestroy(pq);
}

static void EraseStructTest(void)
{
	student_t *data = NULL;
	student_t student1 = {"Shlomo", "Artzi"};
	student_t student2 = {"Omer", "Adam"};
	student_t student3 = {"Noa", "Kirel"};
	student_t student4 = {"Zuzu", "Zuzu"};
	pqueue_t *pq = PQCreate(CompareStudentsByFirstName);
	if (NULL == pq)
	{
		printf(RED "PQ Creation - FAILED!\n" RESET);
	}

	TestExpected("EraseTest1", PQEnqueue(pq, &student1), 0);
	TestExpected("EraseTest2", PQEnqueue(pq, &student2), 0);
	TestExpected("EraseTest3", PQEnqueue(pq, &student3), 0);
	TestExpected("EraseTest3", PQEnqueue(pq, &student4), 0);

	TestExpected("EraseTest4", PQSize(pq), 4);

	data = (student_t *)PQPeek(pq);
	TestIsEqual("EraseTest5", data->first_name, "Zuzu");
	PQDequeue(pq);

	data = (student_t *)PQErase(pq, MatchStudentsByFirstName, "omer");
	TestIsEqual("EraseTest6", data->first_name, "Omer");

	data = (student_t *)PQErase(pq, MatchStudentsByFirstName, "shlomo");
	TestIsEqual("EraseTest7", data->first_name, "Shlomo");

	data = (student_t *)PQErase(pq, MatchStudentsByFirstName, "Justin");
	if (NULL == data)
	{
		printf(GREEN "Test: 'EraseTest8' - PASSED!" RESET);
	}
	else
	{
		printf(RED "Test: 'EraseTest8' - FAILED!" RESET);
	}

	PQDestroy(pq);
}



/*---Service Functions---*/
static int AscendingIntCmp(const void *base_val, const void *cmp_to)
{
	assert(NULL != base_val && NULL != cmp_to);

	return *(int *)base_val - *(int *)cmp_to;
}

static int DecendingIntCmp(const void *base_val, const void *cmp_to)
{
	assert(NULL != base_val && NULL != cmp_to);

	return *(int *)cmp_to - *(int *)base_val;
}

static int CompareStudentsByFirstName(const void *student1_v, const void *student2_v)
{
	const student_t * student1 = (const student_t *)student1_v;
	const student_t * student2 = (const student_t *)student2_v;

	assert(NULL != student1 && NULL != student2);

	return strcmp(student1->first_name, student2->first_name);
}

static int StrICmp(const char *str1, const char *str2)
{
	assert(NULL != str1 && NULL != str2);
	while (('\0' != *str1) || ('\0' != *str2))
	{
		if (tolower(*str1) != tolower(*str2))
		{
			return *str1 - *str2;
		}
		++str1;
		++str2;
	}

	return 0;
}

static int MatchStudentsByFirstName(const void * student_v, void * first_name_v)
{
	const student_t * student = (const student_t *)student_v;
	const char * first_name = (const char *)first_name_v;

	assert(NULL != student && NULL != first_name);

	return !StrICmp(student->first_name, first_name);
}

