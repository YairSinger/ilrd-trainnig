/* ----------------------------------------------------------
 * Filename:    heap_pqueue.c
 * Author:      Shahar Molina
 * Reviewer:	Yael Hava
 * Date:        15.11.2023
 * Course:      OL-149
 * Description: Priority Queue Library
 * ----------------------------------------------------------
 */

/***********************************************
 * Priority Queue Library
 *
 * Description:
 * This header file defines an API for priority queues, a data structure
 * for managing elements based on their priority levels. A priority queue is
 * a dynamic data structure where elements are ordered by their priorities,
 * with higher-priority elements dequeued before lower-priority ones.
 * Users can create a priority queue with a custom comparison function to
 * determine the order of elements based on their priorities.
 * the priority queue stores references to the data elements.
 * Main operations: enqueue, dequeue, clear, erase.
 * Enqueuing is stable and can handle duplicates of data and priority.
 *
 * Note:
 * Proper usage of the library's functions is crucial. Users must provide a
 * valid comparison function to establish the order of elements. Care should
 * be taken when performing operations to ensure that the priority queue
 * remains well-organized and to avoid undefined behavior.
 ***********************************************/

#ifndef __ILRD_OL149_HEAP_PQ_H__
#define __ILRD_OL149_HEAP_PQ_H__

#include <stddef.h> /* size_t */

typedef struct pqueue pqueue_t;

/**
 * @brief Function reference for comparing and priorotizing elements in the
 priority queue.

 * @param target: data of the current element being compared.
 * @param source: A reference to the data that can be used by the function to
 * perform the comparison, sent by the user.
 *
 * @return An integer representing the comparison result:
 *         - Negative value if target is less than source.
 *         - Zero if target is equal to source.
 *         - Positive value if target is greater than source.
 * @complexity Time Complexity: O(1), Space Complexity: O(1)
 */
typedef int (*cmp_func_t)(const void *target, const void *source);

/**
 * @brief Function reference for matching elements in the priority queue.
 *
 * @param data:  A reference to the data of the current element being evaluated.
 * @param param: A parameter that can be used by the function to perform the
 *              matching, sent by the user.
 *
 * @return An integer value representing the result of the matching operation,
 * a non-zero value indicates a match, zero indicates no match.
 *
 * @complexity Time Complexity: O(1), Space Complexity: O(1)
 */
typedef int (*match_func_t)(const void *data, void *param);

/**
 * @brief Creates a new priority queue with the specified comparison function.
 *
 * @param cmp_func: A function reference that defines how elements in the
 * priority queue are compared and priorotized.
 *
 * @return A handle to the newly created priority queue or NULL on failure.
 *
 * @complexity Time Complexity: O(1), Space Complexity: O(1)
 */
pqueue_t *PQCreate(cmp_func_t cmp_func);

/**
 * @brief Destroys the specified priority queue and its associated resources.
 *
 * @param pq: A handle to the priority queue to be destroyed.
 *
 * @complexity Time Complexity: O(n), Space Complexity: O(1)
 */
void PQDestroy(pqueue_t *pq);

/**
 * @brief Enqueues (Inserts) an element into the priority queue.
 *
 * @param pq: A handle to the priority queue.
 * @param data: A reference to the data to be inserted into the priority queue.
 *
 * @return 0 if successful, non-zero if failed.
 *
 * @note If the comparison function returns zero, the new element will take a
 * position after an existing element, ensuring stable insertion.
 * @note Data that does not agree with cmp_func_t will result in an undefined
 * behavior.
 * @note Undefined behavior may occur if pq or data is NULL.
 *
 * @complexity Time Complexity: O(1), Space Complexity: O(1)
 */
int PQEnqueue(pqueue_t *pq, void *data);

/**
 * @brief Dequeues (removes) and returns the highest-priority element from the
 * priority queue.
 *
 * @param pq: A handle to the priority queue.
 *
 * @return A reference to the removed element.
 *
 * @note Undefined behavior may occur if the priority queue is empty.
 *
 * @complexity Time Complexity: O(1), Space Complexity: O(1)
 */
void *PQDequeue(pqueue_t *pq);

/**
 * @brief Returns a handle to the highest-priority element in the priority queue
 * without removing it.
 *
 * @param pq: A handle to the priority queue.
 *
 * @return A reference to the highest-priority element.
 *
 * @note Undefined behavior may occur if the priority queue is empty.
 *
 * @complexity Time Complexity: O(1), Space Complexity: O(1)
 */
void *PQPeek(const pqueue_t *pq);

/**
 * @brief Returns the size (number of elements) of the priority queue.
 *
 * @param pq: A handle to the priority queue.
 *
 * @return The number of elements in the priority queue.
 *
 * @complexity Time Complexity: O(n), Space Complexity: O(1)
 */
size_t PQSize(const pqueue_t *pq);

/**
 * @brief Checks if the priority queue is empty.
 *
 * @param pq: A handle to the priority queue.
 *
 * @return 1 if the priority queue is empty, 0 if it is not empty.
 *
 * @complexity Time Complexity: O(1), Space Complexity: O(1)
 */
int PQIsEmpty(const pqueue_t *pq);

/**
 * @brief Clears all elements from the priority queue.
 *
 * @param pq: A handle to the priority queue.
 *
 * @complexity Time Complexity: O(n), Space Complexity: O(1)
 */
void PQClear(pqueue_t *pq);

/**
 * @brief Searches for and removes an element from the priority queue based on a
 * matching function.
 *
 * @param pq: A handle to the priority queue.
 * @param match_func: A function reference that defines the matching criteria.
 * @param param: A parameter to be passed to the matching function by the user.
 *
 * @return A handle to the removed element if found, otherwise NULL.
 *
 * @complexity Time Complexity: O(n), Space Complexity: O(1)
 */
void *PQErase(pqueue_t *pq, match_func_t match_func, void *param);

#endif /* __ILRD_OL149_HEAP_PQ_H__ */
