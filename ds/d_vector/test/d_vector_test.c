/* Name: Shahar Molina
 * Reviewer: Liach Fainer
 * File: d_vector_test.c
 * Date: 31/08/23 */

/*-----------------------Includes------------------------*/
#include <stdio.h>  /*printf*/
#include <assert.h> /*assert*/
#include <string.h> /*strcmp*/

#include "d_vector.h" /* my d_vector library */

/*-------------------Typedef & Macros--------------------*/
#define FIRST_NAME_SIZE 100
#define LAST_NAME_SIZE 100

typedef struct student_t
{
	char first_name[FIRST_NAME_SIZE];
	char last_name[LAST_NAME_SIZE];
} student_t;

/*---------------------Declerations----------------------*/
static void TestIntEven(void);
static void TestIntOdd(void);
static void TestChar(void);
static void TestStudent(void);

/*------------------------Tests--------------------------*/
int main(void)
{
	TestIntEven();
	TestIntOdd();
	TestChar();
	TestStudent();

	return 0;
}

void TestIntEven(void)
{
	d_vector_t *new_vec = VectorCreate(4, sizeof(int));
	int element = 3;
	int elm = 55;

	printf("--------Tests Int-Even--------\n");

	assert(4 == VectorCapacity(new_vec));
	assert(0 == VectorSize(new_vec));
	VectorPushBack(new_vec, &element);
	VectorPushBack(new_vec, &element);
	VectorPushBack(new_vec, &elm);
	VectorPushBack(new_vec, &element);
	assert(4 == VectorSize(new_vec));
	assert(8 == VectorCapacity(new_vec));
	assert(4 == VectorSize(new_vec));
	VectorPopBack(new_vec);
	assert(3 == VectorSize(new_vec));
	VectorShrink(new_vec);
	assert(5 == VectorCapacity(new_vec));
	assert(3 == VectorSize(new_vec));
	VectorPushBack(new_vec, &element);
	assert(4 == VectorSize(new_vec));
	assert(55 == *(int *)VectorGetElem(new_vec, 2));

	VectorDestroy(new_vec);

	printf("PASSED!");
	printf("\n\n");
}

void TestIntOdd(void)
{
	d_vector_t *new_vec = VectorCreate(3, sizeof(int));
	int element = 3;
	int elm = 55;

	printf("--------Tests Int-Odd--------\n");

	assert(3 == VectorCapacity(new_vec));
	assert(0 == VectorSize(new_vec));
	VectorPushBack(new_vec, &element);
	VectorPushBack(new_vec, &element);
	VectorPushBack(new_vec, &elm);
	VectorPushBack(new_vec, &element);
	assert(4 == VectorSize(new_vec));
	assert(6 == VectorCapacity(new_vec));
	assert(4 == VectorSize(new_vec));
	VectorPopBack(new_vec);
	assert(3 == VectorSize(new_vec));
	VectorShrink(new_vec);
	assert(4 == VectorCapacity(new_vec));
	assert(3 == VectorSize(new_vec));
	VectorPushBack(new_vec, &element);
	assert(4 == VectorSize(new_vec));
	assert(55 == *(int *)VectorGetElem(new_vec, 2));

	VectorDestroy(new_vec);

	printf("PASSED!");
	printf("\n\n");
}

void TestChar(void)
{
	d_vector_t *new_vec = VectorCreate(4, sizeof(char));
	char element = 'c';
	char elm = 'f';

	printf("--------Tests char--------\n");

	assert(4 == VectorCapacity(new_vec));
	assert(0 == VectorSize(new_vec));
	VectorPushBack(new_vec, &element);
	VectorPushBack(new_vec, &element);
	VectorPushBack(new_vec, &elm);
	VectorPushBack(new_vec, &element);
	assert(4 == VectorSize(new_vec));
	assert(8 == VectorCapacity(new_vec));
	assert(4 == VectorSize(new_vec));
	VectorPopBack(new_vec);
	assert(3 == VectorSize(new_vec));
	VectorShrink(new_vec);
	assert(5 == VectorCapacity(new_vec));
	assert(3 == VectorSize(new_vec));
	VectorPushBack(new_vec, &element);
	assert(4 == VectorSize(new_vec));
	assert('f' == *(char *)VectorGetElem(new_vec, 2));

	VectorDestroy(new_vec);

	printf("PASSED!");
	printf("\n\n");
}

static void TestStudent(void)
{
	d_vector_t *new_vec = VectorCreate(4, sizeof(student_t));
	student_t element = {"hello", "world"};
	student_t elm = {"world", "wow"};
	student_t *s = NULL;

	printf("--------Tests student_t--------\n");

	assert(4 == VectorCapacity(new_vec));
	assert(0 == VectorSize(new_vec));
	VectorPushBack(new_vec, &element);
	VectorPushBack(new_vec, &element);
	VectorPushBack(new_vec, &elm);
	VectorPushBack(new_vec, &element);
	assert(4 == VectorSize(new_vec));
	assert(8 == VectorCapacity(new_vec));
	assert(4 == VectorSize(new_vec));
	VectorPopBack(new_vec);
	assert(3 == VectorSize(new_vec));
	VectorShrink(new_vec);
	assert(5 == VectorCapacity(new_vec));
	assert(3 == VectorSize(new_vec));
	VectorPushBack(new_vec, &element);
	assert(4 == VectorSize(new_vec));
	s = VectorGetElem(new_vec, 2);
	assert(0 == strcmp("world", s->first_name));
	assert(0 == strcmp("wow", s->last_name));

	VectorDestroy(new_vec);

	if (0 == strcmp("wow", s->last_name))
	{
		printf("PASSED!");
		printf("\n\n");
	}
}
