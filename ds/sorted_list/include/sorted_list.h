/***********************************************************
* PROJECT: SORTED_LIST 
* Group: OL 147-148 
* IP Version: 2.1.0  
* WRITER: Yair Singer
* REVIEWER: Shai Labbel 
* STATUS: Approved
* DATE: 20.8.23
***********************************************************/



#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include <stddef.h> /* size_t */

#include "dll.h"


typedef struct sorted_list sorted_list_t;

typedef struct sorted_list_iter
{
    dll_iter_t iter;
    
    #ifndef NDEBUG
    sorted_list_t *srt_list;
    #endif
} sorted_list_iter_t;



/*
@Description: Dynamically allocates a sorted linked list.
@Parameters:  
            1. [cmp_func] - the function used to insert the elements sorted.
@Return value: Pointer to the sorted linked list, NULL on failure.
@Time Complexity: O(1).
@Notes: None.
*/
sorted_list_t *SortedListCreate(int (*cmp_func)(const void *list_data, const void *user_data));

/*
@Description: Dynamically deallocates a sorted linked list.
@Parameters:  
            1. [sorted_list] - Pointer to the sorted list.
@Return value: None.
@Time Complexity: O(n).
@Notes: [sorted_list] should be a valid list.
*/
void SortedListDestroy(sorted_list_t *sorted_list);


/*
@Description: Inserts data to the right place in the list.
@Parameters:  
            1. [sorted_list] - Pointer to the sorted list.
            1. [data] - Pointer to data.
@Return value: Iterator to the new node or SortedListEnd(sorted_list) on failure.
@Time Complexity: O(n).
@Notes: [sorted_list] should be a valid list.
*/
sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, const void *data);


/*
@Description: Removes the [who] node.
@Parameters:  
			 1. [who] - Iterator to the node to remove.
@Return value: SortedListNext(who).
@Time Complexity: O(1).
@Notes: [who] should be a valid iterator.
        invalidates [who].
*/
sorted_list_iter_t SortedListRemove(sorted_list_iter_t who);

/*
@Description: Pops the first element.
@Parameters:  
			 1. [sorted_list] - Pointer to the sorted list.
@Return value: Pointer to data of popped element.
@Time Complexity: O(1).
@Notes: [sorted_list] should be valid.
*/
void *SortedListPopFront(sorted_list_t *sorted_list);

/*
@Description: Pops the last element.
@Parameters:  
			 1. [sorted_list] - Pointer to the sorted list.
@Return value: Pointer to data of popped element.
@Time Complexity: O(1).
@Notes: [sorted_list] should be valid.
*/
void *SortedListPopBack(sorted_list_t *sorted_list);

/*
@Description: Return the size of the list.
@Parameters:  
			 1. [sorted_list] - Pointer to the sorted list.
@Return value: [sorted_list] size.
@Time Complexity: O(n).
@Notes: [sorted_list] should be valid.
*/
size_t SortedListSize(const sorted_list_t *sorted_list);

/*
@Description: Gets a node data.
@Parameters:  
			 1. [iter] - Iterator to node with the data.
@Return value: the data by reference.
@Time Complexity: O(1).
@Notes: [iter] should be a valid iterator.
*/
void *SortedListGetData(const sorted_list_iter_t iter);

/*
@Description: Gets iterator for the first valid element in the list.
@Parameters:  
			 1. [sorted_list] - Pointer to the doubly linked list.
@Return value: returns first valid node, SortedListEnd(sorted_list) if empty.
@Time Complexity: O(1).
@Notes: [sorted_list] should be valid.
*/
sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list);

/*
@Description: Gets iterator for an invalid element after the last.
@Parameters:  
			 1. [sorted_list] - Pointer to the doubly linked list.
@Return value: returns an iterator of invalid node at the end.
@Time Complexity: O(1).
@Notes: [sorted_list] should be valid.
*/
sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list);


