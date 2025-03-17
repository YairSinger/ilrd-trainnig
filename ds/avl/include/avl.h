/***********************************************************
*PROJECT:AVL (Adelson, Velsky, Landis) self-balancing BST
*
*WRITER: Yair Singer
*
*REVIEWER: 
*
*STATUS: 
*
*DATE: 12/09/2023
***********************************************************/
#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */
#include <sys/types.h> /*ssize_t*/
typedef struct avl avl_t;

typedef enum traverse_type
{
    IN_ORDER,
    POST_ORDER,
    PRE_ORDER
} traverse_type_t;



/******************************************************************************/
/******************************************************************************/
/*
@Name: AVLCreate
@Description: 
    Creates a new AVL tree with the specified comparison function. The function
    allocates memory for the AVL tree object and initializes it with the provided
    comparison function to ensure the AVL properties (balance and order) are 
    maintained during insertion and deletion operations.

@Parameters: 
    1. cmp_func - A pointer to a user-defined function that compares two elements
       in the tree. This function takes two const void pointers (representing 
       two elements) as parameters and returns an integer as per the following contract:
          - Returns a negative value if lhs is less than rhs.
          - Returns zero if lhs is equal to rhs.
          - Returns a positive value if lhs is greater than rhs.

@Return: 
    A pointer to the newly created AVL tree. It encapsulates the root node and 
    the comparison function needed for the ordered operations. If the creation 
    fails (e.g., due to memory allocation issues), it returns NULL.

@Time Complexity: 
    O(1).

@Space Complexity: 
    O(1).
*/
avl_t *AVLCreate(int (*cmp_func)(const void *lhs, const void *rhs));

/******************************************************************************/
/*
@Name: AVLDestroy
@Description: 
    Frees all memory allocated for the AVL tree and its nodes. This function 
    traverses the AVL tree and deallocates each node before finally deallocating 
    the tree structure itself. 
@Parameters: 
    1. tree - A pointer to the valid AVL tree that needs to be destroyed. 

@Return: 
    void - This function does not return any value. .

@Time Complexity: 
    O(n) - The time complexity of the function is linear, as it needs to visit 
    each node once to free the memory allocated for it, where n is the number of 
    nodes in the tree.

@Space Complexity: 
    O(h) - where h is the height of the AVL tree. 
*/
void AVLDestroy(avl_t *tree);


/******************************************************************************/
/*
@Name: AVLInsert
@Description: 
    Inserts a new node with the specified data into the AVL tree. The function maintains 
    the AVL property by performing necessary rotations after the insertion to 
    ensure that the tree remains balanced. The data is inserted according to the comparison 
    function provided during the creation of the AVL tree.

@Parameters: 
    1. tree - A pointer to the valid AVL tree where the data should be inserted. It should not be NULL.
    2. data - A pointer to the data that should be stored in the new node. The type of data 
       it points to should match the data type that the tree's comparison function expects.

@Return: 
    int - Returns 0 if the insertion was successful. Returns a non-zero value if the 
    insertion failed, which could occur due to memory allocation failure or other issues.

@Time Complexity: 
    O(log n) - In the worst case, the function may have to traverse a path from the root 
    to a leaf node, and AVL trees are height-balanced, ensuring a logarithmic time complexity.

@Space Complexity: 
    O(1).
*/
int AVLInsert(avl_t *tree, const void *data);

/******************************************************************************/
/*
@Name: AVLRemove
@Description: 
    Removes a node with the specified key data from the AVL tree. The function maintains 
    the AVL property by performing necessary rotations after the removal to 
    ensure that the tree remains balanced. The removal is conducted based on the comparison 
    function provided during the creation of the AVL tree.

@Parameters: 
    1. tree - A pointer to the valid AVL tree from where a node should be removed. 
    2. data_key - A pointer to the key data that identifies the node to be removed. The data 
       type it points to should match the data type expected by the tree's comparison function.

@Return: 
    void - The function does not return a value. 

@Time Complexity: 
    O(log n) - In the worst case, the function may have to traverse a path from the root 
    to a leaf node to find the node to be removed, and potentially adjust the balance 
    of the tree, which ensures a logarithmic time complexity.

@Space Complexity: 
    O(1).
*/
void AVLRemove(avl_t *tree, const void *data_key);

/******************************************************************************/
/*
@Name: AVLGetHeight
@Description: 
    Retrieves the height of the given AVL tree. The height of a tree is defined as the 
    number of edges on the longest path from the root node to a leaf node. An empty tree 
    has a height of -1.

@Parameters: 
    1. tree - A pointer to the valid AVL tree whose height is to be retrieved. The tree pointer 
       should not be NULL.

@Return: 
    ssize_t - Returns the height of the AVL tree as a ssize_t value. 

@Time Complexity: 
    O(1).

@Space Complexity: 
    O(1).
*/
ssize_t AVLGetHeight(const avl_t *tree);


/******************************************************************************/
/*
@Name: AVLCount
@Description: 
    Returns the number of nodes present in the AVL tree.

@Parameters: 
    1. tree - A pointer to the valid AVL tree whose node count is to be retrieved. 
       It should not be NULL.

@Return: 
    size_t - Returns the number of nodes in the AVL tree as a size_t value.

@Time Complexity: 
    O(n) - Count is calculated during this function call by traversing 
    all the nodes in the tree.

@Space Complexity: 
    O(1).
*/
size_t AVLCount(const avl_t *tree);

