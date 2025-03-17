/**************************
* Group: OL 147-148 	  *
* Project: D_Vector		  *
* Version: 1.0.3          *
* Student: Yair singer    *
* Reviewer: Dor	Dalmedigo *
* Status: Approved   	  *
*						  *
* Date: 1.08.23           *
**************************/

#ifndef __D_VECTOR_H__
#define __D_VECTOR_H__

#include <stddef.h> /* size_t */

typedef struct d_vector d_vector_t;

#define GROWTH_FACTOR 2 

/*
@Description: Dynamically allocates a vector.
@Parameters:
			 1. [capacity] - size of vector.
			 2. [element_size] - non-zero byte size of each element.
@Return value: Pointer to the vector OR NULL if fails.
@Time Complexity: O(1)
@Undefined Behavior: [element_size] is 0.
*/
d_vector_t *DVectorCreate(size_t capacity, size_t element_size);

/*
@Description: Frees allocated vector.
@Parameters:
			 1. [vector_ptr] - pointer to the vector.
@Return value: None.
@Time Complexity: O(1)
@Undefined Behavior: [vector_ptr] is NULL.
*/
void DVectorDestroy(d_vector_t *vector_ptr);

/*
@Description: Retrieves pointer to vector element.
@Parameters:
			 1. [vector_ptr] - pointer to the vector.
			 2. [index] - inedx of element in vector.
@Return value: Pointer to the element in vector.
@Time Complexity: O(1)
@Undefined Behavior: [inedx] is equal/higher than vector size.
                     [vector_ptr] is NULL.
*/
void *DVectorGetElementAccess(const d_vector_t *vector_ptr, size_t index);

/*
@Description: Inserts element to the end of a vector, 
              allocates memory if needed.
@Parameters:
			 1. [vector_ptr] - pointer to the vector.
			 2. [element] - pointer to inserted element.
@Return value: 0 on succuss, 1 on realloc fail.
@Time Complexity: Amortized O(1)
@Undefined Behavior: [element] is NULL or not size of stack element.
                     [vector_ptr] is NULL.
*/
int DVectorPushBack(d_vector_t *vector_ptr, const void *element);

/*
@Description: Removes the last element of a vector.
@Parameters:
			 1. [vector_ptr] - pointer to the vector.
@Return value: none.
@Time Complexity: O(1)
@Undefined Behavior: [vector_ptr] is NULL.
                     [vector_ptr] current size is 0.
*/
void DVectorPopBack(d_vector_t *vector_ptr);

/*
@Description: Retrieves current size of vector.
@Parameters:
			 1. [vector_ptr] - pointer to the vector.
@Return value: size of vector.
@Time Complexity: O(1)
@Undefined Behavior: [vector_ptr] is NULL.
*/
size_t DVectorSize(const d_vector_t *vector_ptr);

/*
@Description: Retrieves current capacity of vector.
@Parameters:
			 1. [vector_ptr] - pointer to the vector.
@Return value: capacity of vector.
@Time Complexity: O(1)
@Undefined Behavior: [vector_ptr] is NULL.
*/
size_t DVectorCapacity(const d_vector_t *vector_ptr);

/*
@Description: Shrinks current capacity of vector to current size.
@Parameters:
			 1. [vector_ptr] - pointer to the vector.
@Return value: 0 on succuss, 1 on realloc fail.
@Time Complexity: O(n)
@Undefined Behavior: [vector_ptr] is NULL.
*/
int DVectorShrink(d_vector_t *vector_ptr);

/*
@Description: Reserves memory for current vector.
@Parameters:
			 1. [vector_ptr] - pointer to the vector.
			 2. [capacity] - amount of memory to reserve.
			                 if capacity is lower than vector capacity,
			                 function does nothing.
@Return value: 0 on succuss, 1 on realloc fail.
@Time Complexity: O(n)
@Undefined Behavior: [vector_ptr] is NULL.
*/
int DVectorReserve(d_vector_t *vector_ptr, size_t capacity);

#endif /* __D_VECTOR_H__ */
