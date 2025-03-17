#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /* size_t */

typedef struct heap heap_t;




/*
@Name: HeapCreate
@Description: 
    Initializes and returns a new heap based on the provided priority comparison function. 
@Parameters: 
    - priority_cmp: A function pointer that determines the priority of the data in the heap.
      Returns a positive value if the first argument has higher priority, 0 if equal,
      and negative if the second argument has higher priority.
      
@Return: 
    - Returns a valid pointer to the newly created heap or NULL if allocation fails.

@Time Complexity: 
    O(1)

@Space Complexity: 
    O(1).
*/
heap_t *HeapCreate(int (*priority_cmp)(const void*, const void*));


/*
@Name: HeapDestroy
@Description: 
    - Deletes and frees all the resources associated with the Heap data structure. 
@Parameters: 
    - heap: A valid pointer to the heap to be destroyed.
    
@Return: 
    Void

@Time Complexity: 
    O(1)

@Space Complexity: 
    O(1).
 */
void HeapDestroy(heap_t *heap);


/*
@Name: HeapPush
@Description: 
    - Inserts a new element into the Heap data structure based on its priority.
@Parameters: 
    - heap: A valid pointer to the heap.
    - data: The data to be inserted into the heap.

@Return: 
    - Returns 0 on success or a non-zero value on error.

@Time Complexity: 
    O(log n)

@Space Complexity: 
    O(1).
 */
int HeapPush(heap_t *heap, const void *data);


/*
@Name: HeapPop
@Description: 
    - Removes the top-priority element from the Heap.
@Parameters: 
    - heap: A valid pointer to the heap.

@Return: 
    Void

@Time Complexity: 
    O(log n)

@Space Complexity: 
    O(1).
 */
void HeapPop(heap_t *heap);


/*
@Name: HeapPeek
@Description: 
    - Provides a pointer to the top-priority element without removing it from the heap.
@Parameters: 
    - heap: A pointer to the heap.

@Return: 
    - Returns a valid pointer to the top-priority element or NULL if the heap is empty.

@Time Complexity: 
    O(1)

@Space Complexity: 
    O(1).
 */
void *HeapPeek(const heap_t *heap);


/*
@Name: HeapGetSize
@Description: 
    - Gets the number of elements in the heap.
@Parameters: 
    - heap: A valid pointer to the heap.

@Return: 
    - Returns the number of elements in the heap.

@Time Complexity: 
    O(1)

@Space Complexity: 
    O(1).
 */
size_t HeapGetSize(const heap_t *heap);


/*
@Name: HeapIsEmpty
@Description: 
    - Checks if the heap is empty.
@Parameters: 
    - heap: A valid pointer to the heap.

@Return: 
    - Returns 1 (true) if the heap is empty, 0 (false) otherwise.

@Time Complexity: 
    O(1)

@Space Complexity: 
    O(1).
 */
int HeapIsEmpty(const heap_t *heap);


/*
@Name: HeapRemove
@Description: 
    - Removes an element from the heap that matches the given criteria.
@Parameters: 
    - heap: A valid pointer to the heap.
    - param: A pointer to the parameter that's used to identify the item to remove.
    - heap_is_match: A valid function pointer that checks for matching criteria. 
      Returns non-zero if the criteria is met, and 0 otherwise.
    
@Return: 
    - Returns a pointer to the removed item or NULL if the item wasn't found.

@Time Complexity: 
    O(log n)

@Space Complexity: 
    O(1).
 */
void *HeapRemove(heap_t *heap, const void *param, int(*heap_is_match)(const void *data, const void *param));

#endif /*__HEAP_H__*/


