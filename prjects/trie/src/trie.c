#include <string.h> /*memset*/
#include <stdlib.h>
#include <assert.h>
#include "trie.h"

#define TRUE 1
#define FALSE 0
#define MAX_TRIE_HEIGHT 32


typedef enum children
{
    LEFT,		/*must be first*/
    RIGHT,		/*must be sec*/
    NUM_OF_CHILDREN
} children_t;

struct trie_node
{
    trie_node_t *children[NUM_OF_CHILDREN];
    struct trie_node *parent;
    int is_full;
};

struct trie
{
    size_t height;
    trie_node_t *root;
};

static void RemoveNodes(trie_node_t *root);/*post order traverse and remove*/
static void UpdateIsFull(trie_node_t *leaf, size_t cur_height);
static size_t CountFreeLeafsRec(const trie_t *trie, trie_node_t *root,size_t cur_height, size_t total_count);
static size_t Pow(size_t base, size_t to_the_power);
static trie_node_t *CreateNewTrieNode(trie_node_t *parent);
static void RemoveNodesAfterMallocFail(trie_node_t *leaf);

/*=============== API Functions ================================*/

trie_t *TrieCreate(size_t height)
{
	trie_t *trie = NULL;
	
	size_t i = 0;
		
	trie = (trie_t *)malloc(sizeof(trie_t));
	if (NULL == trie)
	{
		return NULL;
	}
	
	trie->height = height;
	trie->root = (trie_node_t *)malloc(sizeof(trie_node_t));
	if (NULL == trie->root)
	{	
		free(trie);
		return NULL;
	}
	
	for (i = 0; i < NUM_OF_CHILDREN; ++i)
	{
		trie->root->children[i] = NULL;
	}
	trie->root->parent = NULL;
	trie->root->is_full = FALSE;
	
	return trie;
}


/*============================================*/


void TrieDestroy(trie_t *trie)
{
	assert(NULL != trie);
	
	
	RemoveNodes(trie->root);
	trie->root = NULL;
	trie->height = 0;
	free(trie);
}

int TrieIsFull(trie_t *trie)
{
	assert(NULL != trie);
	
	return (trie->root->is_full);
}


/*============================================*/


trie_status_t TrieCreatePath(trie_t *trie, unsigned int requested_path, unsigned int *givven_path)
{
	trie_node_t *parent = NULL;
	unsigned int path = requested_path;
	unsigned int max_path = requested_path;
	unsigned int min_path = 0;
	unsigned int mask = 0x80000000;
	children_t child = LEFT;
	size_t cur_height = 0;
	size_t base_height = 0;
	size_t i = 0;
	
	
	assert(NULL != trie);
	
	if (TrieIsFull(trie))
	{
		return TRIE_PATH_IS_FULL;
	}
	
	base_height = MAX_TRIE_HEIGHT - trie->height;
	for (i = 0; i < trie->height; ++i)
	{
		max_path = max_path | (mask >> (base_height + i));
	}
	
	for (i = 0, min_path = max_path; i < trie->height; ++i)
	{
		min_path = min_path ^ (1 << i);
	}
	
	parent = trie->root;
	while(cur_height < trie->height && path <= max_path)
	{
		child = ((mask >> (base_height + cur_height)) & path) ? RIGHT : LEFT;
		if (NULL == parent->children[child])
		{
			parent->children[child] = CreateNewTrieNode(parent);
			if (NULL == parent->children[child])
			{
				RemoveNodesAfterMallocFail(parent);
				return TRIE_ALLOCATION_FAIL;
			}
						
			++cur_height;
			parent = parent->children[child];
		}
		else
		{
			if(parent->children[child]->is_full == TRUE)/*continue searching for next address from node above */
			{
				if(0 != cur_height)
				{
					do 
					{
						--cur_height;				
						parent = parent->parent;
					}
					while (NULL != parent->parent && (mask >> (base_height + cur_height)) & path);
				}
				path += 1;
			}
			else /*continue on exsiting path*/
			{
				parent = parent->children[child];
				++cur_height;
			}
		}				
	}
	
	if (path == max_path + 1)
	{
		return TrieCreatePath(trie, min_path, givven_path);
	}
	
	if(cur_height == trie->height && FALSE == parent->is_full) 
	{
		parent->is_full = TRUE;
		*givven_path = path;
		UpdateIsFull(parent, cur_height);
		return TRIE_SUCCESS;
	}
	
}

static trie_node_t *CreateNewTrieNode(trie_node_t *parent)
{
	trie_node_t *new_node = (trie_node_t *)malloc(sizeof(trie_node_t));
	if (NULL == new_node)
	{
		return NULL;				
	}
			
	new_node->parent = parent;
	new_node->is_full = FALSE;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	return new_node;
}