/*
@Description: Gets iterator for the previous node of an iterator.
@Parameters:  
			 1. [iter] - Iterator to the get it's previous.
@Return value: returns previous node iterator.
@Time Complexity: O(1).
@Notes: [iter] should be a valid iterator.
        SortedListPrev(SortedListBegin(sorted_list)) returns an invalid iterator,
        just like SortedListEnd().
        undefined behaviour at SortedListPrev(SortedListPrev(SortedListBegin(sorted_list))).
*/
sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter);

/*
@Description: Gets iterator for the next node of an iterator.
@Parameters:  
			 1. [iter] - Iter to the get it's next.
@Return value: returns next node iterator.
@Time Complexity: O(1).
@Notes: [iter] should be a valid iterator.
        undefined behaviour at SortedListNext(SortedListEnd(sorted_list)).
*/
sorted_list_iter_t SortedListNext(sorted_list_iter_t iter);

/*
@Description: Compares two iterators.
@Parameters:  
			 1. [iter1] - Iterator.
			 2. [iter2] - Iterator.
@Return value: true or false.
@Time Complexity: O(1).
@Notes: [iter1]/[iter2] should be valid iterators.
*/
int SortedListIsSameIter(sorted_list_iter_t iter1, sorted_list_iter_t iter2);

/*
@Description: Returns whether [sorted_list] is empty.
@Parameters:  
			 1. [sorted_list] - Pointer to the sorted list.
@Return value: returns true or false.
@Time Complexity: O(1).
@Notes: [sorted_list] should be valid.
*/
int SortedListIsEmpty(const sorted_list_t *sorted_list);

/*
@Description: Finds the first node that matches param.
@Parameters: 
            1. [from]       - Iterator to the first node to search from (inclusive).
            2. [to]         - Iterator to the last node to search to (exclusive).
            4. [param]      - Pointer of parameters.
@Return value: Found Iter or [to] param or first irrelevant iterator to search.
               in debug mode - when [to] and [from] aren't from the same list, 
               return SortedListPrev(from);
@Time Complexity: O(n).
@Notes: [from] should be valid iterator before [to] and from the same list as [to].
        [to] should be valid iterator.
*/
sorted_list_iter_t SortedListFind(const sorted_list_t *sorted_list, sorted_list_iter_t from, sorted_list_iter_t to, const void *param);
/*
@Description: Finds the first node that the find function finds as a match.
@Parameters: 
            1. [from]           - Iterator to the first node to search from (inclusive).
            2. [to]             - Iterator to the last node to search to (exclusive).
            3. [is_match_func]  - Pointer to function that returns 1 on a match, or 0 otherwise.
            4. [param]          - Pointer of parameters for find function.
@Return value: Iterator matching the find function result, or [to] if no matching node was found.
               in debug mode - when [to] and [from] aren't from the same list, 
               return SortedListPrev(from);
@Time Complexity: O(n).
@Notes: [from] should be valid iterator before [to] and from the same list as [to].
        [to] should be valid iterator.
        [is_match] should be valid.
*/
sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to, int (*is_match_func)(const void *data, const void *param), const void *param);

/*
@Description: Transfers elements from one list to another.
@Parameters:d   
            1. [dest]  - Pointer to the destination list.
            2. [src]   - Pointer to the source list.
@Return value: None.
@Time Complexity: O(n+m).
@Notes: [src] and [dest] should be valid.
        [src] and [dest] must follow the same cmp_func.
*/
void SortedListMerge(sorted_list_t *dest, sorted_list_t *src);

/*
@Description: Iterates over the list and calls a function on each node data.
@Parameters: 
            1. [from]        - Iterator to the first node to iterate from (inclusive).
            2. [to]          - Iterator to the last node to iterate to (exclusive).
            3. [action_func] - Pointer to function that modify the data and returns 0 on sucess,
                               or any other value otherwise.
            4. [param]       - Pointer of parameters for action function.
@Return value: [action] status, 0 or the first non-zero value received from action function.
               in debug mode - when [to] and [from] aren't from the same list, returns -1.
@Time Complexity: O(n).
@Notes: [from] should be valid iterator before [to] and from the same list as [to].
        [to] should be valid iterator.
        [action] should be valid.
*/
int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, int (*action_func)(void *data, void *param), void *param);

#endif /* __SORTED_LIST_H__ */


