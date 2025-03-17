#ifndef __TRIE__H
#define __TRIE__H

#include <stddef.h> /* size_t */

typedef enum trie_status
{
	TRIE_SUCCESS,
	TRIE_ALLOCATION_FAIL,
	TRIE_IS_FULL,
	TRIE_PATH_IS_ALLOCATED,
	TRIE_PATH_IS_FULL,
	TRIE_DOUBLE_FREE,
	TRIE_INVALID_INPUT
} trie_status_t;

typedef enum path_insert_mode
{
	TRIE_INSERT_BY_NODE_POINTER,
	TRIE_INSERT_BY_PATH
} path_insert_mode_t;

typedef struct trie trie_t;
typedef struct trie_node trie_node_t;

/*
typedef enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
} children_t;

trie_node
{
    trie_node_t *children[NUM_OF_CHILDREN];
    struct trie_node *parent;
    int is_full;
};

struct trie
{
    size_t height;
    trie_node_t root;
};
*/

/*****************************************************************************************/
/*
@Name: TrieCreate
@Description: 
    Allocates memory and initializes a new Trie with a specified height. The 
    height determines the depth or levels the trie can have.
 
@Parameters: 
    - height: The maximum depth or levels the Trie can have.

@Return: 
    - Returns a valid pointer to the newly created Trie or NULL if memory 
    allocation fails.

@Time Complexity: 
    O(1).

@Space Complexity: 
    O(1).

*/
trie_t *TrieCreate(size_t height);

/*****************************************************************************************/
/*

@Name: TrieIsFull
@Description: 
   
 
@Parameters: 
    - .

@Return: 
    - 

@Time Complexity: 
    O(1).

@Space Complexity: 
    O(1).
*/
int TrieIsFull(trie_t *trie);


/*****************************************************************************************/
/*
@Name: TrieDestroy
@Description: 
    Deallocates memory and safely terminates the Trie structure.
 
@Parameters: 
    - trie: A valid pointer to the trie to be destroyed.

@Return: 
    - None.

@Time Complexity: 
    O(n).

@Space Complexity: 
    O(1).
*/
void TrieDestroy(trie_t *trie);


/*****************************************************************************************/
/*
@Name: TrieCreatePath
@Description: 
    Inserts a new path into the Trie.
 
@Parameters: 
    - trie: A valid pointer to the trie.
    - requested: requested host_id,  if node pointer is holds the node data.
    - node:  when NULL, return as a pointer to the path end node.
    		when node is given, insert requested to node in direct access

@Return: 
	- TRIE_SUCCESS - Operation successful.
	- TRIE_ALLOCATION_FAIL - Memory allocation failed during insertion.
	- TRIE_PATH_IS_FULL - if path is allocated
@Time Complexity: 
    O(n).

@Space Complexity: 
    O(1).
*/
trie_status_t TrieCreatePath(trie_t *trie, unsigned int requested_path, unsigned int *givven_path);


/*****************************************************************************************/

/*

@Name: TrieRemovePath
@Description: 
 
@Parameters: 
    - trie: A valid pointer to the trie.

@Return: 
	- TRIE_SUCCESS - Operation successful.
	- TRIE_DOUBLE_FREE -Givven path does not exists.
@Time Complexity: 
    O(h)

@Space Complexity: 
    O(1).
*/
trie_status_t TrieRemovePath(trie_t *trie,  unsigned int path);

/*****************************************************************************************/
/*
@Name: TrieCountLeafs
@Description: 
     - Counts the number of leafs.
@Parameters: 
    - trie: A valid pointer to the trie. 

@Return: 
    - number of leafs.
    
@Time Complexity: 
    O(n)

@Space Complexity: 
    O(1).
*/
size_t TrieCountFreeLeafs(const trie_t *trie);

#endif /* __TRIE__H */
