
/* ----------------------------------------------------------
 * Filename:    heap.h
 * Author:      Shahar Molina
 * Reviewer:	Yael Hava
 * Date:        15.11.2023
 * Course:      OL-149
 * Description: Library
 * ----------------------------------------------------------
 */
/***********************************************
 * Heap Library
 *
 * Description:
 * This header file defines an API for a heap data structure, a specialized
 * tree-based structure satisfying the heap property. The heap organizes
 * elements such that the parent node holds a value greater than or equal to
 * its children (for a max heap) or less than or equal to its children (for a
 * min heap). This API provides functions for heap creation, insertion,
 * removal, retrieval of the root element, emptiness check, and size
 * determination. Users can manage heap-based data efficiently using this
 * interface, as the complexity of Push, Pop and Remove are as follow:
 * Time: O(log n) - average, O(n) - worst, Space: O(1), while Peek is O(1) for
 * both time and space complexity.
 *
 * Note:
 * Proper usage of this library requires a valid comparison function to define
 * the order of elements within the heap. Care should be taken to ensure
 * validity of operations to avoid erroneous or undefined behavior, especially
 * when dealing with empty or invalid heap instances.
 ***********************************************/

#ifndef __ILRD_OL149_H_HEAP__
#define __ILRD_OL149_H_HEAP__

#include <stddef.h>

typedef struct heap heap_t;

typedef int(*heap_cmp_func_t)(const void *data, const void *base_data);

typedef int(* heap_match_func_t)(void *data, const void *base_data);

/**
 * @brief Creates a new heap.
 *
 * @param cmp_func: A comparison function used for ordering elements in the heap.
 *
 * @return A reference to the newly created heap or NULL on failure.
 *
 * @complexity Time: O(1), Space: O(1)
 */
heap_t *HeapCreate(heap_cmp_func_t cmp_func);

/**
 * @brief Destroys a heap.
 *
 * @param heap: Reference to the heap to be destroyed.
 *
 * @complexity Time: O(1), Space: O(1)
 */
void HeapDestroy(heap_t *heap);

/**
 * @brief Inserts an element into the heap.
 *
 * @param heap: Reference to the heap.
 * @param element: Reference to the element to be inserted.
 *
 * @return 0 on success, -1 on failure.
 *
 * @complexity Time: O(log n) - average, O(n) - worst, Space: O(1)
 */
int HeapPush(heap_t *heap, void *element);

/**
 * @brief Removes the first element from the heap.
 *
 * @param heap: Reference to the heap.
 *
 * @complexity Time: O(log n) - average, O(n) - worst, Space: O(1)
 */
void HeapPop(heap_t *heap);

/**
 * @brief Retrieves the first element without removing it from the heap.
 *
 * @param heap: Reference to the heap.
 *
 * @return A reference to the root element or NULL if the heap is empty.
 *
 * @complexity Time: O(1), Space: O(1)
 */
void *HeapPeek(const heap_t *heap);

/**
 * @brief Removes the first element that matches the provided criteria.
 *
 * @param heap: Reference to the heap.
 * @param match_func: A matching function for finding the element to remove.
 * @param base_data: Data used as a criteria for element removal.
 *
 * @return A reference to the removed element or NULL if not found or empty.
 *
 * @complexity Time: O(log n) - average, O(n) - worst, Space: O(1)
 */
void *HeapRemove(heap_t *heap, heap_match_func_t match_func, const void *base_data);

/**
 * @brief Checks if the heap is empty.
 *
 * @param heap: Reference to the heap.
 *
 * @return 1 if empty, 0 if not empty.
 *
 * @complexity Time: O(1), Space: O(1)
 */
int HeapIsEmpty(heap_t *heap);

/**
 * @brief Retrieves the number of elements in the heap.
 *
 * @param heap: Reference to the heap.
 *
 * @return The number of elements in the heap.
 *
 * @complexity Time: O(1), Space: O(1)
 */
size_t HeapSize(heap_t *heap);

#endif /* __ILRD_OL149_H_HEAP__ */