/*============================================*/

trie_status_t TrieRemovePath(trie_t *trie,  unsigned int path)
{
	trie_node_t *parent = NULL;
	trie_node_t *child_node = NULL;
	unsigned int mask = 0x80000000;
	children_t child = LEFT;
	size_t cur_height = 0;
	size_t base_height = 0;
		
	assert(NULL != trie);
	
	base_height = MAX_TRIE_HEIGHT - trie->height;
	parent = trie->root;
	while(cur_height < trie->height)
	{
		child = ((mask >> (base_height + cur_height)) & path)? RIGHT : LEFT;
		if (NULL == parent->children[child])
		{
			return TRIE_DOUBLE_FREE;
		}
		parent = parent->children[child];
		++cur_height;
	}
	
	while(cur_height > 0)
	{
		--cur_height;
		child = ((mask >> (base_height + cur_height)) & path)? RIGHT : LEFT;
		child_node = parent;
		parent = parent->parent;
		
		if (NULL == child_node->children[LEFT] && NULL == child_node->children[RIGHT])
		{
			memset(child_node, 0, sizeof(trie_node_t));
			free(child_node);
			parent->children[child] = NULL;
			parent->is_full = FALSE;
		}
		else
		{
			child_node->is_full = FALSE;
		}
	}
	
	trie->root->is_full = FALSE;
	return TRIE_SUCCESS;
}
/*============================================*/
size_t TrieCountFreeLeafs(const trie_t *trie)
{
	size_t total_count = 0;	
	
	assert(NULL != trie);
	
	total_count = Pow(2,trie->height);
	return CountFreeLeafsRec(trie, trie->root, 0, total_count);	
}

static size_t CountFreeLeafsRec(const trie_t *trie, trie_node_t *root,size_t cur_height, size_t total_count)
{
	assert(NULL != trie);
	assert(NULL != root);
	assert(cur_height < trie->height + 1);
	
	if(TRUE == root->is_full)
	{
		return total_count - Pow(2,trie->height - cur_height);
	}
	
	if(NULL == root->children[LEFT] && NULL == root->children[RIGHT])
	{
		return total_count;
	}
	
	
	if(NULL != root->children[LEFT])
	{
		total_count = CountFreeLeafsRec(trie, root->children[LEFT], cur_height + 1, total_count);
	}
	
	if(NULL != root->children[RIGHT])
	{
		total_count = CountFreeLeafsRec(trie, root->children[RIGHT], cur_height + 1, total_count);
	}
	
	return total_count;
}
	
static size_t Pow(size_t base, size_t to_the_power)
{
	size_t i = 0;
	size_t res = 1;
	 
	for (i = 0; i < to_the_power; ++i)
	{
		res *= base;
	}
	
	return res;
}	

static void RemoveNodes(trie_node_t *root) /*post order traverse and remove*/
{
	if (NULL == root)
	{
		return;
	}
	
	root->is_full = 0;
	RemoveNodes(root->children[LEFT]);
	RemoveNodes(root->children[RIGHT]);	
	free(root);
}

static void UpdateIsFull(trie_node_t *leaf, size_t cur_height)
{
	trie_node_t *runner = NULL;
		
	assert(NULL != leaf);
	
	runner = leaf->parent;
	--cur_height;
	while(0 < cur_height && NULL != runner->children[LEFT] && TRUE == runner->children[LEFT]->is_full &&
		   					NULL != runner->children[RIGHT] && TRUE == runner->children[RIGHT]->is_full)
	{
			runner->is_full = TRUE;
			runner = runner->parent;
			--cur_height;			
	}
	
	if (0 == cur_height && NULL != runner->children[LEFT] && TRUE == runner->children[LEFT]->is_full &&
		   					NULL != runner->children[RIGHT] && TRUE == runner->children[RIGHT]->is_full)
	{
		runner->is_full = TRUE;
	}
	
	
}

static void RemoveNodesAfterMallocFail(trie_node_t *leaf)
{
	trie_node_t *runner = NULL;
	trie_node_t *node_to_free = NULL;
		
	assert(leaf);
	
	runner = leaf;

	while(NULL != runner->parent)
	{
		if(NULL != runner->children[LEFT]  || NULL != runner->children[RIGHT])
		{
			break;
		}
		
		node_to_free = runner;
		runner = runner->parent;
		memset(node_to_free, 0,sizeof(trie_node_t));
		free(node_to_free);
		/*TODO set parent pointer to null*/
	}
}