/******************************************************************************/
/*
@Name: AVLIsEmpty
@Description: 
    Checks whether the AVL tree is empty or not. An AVL tree is considered empty if it 
    doesn't contain any nodes, i.e., the root node is NULL.

@Parameters: 
    1. tree - A pointer to the valid AVL tree which needs to be checked for emptiness. 
       It should not be NULL.

@Return: 
    int - Returns 1 if the tree is empty, i.e., contains no nodes. Otherwise, returns 0.

@Time Complexity: 
    O(1).

@Space Complexity: 
    O(1).
*/
int AVLIsEmpty(const avl_t *tree);

/******************************************************************************/
/*
@Name: AVLFind
@Description: 
    Searches the AVL tree for a node that matches the specified key. If a node with 
    the key is found, it returns a pointer to the data in the node. Otherwise, returns NULL.

@Parameters: 
    1. tree - A pointer to the valid AVL tree where the search will be conducted. The tree pointer 
       should not be NULL.
    2. key - A pointer to the key which needs to be searched within the tree. The key 
       used for the search should be compatible with the comparison function used to 
       build the tree.

@Return: 
    void* - Returns a pointer to the data of the node which matches the key if found, 
    otherwise returns NULL if no matching node is found.

@Time Complexity: 
    O(log n) - In a balanced AVL tree, the time complexity of searching a node is 
    logarithmic in the worst case as the tree height is log(n).

@Space Complexity: 
    O(1).
*/
void *AVLFind(const avl_t *tree, void *key);

/******************************************************************************/
/*
@Name: AVLForEach
@Description: 
    Iterates over each node in the AVL tree and performs the specified action 
    callback function on each node's data. The nodes are visited based on the 
    specified traversal type. 

@Parameters: 
    1. tree - A pointer to the valid AVL tree.
    2. traverse_type - An integer representing the type of tree traversal 
       to perform:
            0 - IN_ORDER.
            1 - POST_ORDER.
            2 - PRE_ORDER.

    3. action_callback - A function pointer representing the callback function to 
       be called on each node's data as it is visited during the traversal. The 
       function takes two parameters: a pointer to the node data and a pointer to 
       some parameter data, and it returns an integer used to indicate 
       success or failure of the action.
    4. param - A pointer to some parameter data to be passed into the action callback 
       function at each call.

@Return: 
    int - Returns 0 if the operation succeeds for all nodes in the tree; otherwise 
    returns a non-zero value, which might indicate the error or the result of 
    the action callback function on the last node visited.

@Time Complexity: 
    O(n) - The time complexity is linear, as each node in the tree needs to be visited 
    once during the traversal.

@Space Complexity: 
    O(log n), where n is the number of nodes in the tree.
*/
int AVLForEach(avl_t *tree, int traverse_type, int (*action_callback)(void *, void *), void *param);

/*** Advanced **/
/******************************************************************************/
/*
@Name: AVLMultiFind
@Description: Performs a multiple find operation on an AVL tree, populating a doubly-linked list with the nodes that match the criteria defined by the is_match function.

@Parameters: 
   - const avl_t *tree: a pointer to the valid AVL tree where the find operation is to be performed.
   - int (*is_match)(void *data, void *arg): a function pointer to a valid match function which determines whether a node matches the desired criteria.
   - void *arg: a pointer to an argument to be passed to the is_match function.
   - dllist_t *output_list: a pointer to a valid doubly-linked list where the found items will be stored.

@Return: This function does not return any value; it populates the output_list with the results.

@Time Complexity: O(n), where n is the number of nodes in the tree (assuming a full traversal is necessary).

@Space Complexity: O(log(n)) for the recursive stack (assuming a recursive approach), plus additional space for storing results in the output list.
*/
/*void AVLMultiFind(const avl_t *tree, int (*is_match)(void *data, void *arg), void *arg, dllist_t *output_list);
*/
/******************************************************************************/
/*
@Name: AVLRemoveMultiple
@Description: This function traverses the AVL tree and removes nodes that satisfy the condition specified by the should_remove callback function. 
The removed nodes are stored in the output_list.

@Parameters: 
   - avl_t *tree: A pointer to the valid AVL tree from which nodes are to be removed.
   - int (*should_remove)(void *data, void *arg): A callback function that takes a data pointer and an argument pointer, returning a boolean indicating 
     whether a given node should be removed (1 for true, 0 for false).
   - void *arg: A pointer to an argument that will be passed to the should_remove callback function to help determine whether to remove a node.
   - dllist_t *output_list: A pointer to a valid doubly-linked list where removed items will be stored.

@Return: This function does not return any value; it modifies the AVL tree in place and populates the output_list with removed nodes.

@Time Complexity: O(n), where n is the number of nodes in the AVL tree, assuming the function performs a full traversal of the tree to find nodes to remove.

@Space Complexity: O(log(n)) for the recursive stack space (assuming a recursive approach to tree traversal), plus the additional space required to store removed nodes in the output list.
*/
/*void AVLRemoveMultiple(avl_t *tree, int (*should_remove)(void *data, void *arg), void *arg, dllist_t *output_list);
*/

#endif /* __AVL_H__ */
