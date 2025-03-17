/***********************************************************
* PROJECT: PRIORITY_QUEUE
* Group: OL 147-148 
* IP Version: 3.0.0  
* WRITER: Yair Singer
* REVIEWER:  Zayd Abu Sneineh
* STATUS: Pre-reviewed
* DATE: 24.8.23
***********************************************************/


#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include <stddef.h> /* size_t */

typedef struct pqueue pqueue_t;

/*
@Description: Creates Priority Queue.
@Parameters:  
            1. [priority_func] - user custom priority compare function. 
                                 results a positive number when rhs has higher priority,
                                 zero on equal priority,
                                 negative on lower priorty.
@Return value: Pointer to the priority queue, NULL on failure.
@Time Complexity: O(1).
@Notes: None.
*/
pqueue_t *PQCreate(int (*priority_func)(const void *lhs, const void *rhs));

/*
@Description: Cleans Priority Queue from memory.
@Parameters:  
            1. [queue] - pointer to Priority Queue.
@Return value: None.
@Time Complexity: O(n).
@Notes: [queue] must be valid.
*/
void PQDestroy(pqueue_t *queue);

/*
@Description:   Inserts data to the correct place in the list.
                The insertion is stable.
@Parameters:  
            1. [queue] - Pointer to the Priority Queue.
            1. [data]  - Pointer to data.
@Return value: 0 on success or 1 on failure.
@Time Complexity: O(n).
@Notes: [queue] should be a valid list.
*/
int PQEnqueue(pqueue_t *queue, const void *data);
 
/*
@Description: Removes highest priority element from queue.
@Parameters:  
			 1. [queue] - Pointer to the Priority Queue.
@Time Complexity: O(1).
@Notes: [queue] should be a valid list.
*/
void PQDequeue(pqueue_t *queue);

/*
@Description: Retrieves the highest priority element in queue.
@Parameters:  
            1. [queue] - pointer to Priority Queue.
@Return value: pointer to the first element's data.
@Time Complexity: O(1).
@Notes: Using PQPeek on an empty list will result in undefined behavior.
        [queue] must be valid.
*/
void *PQPeek(pqueue_t *queue);

/*
@Description: Returns whether [queue] is empty.
@Parameters:  
			 1. [queue] - Pointer to the queue.
@Return value: returns true if queue is empty or false otherwise.
@Time Complexity: O(1).
@Notes: [queue] should be valid.
*/
int PQIsEmpty(const pqueue_t *queue);

/*
@Description: Returns the number of elements that are currently in the queue.
@Parameters: 
            1. [queue] - Pointer to the PQueue. 
@Return Value: [queue] size.            
@Time Complexity: O(n).
@Notes: [queue] should be valid.
*/
size_t PQSize(const pqueue_t *queue);

/*
@Description: Clears queue's elements.
@Parameters:  
			 1. [queue] - Pointer to the queue.
@Return value: None.
@Time Complexity: O(n).
@Notes: [queue] should be valid.
*/
void PQClear(pqueue_t *queue);

/*
@Description: Erases the first element matching the function.
@Parameters:  
			 1. [queue]          - Pointer to the queue.
			 2. [is_match_func]  - Pointer to function that returns 1 on a match, or 0 otherwise.
			 3. [rhs]            - Pointer to user's input to be compared with match function.
@Return value: Data of popped node.
@Time Complexity: O(n).
@Notes: [queue] should be valid.
*/
void *PQErase(pqueue_t *queue, int (*is_match_func)(const void *lhs, const void *rhs), void *rhs);

#endif /* __PQUEUE_H__ */
