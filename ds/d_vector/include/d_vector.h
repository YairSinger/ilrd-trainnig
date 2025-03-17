/* Name: Shahar Molina
 * Reviewer: Liach Fainer
 * File: d_vector.h
 * Date: 31/08/23 */

#ifndef __ILRD_OL149_D_VECTOR_H__
#define __ILRD_OL149_D_VECTOR_H__

#include <stddef.h> /* size_t */

/**
 * dynamic vector: dynamic array of sequential memory.
 * using random access to add and remove elements.
 * save elements by value.
 * GROWTH FACTOR = 2
 * should be destroied using VectorDestroy after
 * creating using VectorCreate.
 */
typedef struct d_vector d_vector_t;

/**
 * description: creates dynamic vector using capacity and element size.
 * input: size_t capacity- max capacity of created d_vector,
 * size_t element size - size in bytes for each elemnet of the vector.
 * output: a pointer to the new d_vector_t that was allocated, or NULL if
 * allocation failed.
 * time complexity: O(1), space complexity: O(n).
 * notes: the user needs to destroy the vector using the function VectorDestroy.
 */
d_vector_t *VectorCreate(size_t capacity, size_t elem_size);

/**
 * description: Destroys a dynamic vector that was created by the user.
 * input: d_vector_t vec- the vector to be destroied.
 * output: no output - void.
 * time complexity: O(1), space complexity: O(1).
 * notes:
 */
void VectorDestroy(d_vector_t *vec);

/**
 * description: pushes a value to the end of the vector. exapand vector in
 * growth factor when capacity equals size.
 * input: d_vector_t vector - the vector that will recieve the value,
 * const void *value - the pointer to the value to be pushed.
 * output: boolean int - if expansion fails return failure (non-zero),
 * otherwise push back value and return success (0).
 * notes: undefined behaviour if size is equals or greater than capacity.
 * undefined behaviour if the vector is NULL.
 * undefined behaviour if value is NULL. if the user have a previous pointer to
 * the vector, it may not be pointed to it anymore after being reserved.
 * Amortized Time Complexity- O(1), Worst Case Time Complexity- O(n).
 */
int VectorPushBack(d_vector_t *vec, const void *value);

/**
 * description: remove a value from the end of the vector.
 * input: d_vector_t vector - the vector that will be poped.
 * output: boolean int - if expansion fails return failure (non-zero),
 * otherwise push back value and return success (0).
 * Notes: undefined behavior if vector is empty.
 * undefined behaviour if the vector is NULL.
 * Time Complexity- O(1), Space Complexity- O(1)
 */
void VectorPopBack(d_vector_t *vec);

/**
 * description: returns a pointer to the element from the vector in the
 * specified index.
 * input: d_vector_t vector - the vector that contains the requested
 * element, size_t index- the index of that element.
 * output: void * - a pointer to the element in the specified index.
 * Notes: undefined behavior if index is out of range (index starts at 0).
 * undefined behaviour if the vector is NULL.
 * Time Complexity- O(1), Space Complexity- O(1)
 */
void *VectorGetElem(const d_vector_t *vec, size_t index);

/**
 * description: returning the current size of the vector.
 * input: const d_vector_t vec - vector of interest.
 * output: size_t that represents the current size of the vector_t.
 * time complexity: O(1), space complexity: O(1).
 * notes: undefined behaviour if the vector is NULL.
 */
size_t VectorSize(const d_vector_t *vec);

/**
 * description: returning the max capacity of the vector.
 * input: const d_vector_t vec - vector of interest.
 * output: size_t that represents the max capacity of the vector_t.
 * time complexity: O(1), space complexity: O(1).
 * notes: undefined behaviour if the vector is NULL.
 */
size_t VectorCapacity(const d_vector_t *vec);

/**
 * description: expanding the capacity of the vector by positive value as
 * requested by the user.
 * input: const d_vector_t vec - vector of interest,  size_t new_capacity-
 * the user requested size.
 * output: boolean int - if expansion fails return failure (non-zero),
 * otherwise return success (0).
 * time complexity: O(n), space complexity: O(n).
 * notes: undefined behaviour if new capacity is smaller than original capacity.
 * undefined behaviour if the vector is NULL. if the user have a previous
 * pointer to the vector, it may not be pointed to it anymore after the
 * function expansion.
 */
int VectorReserve(d_vector_t *vec, size_t new_capacity);

/**
 * description: reducing the capacity of the vector by growth factor.
 * input: const d_vector_t vec - vector of interest.
 * output: boolean int - if reduction fails return failure (non-zero)
 * otherwise return success (0).
 * time complexity: O(n), space complexity: O(n).
 * notes: be careful, elements may be lost during reduction if the reduced
 * capacity is smaller than the curret element size. capacity changes to
 * (capacity/growth factor) + 1. if the user have a previous pointer to
 * the vector, it may not be pointed to it anymore after expansion. undefined
 * behaviour if the vector is NULL.
 */
int VectorShrink(d_vector_t *vec);

#endif /* __ILRD_OL149_D_VECTOR_H__ */
