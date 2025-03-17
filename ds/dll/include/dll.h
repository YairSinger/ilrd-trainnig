
/**************************
* Group: OL 147-148 	  *
* Project: DLL  		  *
* Version: 2.0.0   		  *
* Student: Yair singer    *
* Reviewer: Amit Senouf	  *
* Status: pre-reviewed 	  *
*						  *
* Date: 	13.8.23       *
**************************/



#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h>
#include <assert.h>

typedef struct dll dll_t;
typedef struct node *dll_iter_t;

typedef int (*is_match_func)(const void *data, const void *param);
typedef int (*action_func)(void *data, void *param);

/*
@Description: Dynamically allocates a doubly linked list.
@Parameters:  None.
@Return value: Pointer to the doubly linked list, NULL on failure.
@Time Complexity: O(1).
@Notes: None.
*/
dll_t *DllCreate(void);

/*
@Description: Dynamically deallocates a doubly linked list.
@Parameters: Pointer to the doubly linked list.
@Return value: None.
@Time Complexity: O(n).
@Notes: [dll] should be valid.
*/
void DllDestroy(dll_t *dll);

/*
@Description: Inserts new node before [where].
@Parameters:  
			 1. [dll]   - Pointer to the doubly linked list.
			 2. [where] - Iterator to the node to be inserted before.
			 3. [data]  - Data to set in where.
@Return value: Iterator to the new node or DllEnd(dll) on failure.
@Time Complexity: O(1).
@Notes: [dll] should be valid.
        [where] should be a valid iterator.
*/
dll_iter_t DllInsert(dll_t *dll, dll_iter_t where, const void *data);

/*
@Description: Removes the [who] node.
@Parameters:  
			 1. [who] - Iterator to the node to remove.
@Return value: DllNext(who).
@Time Complexity: O(1).
@Notes: [who] should be a valid iterator.
        invalidates [who].
*/
dll_iter_t DllRemove(dll_iter_t who);

/*
@Description: Return the size of the list.
@Parameters:  
			 1. [dll] - Pointer to the doubly linked list.
@Return value: dll size.
@Time Complexity: O(n).
@Notes: [dll] should be valid.
*/
size_t DllSize(const dll_t *dll);

/*
@Description: Gets a node data.
@Parameters:  
			 1. [iter] - Iterator to node with the data.
@Return value: the data by reference.
@Time Complexity: O(1).
@Notes: [iter] should be a valid iterator.
*/
void *DllGetData(const dll_iter_t iter);

/*
@Description: Sets a node data.
@Parameters:  
			 1. [iter] - Iterator to the node to be set with data.
			 2. [data] - Data to set in [iter].
@Return value: None.
@Time Complexity: O(1).
@Notes: [iter] should be a valid iterator.
*/
void DllSetData(dll_iter_t iter, const void *data);

/*
@Description: Gets iterator for the first valid element in the list.
@Parameters:  
			 1. [dll] - Pointer to the doubly linked list.
@Return value: returns first valid node, DllEnd(dll) if empty.
@Time Complexity: O(1).
@Notes: [dll] should be valid.
*/
dll_iter_t DllBegin(const dll_t *dll);

/*
@Description: Gets iterator for an invalid element after the last.
@Parameters:  
			 1. [dll] - Pointer to the doubly linked list.
@Return value: returns an iterator of invalid node at the end.
@Time Complexity: O(1).
@Notes: [dll] should be valid.
*/
dll_iter_t DllEnd(const dll_t *dll);

/*
@Description: Gets iterator for the previous node of an iterator.
@Parameters:  
			 1. [iter] - Iterator to the get it's previous.
@Return value: returns previous node iterator.
@Time Complexity: O(1).
@Notes: [iter] should be a valid iterator.
        DllPrev(DllBegin(dll)) returns an invalid iterator, just like DllEnd().
        undefined behaviour at DllPrev(DllPrev(DllBegin(dll))).
*/
dll_iter_t DllPrev(dll_iter_t iter);

/*
@Description: Gets iterator for the next node of an iterator.
@Parameters:  
			 1. [iter] - Iter to the get it's next.
@Return value: returns next node iterator.
@Time Complexity: O(1).
@Notes: [iter] should be a valid iterator.
        undefined behaviour at DllNext(DllEnd(dll)).
*/
dll_iter_t DllNext(dll_iter_t iter);

/*
@Description: Compares two iterators.
@Parameters:  
			 1. [iter1] - Iterator.
			 2. [iter2] - Iterator.
@Return value: true or false.
@Time Complexity: O(1).
@Notes: [iter1]/[iter2] should be valid iterators.
*/
int DllIsSameIter(const dll_iter_t iter1, const dll_iter_t iter2);

