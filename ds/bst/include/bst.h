/***********************************************************
*PROJECT: Binary Search Tree BST
*
*WRITER: Yair Singer
*
*REVIEWER: Zayd Abu Sneineh
*
*STATUS: Approved
*
*DATE: 15/09/2023
***********************************************************/
#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct bst bst_t;
typedef struct bst_node bst_node_t;
typedef bst_node_t *bst_iter_t;

/******************************************************************************/
/*
@Name: BSTCreate
@Description: Creates a new binary search tree.
@Parameters: 
             1. cmp_func - A user-defined comparison function that dictates the ordering of nodes within the tree.

@Return Value: A pointer to the newly created binary search tree (bst_t*).

@Time Complexity: O(1) 

@Space Complexity: O(1)
*/
bst_t *BSTCreate(int (*cmp_func)(const void *lhs, const void *rhs));


/*
@Name: BSTDestroy
@Description: Destroys a binary search tree, freeing up all the resources that were allocated for it. 
@Parameters: 
             1. tree - A valid pointer to a binary search tree that is to be destroyed. 

@Return Value: Void.

@Time Complexity: 
                    - Best Case: O(n), where n is the number of nodes in the tree.
                    - Average Case: O(n), where n is the number of nodes in the tree.
                    - Worst Case: O(n), where n is the number of nodes in the tree.

@Space Complexity: O(1).
*/
void BSTDestroy(bst_t *tree);


/******************************************************************************/
/*
@Name: BSTInsert
@Description: Inserts a new node with the given data into the binary search tree. 
              If data identical to the given data already exists within the tree, the behavior is undefined.
@Parameters: 
             1. tree - A pointer to the binary search tree where the data will be inserted.
             2. data - A pointer to the data to be inserted into the tree.

@Return Value: An iterator to the inserted node.
               NULL if the allocation fails.

@Time Complexity: 
                    - Best Case: O(1)
                    - Average Case: O(log(n))
                    - Worst Case: O(n)

@Space Complexity: O(1)
*/
bst_iter_t BSTInsert(bst_t *tree, const void *data);


/******************************************************************************/
/*
@Name: BSTRemove
@Description: Removes the node pointed to by the given iterator from the binary search tree.
@Parameters: 
             1. iter - An iterator pointing to the node to be removed.

@Return Value: Void.

@Time Complexity: 
                    - Best Case: O(1)
                    - Average Case: O(log(n))
                    - Worst Case: O(n)

@Space Complexity: O(1)
*/
void BSTRemove(bst_iter_t iter);

/******************************************************************************/
/*
@Name: BSTGetSize
@Description: Retrieves the number of nodes currently present in the binary search tree.
@Parameters: 
             1. tree - A pointer to the valid binary search tree.

@Return Value: The number of nodes present in the tree.

@Time Complexity: O(n).

@Space Complexity: O(1).
*/
size_t BSTGetSize(const bst_t *tree);


/******************************************************************************/
/*
@Name: BSTNext
@Description: Returns an iterator pointing to the element following the element pointed to by the given iterator in the binary search tree. 
              If the iterator points to the last element (largest) in the tree, the behavior is undefined.

@Parameters: 
             1. iter - An iterator pointing to an element within the binary search tree.

@Return Value: Returns an iterator pointing to the next element in the binary search tree. 
               If the iterator pointed to the last element in the tree, the behavior is undefined.

@Time Complexity: 
                  Best: O(1) - If the node has a right child, it is a constant time operation to find the leftmost child of the right subtree.
                  Average: O(log(n)) - On average, the function would take logarithmic time in the number of nodes present in the tree.
                  Worst: O(n) - In the worst case, it may have to traverse to the rightmost node which can take linear time in case of a skewed tree.

@Space Complexity: O(1).
*/
bst_iter_t BSTNext(bst_iter_t iter);


/******************************************************************************/
/*
@Name: BSTPrev
@Description: Returns an iterator pointing to the element preceding the element pointed to by the given iterator in the binary search tree. 
              If the iterator points to the first element (smallest) in the tree, the behavior is undefined.

@Parameters: 
             1. iter - An iterator pointing to an element within the binary search tree.

@Return Value: Returns an iterator pointing to the previous element in the binary search tree. 
               If the iterator pointed to the first element in the tree, the behavior is undefined.

@Time Complexity: 
                  Best: O(1) - If the node has a left child, it is a constant time operation to find the rightmost child of the left subtree.
                  Average: O(log(n)) - On average, the function would take logarithmic time in the number of nodes present in the tree.
                  Worst: O(n) - In the worst case, it may have to traverse to the leftmost node which can take linear time in case of a skewed tree.

@Space Complexity: O(1).
*/
bst_iter_t BSTPrev(bst_iter_t iter);



/******************************************************************************/
/*
@Name: BSTGetData
@Description: This function retrieves the data stored at the node pointed to by the specified iterator within a binary search tree. 

@Parameters: 
             1. iter - An iterator pointing to the node in the binary search tree whose data needs to be retrieved.

@Return Value: Returns a pointer to the data stored at the node pointed to by the iterator. If the iterator points to an end node or invalid node, 
               the behavior is undefined.

@Time Complexity: 
                  Best: O(1) - Retrieving data from a node using an iterator is a constant time operation, as it involves direct memory access.
                  Average: O(1) - Same as the best case, as the operation doesn't depend on the number of nodes in the tree.
                  Worst: O(1) - Same as the best case.

@Space Complexity: O(1).
*/
void *BSTGetData(bst_iter_t iter);


