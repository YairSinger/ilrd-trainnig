/***********************************************************
*PROJECT: Structs
*
*WRITER: Yair Singer
*
*REVIEWER: Maor Levi
*
*STATUS: Approved
*
*DATE: 20/7/23
***********************************************************/
#include <stdlib.h> /* realloc */
#include <stdio.h> 	/*printf */
#include <string.h>	/*strlen, */
#include <assert.h>
#include "ws8.h"



void PrintElementArray(element_t *array, size_t size)
{
	size_t i = 0;
	
	assert(NULL != array);
	
	
	for (i = 0; i < size; ++i)
	{
		array[i].print(&array[i]);
	}
}

void AddToElementArray(element_t *array, size_t size, int add_value)
{
	size_t i = 0;
	
	assert(NULL != array);
	
	for (i = 0; i < size; ++i)
	{
		array[i].add(add_value, &array[i]);
	}
}

void CleanupElementArray(element_t *array, size_t size)
{
	size_t i = 0;
	assert(NULL != array);
	
	for (i = 0; i < size; ++i)
	{
		array[i].clean(&array[i]);
	}
}



void PrintInt(element_t *el)
{
	assert(NULL != el);
	printf("element value: %d\n", *((int *) el->value_p));
}

void PrintFloat(element_t *el)
{
	assert(NULL != el);
	printf("element value: %f\n", *((float *) el->value_p));
}

void PrintString(element_t *el)
{
	assert(NULL != el);
	printf("element value: %s\n",(char *) el->value_p);
}

void PrintStudent(element_t *el)
{
	size_t i = 0 ;
	assert(NULL != el);
	printf("student name: %s\n",((student_t *) el->value_p)->name);
	printf("student id: %d\n",((student_t *) el->value_p)->id);
	
	for(i = 0; i < ((student_t *) el->value_p)-> grades_size ; ++i)
	{
		printf("grade  No %ld is: %d\n",i,((student_t *) el->value_p)->grades[i]);
	}
	
}

void AddInt(int value_to_add, element_t *el)
{
	assert(NULL != el);
 	*((int *) el->value_p) += value_to_add;
}

void AddFloat(int value_to_add, element_t *el)
{
	assert(NULL != el);
	*((float *) el-> value_p) += (float) value_to_add;
}

void AddString(int value_to_add, element_t *el)
{		
	char buffer[MAX_DIGITS_IN_INT] = {'\0'};
	size_t len_origin_str = 0;
	size_t len_addition_str = 0;
	
	assert(NULL != el);
	
	sprintf(buffer, "%d", value_to_add);
	len_origin_str = strlen((char *) el->value_p);	
	len_addition_str = strlen(buffer);
	
	el->value_p = (char *) realloc((char *) el->value_p, 
	sizeof(char) * (len_origin_str + len_addition_str +1));
	strncat((char *) el->value_p, buffer, len_addition_str);
	
	 assert (NULL != el->value_p);
}

void AddStudent(int value_to_add, element_t *el)
{
	size_t new_grades_size = (((student_t *) el->value_p )->grades_size + 1);
	assert(NULL != el);
	((student_t *) el->value_p)->grades = 
	(int *) realloc(((student_t *) el->value_p)->grades,
	 sizeof(int) * new_grades_size);
	
	assert(NULL !=((student_t *) el->value_p)->grades);
	((student_t *) el->value_p)->grades[new_grades_size-1] = value_to_add;
	((student_t *) el->value_p)->grades_size = new_grades_size;
}

void CleanUpString(element_t *el)
{
	assert(NULL != el);	
	free(el->value_p);
}

void CleanUpStudent(element_t *el)
{
	assert(NULL != el);
	free(((student_t *) el->value_p)->grades );
}

void DoNothing(element_t *el)
{
	UNUSED(el);
}

