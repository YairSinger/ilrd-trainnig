
/***********************************************************
* PROJECT: Single linked list
* Group: OL 147-148      
* API Version:  1.4.2
* API Date 2.8.2023   
* WRITER: Yair Singer
* REVIEWER: Maor Levi
* STATUS: Approved
* DATE: 5/8/23
***********************************************************/
#ifndef __SLL_H__
#define __SLL_H__

#include <stddef.h>

typedef struct sll sll_t;
typedef struct node *sll_iter_t;

typedef int (*match_func)(const void *lhs, void *rhs);
typedef int (*action_func)(void *data, void *param);

/*
@Description: Dynamically allocates a singly linked list.
@Parameters:  None.
@Return value: Pointer to the singly linked list, NULL on failure.
@Time Complexity: O(1).
@Undefined Behavior: None.
*/
sll_t *SllCreate(void);


/*
@Description: Frees allocated singly linked list (and all the related nodes).
@Parameters:  sll - Pointer to the singly linked list.
@Return value: None.
@Time Complexity: O(n).                           
@Undefined Behavior: sll is NULL.
*/
void SllDestroy(sll_t *sll);

int SllIsEmpty(sll_t *sll);


/*
@Description: Creates a new node and insert it before the given iterator.
@Parameters: 
    sll     - Pointer to the singly linked list.
    where   - The iterator to place the new node before.
    data    - The data attached to that node.
@Return value: Iterator of the new inserted node, or SllEnd incase of failure.
@Time Complexity: O(1).
@Undefined Behavior: sll is NULL, where is NULL, data is NULL.
*/
sll_iter_t SllInsert(sll_t *sll, sll_iter_t where, const void *data);


/*
@Description: Remove an existing node from the list
@Parameters: who - The iterator of the node to be removed.
@Return value: The next node from the removed one.
@Time Complexity: O(1).
@Undefined Behavior: who is NULL or END.
*/
sll_iter_t SllRemove(sll_t *sll, sll_iter_t who);


/*
@Description: Count number of nodes in a singly linked list.
@Parameters:  sll_ptr - Pointer to singly linked list.
@Return value: Number of nodes in list.
@Time Complexity: O(n).
@Undefined Behavior:  sll_t pointer is NULL.
*/
size_t SllCount(const sll_t *sll);


/*
@Description: Returns the data  within iter node.
@Parameters: iter - Points on desired node to access.
@Return value: Memory address of data.
@Time Complexity: O(1).
@Undefined Behavior: iter is NULL.
*/
void *SllGetData(sll_iter_t iter);


/*
@Description: Sets node's data.
@Parameters: iter - Points to the node to be set.
             data - Data to set, by reference
@Time Complexity: O(1).
@Undefined Behavior: iter is NULL , iter is END.
*/
void SllSetData(sll_iter_t iter, void *data);


/*
@Description: Returns an iterator pointing to the first element of the list.
@Parameters: sll - Pointer to the singly likend list.
@Return value: Iterator pointing to the first element of the list.
@Time Complexity: O(1).
@Undefined Behavior: sll_t pointer NULL.
*/
sll_iter_t SllBegin(const sll_t *sll);


/*
@Description: Returns an iterator pointing to the next element in the list.
@Parameters: iter - points on desired node to access.
@Return value: Iterator pointing to the next element from the given iterator.
@Time Complexity: O(1).
@Undefined Behavior: iter is NULL.
*/
sll_iter_t SllNext(sll_iter_t iter);


/*
@Description: Returns an iterator pointing to the end of the list.
@Parameters: sll - Pointer to the singly likend list.
@Return value: Iterator pointing to the end of the list.
@Time Complexity: O(1).
@Undefined Behavior: sll is NULL.
*/
sll_iter_t SllEnd(const sll_t *sll);


/*
@Description: Checks if two iterators are the same.
@Parameters: 
    iter1 - points on desired node to access.
    iter2 - points on desired node to access.
@Return value: 1 if both TRUE, 0 if FALSE.
@Time Complexity: O(1).
@Undefined Behavior: none.
*/
int SllIsSameIter(const sll_iter_t iter1, const sll_iter_t iter2);


/*
@Description: Finds the first node that the find function finds as a match.
@Parameters: 
    from        - Pointer to the first node to search from (inclusive).
    to          - Pointer to the last node to search to (exclusivly).
    match_func  - Pointer to function that returns 1 on a match, or 0 otherwise.
    rhs         - Pointer of parameters for find functions.
    lhs         - 
@Return value: Iterator matching the find function result, or to to if no matching node was found.
@Time Complexity: O(n).
@Undefined Behavior: from is NULL, to is NULL, match_func is NULL.
*/
sll_iter_t SllFind(sll_iter_t from, sll_iter_t to , int (*match_func)(const void *lhs, const void *rhs), const void *rhs);


/*
@Description: Iterates over the list and calls a function on each node data.
    sll         - Pointer to the singly likend list.
    action_func - Pointer to function that modify the data and returns 0 on sucess or any other value otherwise.
    param       - Pointer of parameters for action functions.
    data        -
@Return value: 0 on sucess or a non zero value in failure.
@Time Complexity: O(n).
@Undefined Behavior: sll is NULL, action_func is NULL.
*/
int SllForEach(const sll_t *sll, int (*action_func)(void *data, void *param), void *param);
/*
@Description:   Appends src's nodes to the end of dest's nodes.
                After append src is empty valid list.
	dest		- Pointer to the destination sll.
	src			- Pointer to the source sll.
@Return value: None.
@Time Complexity: O(1).
@Undefined Behavior: dest is NULL, src is NULL.
*/
void SllAppend(sll_t *dest, sll_t *src); 
int HasLoop (const sll_iter_t head);
void PrependList(sll_t *sll,sll_iter_t prepend_to);
size_t SllCountFromIter(sll_iter_t from,sll_iter_t *end_location);
sll_iter_t FindIntersection(sll_iter_t head1,sll_iter_t head2);
sll_iter_t SllFlip(sll_iter_t head);



#endif /* __SLL_H__ */