/******************************************************************************/
/*
@Name: BSTBegin
@Description: Returns an iterator pointing to the first (smallest) element in the binary search tree.
@Parameters: 
             1. tree - A pointer to the valid binary search tree whose first element is to be accessed.

@Return Value: Returns an iterator to the first (smallest) element in the tree. 
               If the tree is empty, the return value will be equal to BSTEnd(tree).

@Time Complexity: 
                    - Average Case: O(log(n))
                    - Worst Case: O(n) where n is the number of nodes in the tree.
                      The worst case occurs when the tree degenerates into a linked list, requiring a traversal down the 
                      entire height of the tree to find the smallest element.

@Space Complexity: O(1)
*/
bst_iter_t BSTBegin(const bst_t *tree);


/******************************************************************************/
/*
@Name: BSTEnd
@Description: Get the right-most node in the tree.
              
@Parameters: 
             1. tree - A pointer to the valid binary search tree.

@Return Value: An iterator to the right-most tree node.

@Time Complexity: O(1).

@Space Complexity: O(1).
*/
bst_iter_t BSTEnd(const bst_t *tree);


/******************************************************************************/
/*
@Name: BSTIsEmpty
@Description: Checks whether the binary search tree is empty (i.e., contains no nodes).
@Parameters: 
             1. tree - A pointer to the valid binary search tree to be checked.

@Return Value: Returns an integer where:
                    - 1 indicates that the tree is empty.
                    - 0 indicates that the tree contains at least one node.

@Time Complexity: O(1)

@Space Complexity: O(1)
*/
int BSTIsEmpty(const bst_t *tree);


/******************************************************************************/
/*
@Name: BSTFind
@Description: This function searches the binary search tree to find a node that contains the specified key.

@Parameters: 
             1. tree - A pointer to a valid binary search tree where the search is to be conducted.
             2. key - A pointer to the key data that needs to be found within the tree. The function uses the tree's comparison function to search for this key.

@Return Value: Returns an iterator pointing to the node containing the key if found. If the key is not found, it returns an iterator pointing to the end node (BSTEnd).

@Time Complexity: 
                  Best: O(1) - In the best-case scenario, the key is found at the root, requiring only one comparison.
                  Average: O(log(n)) - On average, finding a node in a balanced binary search tree takes logarithmic time with respect to the number of nodes in the tree.
                  Worst: O(n) - In the worst case, where the tree degenerates into a linked list, the function might need to traverse all nodes.

@Space Complexity: O(1).
*/
bst_iter_t BSTFind(const bst_t *tree, void *key);


/******************************************************************************/
/*
@Name: BSTForEach
@Description: Apply a user's action function to elements within a specified range in a BST.
@Parameters: 
            1. from - The iterator pointing to the starting nbode of the range within the BST.
            2. to - The iterator pointing to the ending node of the range within the BST.
            3. action_func - A pointer to a user-defined action function.
                    This function should take a single parameter of type 'void*' and return an integer.
                    The action function should return a non-zero value if it encounters an error.
                    If the action function returns a non-zero value, the iteration will stop, and
                    the 'BSTForEach' function will return the same non-zero value.
            4. param - A pointer to user-defined data that can be passed to the action function.

@Return Value: action function status, 0 or the first non-zero value received from action function.

@Time Complexity: 
                    - Average Case: O(log(n))
                    - Worst Case: amortized O(n) where n is the number of nodes in the tree.
                      while some individual Next operations may take O(log(n)) time (when moving from one subtree to another), 
                      most of the Next operations (moving to the next node in the same subtree) will take O(1) time, 
                      leading to a total time complexity of O(n) for the entire traversal. Therefore, the amortized time complexity 
                      of the Next operation during a full traversal is O(1), giving us an amortized time complexity of O(n) for the 
                      whole traversal operation.

@Space Complexity: O(1)
*/
int BSTForEach(bst_iter_t from, bst_iter_t to, int (*action_func)(void *data, void *param), void *param);


/******************************************************************************/
/*
@Name: BSTIsSameIter
@Description: This function checks whether two iterators in a binary search tree point to the same node. 

@Parameters: 
             1. iter1 - The first iterator whose position is to be compared.
             2. iter2 - The second iterator whose position is to be compared.

@Return Value: Returns 1 (true) if both iterators point to the same node in the tree; otherwise, returns 0 (false).

@Time Complexity: 
                  Best: O(1) - The comparison of two iterators is a constant time operation as it involves direct pointer comparison.
                  Average: O(1) - Same as the best case, as the operation doesn't depend on the number of nodes in the tree.
                  Worst: O(1) - Same as the best case.

@Space Complexity: O(1).
*/
int BSTIsSameIter(bst_iter_t iter1, bst_iter_t iter2);


#endif /* __BST_H__ */