/*
@Description: Returns whether dll is empty.
@Parameters:  
			 1. [dll] - Pointer to the doubly linked list.
@Return value: returns true or false.
@Time Complexity: O(1).
@Notes: [dll] should be valid.
*/
int DllIsEmpty(const dll_t *dll);

/*
@Description: Inserts new node at the end.
@Parameters:  
			 1. [dll]   - Pointer to the doubly linked list.
			 2. [data]  - Data to set in node.
@Return value: Iterator to the new node or DllEnd(dll) on failure.
@Time Complexity: O(1).
@Notes: [dll] should be valid.
*/


dll_iter_t DllPushBack(dll_t *dll, const void *data);

/*
@Description: Inserts new node at the start.
@Parameters:  
			 1. [dll]   - Pointer to the doubly linked list.
			 2. [data]  - Data to set in node.
@Return value: Iterator to the new node or DllEnd(dll) on failure.
@Time Complexity: O(1).
@Notes: [dll] should be valid.
*/
dll_iter_t DllPushFront(dll_t *dll, const void *data);

/*
@Description: Pops the last element.
@Parameters:  
			 1. [dll] - Pointer to the doubly linked list.
@Return value: None.
@Time Complexity: O(1).
@Notes: [dll] should be valid.
*/
void *DllPopBack(const dll_t *dll);

/*
@Description: Pops the first element.
@Parameters:  
			 1. [dll] - Pointer to the doubly linked list.
@Return value: None.
@Time Complexity: O(1).
@Notes: [dll] should be valid.
*/
void *DllPopFront(const dll_t *dll);

/*
@Description: Finds the all nodes matching the [is_match] and inserts them to [out_dll].
@Parameters: 
            1. [from]       - Iterator to the first node to search from (inclusive).
            2. [to]         - Iterator to the last node to search to (exclusive).
            3. [is_match]   - Pointer to function that returns 1 on a match, or 0 otherwise.
            4. [param]      - Pointer of parameters for find function.
            5. [out_dll]    - Pointer to the list which contains all found nodes.
@Return value: status of inserting a node to [out_dll].
@Time Complexity: O(n).
@Notes: [from] should be valid iterator before [to] and from the same list as [to].
        [to] should be valid iterator.
        [out_dll] should be valid.
        [is_match] should be valid.
        
*/
int DllMultiFind(const dll_iter_t from, const dll_iter_t to , const is_match_func is_match, const void *param, dll_t *out_dll);

/*
@Description: Finds the first node that the find function finds as a match.
@Parameters: 
            1. [from]       - Iterator to the first node to search from (inclusive).
            2. [to]         - Iterator to the last node to search to (exclusive).
            3. [is_match]   - Pointer to function that returns 1 on a match, or 0 otherwise.
            4. [param]      - Pointer of parameters for find function.
@Return value: Iterator matching the find function result, or [to] if no matching node was found.
@Time Complexity: O(n).
@Notes: [from] should be valid iterator before [to] and from the same list as [to].
        [to] should be valid iterator.
        [is_match] should be valid.
*/
dll_iter_t DllFind(const dll_iter_t from, const dll_iter_t to, const is_match_func is_match, const void *param);

/*
@Description: Transfers elements from one list to another before [where].
@Parameters:d   
            1. [where]  - Iterator to the nodes to be inserted before.
            2. [from]   - Iterator to the first node to move from (inclusive).
            3. [to]     - Iterator to the last node to move (exclusive).
@Return value: None.
@Time Complexity: O(1).
@Notes: [from] should be valid iterator before [to] and from the same list as [to].
        [to] should be valid iterator.
        [where] should be on a different list or not inbetween [from] and [to]
*/
void DllSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to);

/*
@Description: Iterates over the list and calls a function on each node data.
@Parameters: 
            1. [from]   - Iterator to the first node to search from (inclusive).
            2. [to]     - Iterator to the last node to search to (exclusive).
            3. [action]     - Pointer to function that modify the data and returns 0 on sucess,
                          or any other value otherwise.
            4. [param]  - Pointer of parameters for action function.
@Return value: [action] status, 0 or the first non-zero.
@Time Complexity: O(n).
@Notes: [from] should be valid iterator before [to] and from the same list as [to].
        [to] should be valid iterator.
        [action] should be valid.
*/
int DllForEach(dll_iter_t from, const dll_iter_t to, const action_func action, const void *param);

#endif /* __DLL_H__ */
