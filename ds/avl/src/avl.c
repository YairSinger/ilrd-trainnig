#include <assert.h>
#include <stdlib.h> /*calloc */
#include <stdio.h>
#include "avl.h"



typedef struct avl_node avl_node_t;


typedef enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
}children_t;

 struct avl_node
{
    void *data;
    size_t height; 
    avl_node_t *children[NUM_OF_CHILDREN];
};

struct avl
{
    avl_node_t *root;
    int (*cmp_func)(const void *, const void *);
};

#define HAS_LEFT_CHILD(root) (root)->children[LEFT] != NULL
#define HAS_RIGHT_CHILD(root) (root)->children[RIGHT] != NULL

#define RIGHT_HEAVY 2
#define LEFT_HEAVY -2


static void Balance(avl_node_t **root);
static int GetBalanceStatus(avl_node_t *node);
static int IsBalanced(avl_node_t *node);
static avl_node_t **GetBottomLeft(avl_node_t **node);
static void SwapAndFree(avl_node_t **node, avl_node_t **successor, int direction);
static avl_node_t **GetBottomRight(avl_node_t **node);
static void RemoveHelper(const void *data_key, avl_node_t **node, int (*cmp_func)(const void *lhs, const void *rhs));

/*get the max height from both children and increase by one */
static size_t UpdateHeight(avl_node_t *node)
{
	size_t height = 0;
		
	if((NULL == node->children[LEFT]) && (NULL == node->children[RIGHT]))
	{
		height = 0;
	}
	else if((NULL != node->children[LEFT]) && (NULL == node->children[RIGHT]))
	{
		height = 1 + (node->children[LEFT])->height;
	}
	else if((NULL == node->children[LEFT]) && (NULL != node->children[RIGHT]))
	{
		height = 1 + (node->children[RIGHT])->height;
	}
	else
	{
		height = ((node->children[LEFT])->height) > ((node->children[RIGHT])->height) ?
									(1 + (node->children[LEFT])->height): 
									(1 + (node->children[RIGHT])->height);
	}
	
	return height;
							
}

/*positive means right_heavy, negative left heavy*/ 
static int CheckBalance(avl_node_t *node)
{
	int left = 0;
	int right = 0;
	
	assert(NULL != node);
	
	if (NULL != node->children[LEFT])
	{
		left = 1 + (int)((node->children[LEFT])->height);
	}
	
	if (NULL != node->children[RIGHT])
	{
		right = 1 + (int)((node->children[RIGHT])->height);
	}
	
	return right - left;
}

static avl_node_t *RotateRight(avl_node_t *old_root)
{
	avl_node_t *new_root = old_root->children[LEFT];
	
	old_root->children[LEFT] = new_root->children[RIGHT];
	new_root->children[RIGHT] = old_root;
	return new_root;
}

static avl_node_t *RotateLeft(avl_node_t *old_root)
{
	avl_node_t *new_root = old_root->children[RIGHT];
	
	old_root->children[RIGHT] = new_root->children[LEFT];
	new_root->children[LEFT] = old_root;
	return new_root;
}

static void AssureBalance(avl_node_t **root)
{
	int balance = 0;
	int child_balance = 0;
	
	balance = CheckBalance(*root);
		if (balance > 1)
		{
			child_balance = CheckBalance ((*root)->children[RIGHT]);
			if (child_balance < 0) /*RR and then LR*/
			{
				(*root)->children[RIGHT] = RotateRight((*root)->children[RIGHT]);
				(((*root)->children[RIGHT])->children[RIGHT])->height -= 1;
				((*root)->children[RIGHT])->height += 1;
				
								
				(*root) = RotateLeft((*root));
				((*root)->children[LEFT])->height -= 2;
				
			}
			else
			{
				(*root) = RotateLeft((*root));
				((*root)->children[LEFT])->height -= 2;
			}
		}
		else if (balance < -1)
		{
			child_balance = CheckBalance ((*root)->children[LEFT]);
			if (child_balance > 0) /*LR and then RR*/
			{
				(*root)->children[LEFT] = RotateLeft((*root)->children[LEFT]);
				(((*root)->children[LEFT])->children[LEFT])->height -= 1;
				((*root)->children[LEFT])->height += 1;
				
				
				(*root) = RotateRight((*root));
				((*root)->children[RIGHT])->height -= 2;

			}
			else
			{
				(*root) = RotateRight((*root));
				((*root)->children[RIGHT])->height -= 2;
				
			}
		}
}
	


static void PrintTree(avl_node_t *node, int space) 
{

    int i = 0;

      if (node == NULL) 
      {
        return;
      }

      PrintTree(node->children[RIGHT], space  + 1 ); 

      for (; i < space; i++) 
      {
        printf("                 ");   
      }
      
      printf("data:%d, (height:%ld)\n", *(int *)node->data, node->height);
      
      PrintTree(node->children[LEFT], space + 1); 
}


void Print(avl_t *tree)
{

    PrintTree(tree->root, 0);
    
}



/********************************************************
*														*
*					API FUNCTIONS						*	
*														*	
*********************************************************/



/*====================  BSTCreate  =======================*/

avl_t *AVLCreate(int (*cmp_func)(const void *lhs, const void *rhs))
{
	avl_t *avl = (avl_t *) malloc(sizeof(avl_t));
	
	if(avl != NULL)
	{
		avl->cmp_func = cmp_func;
		avl->root = NULL;		
	}

	return avl;
}

/*====================  AVLInsert  =======================*/

static void InsertNode(avl_t *tree, avl_node_t **root, avl_node_t *new_node)
{
	int comp_result = 0;
	/*int balance = 0;
	int child_balance;*/
	
	if(NULL == *root)
	{
		*root = new_node;
		return;
	}
	else
	{	
		comp_result = tree->cmp_func((*root)->data, new_node->data);		
		
		if(comp_result > 0)
		{
			InsertNode(tree, &((*root)->children[LEFT]), new_node);
			(*root)->height = UpdateHeight(*root);
		}
		else if (comp_result < 0)
		{
			InsertNode(tree, &((*root)->children[RIGHT]), new_node);
			(*root)->height = UpdateHeight(*root);
		}
				
		AssureBalance(root);
		return;
	}
}

int AVLInsert(avl_t *tree, const void *data)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	int status = 1; 
	
	assert(NULL != tree);
	
	if (NULL != new_node)
	{
	status = 0;
	new_node->data = (void *) data;
	new_node->height = 0;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	
	InsertNode(tree, &(tree->root), new_node);
	
	}
	
	return status;
}

/*====================  AVLDestroy  =======================*/
static void RemoveNodes(avl_node_t *root) /*post order traverse and remove*/
{
	if (NULL == root)
	{
		return;
	}
	root->data = NULL;
	root->height = 0;
	RemoveNodes(root->children[LEFT]);
	RemoveNodes(root->children[RIGHT]);	
	free(root);
}
/*====================  AVLDestroy  =======================*/
void AVLDestroy(avl_t *tree)
{
	assert(NULL != tree);
	
	RemoveNodes(tree->root);
	tree->root = NULL;
	tree->cmp_func = NULL;
	free(tree);
}

/*====================  AVLRemove  =======================*/
static void Balance(avl_node_t **root)
{
	int balance_status = 0;
	
	balance_status = (GetBalanceStatus(*root));
	
	if (LEFT_HEAVY == balance_status)
	{
		if (0 < GetBalanceStatus((*root)->children[LEFT]))
		{
			RotateDoubleRight(root);
		}
		
		else
		{
			RotateRight(root);
		}
	}
	
	else if (RIGHT_HEAVY == balance_status)
	{
		if (0 > GetBalanceStatus((*root)->children[RIGHT]))
		{
			RotateDoubleLeft(root);
		}
		
		else
		{
			RotateLeft(root);
		}
	}
}


static int GetBalanceStatus(avl_node_t *node)
{
	int balance_status = 0;
	
	if (1 == (HAS_LEFT_CHILD(node)))
	{
		balance_status -= (node->children[LEFT]->height + 1);
	}
	
	if (1 == (HAS_RIGHT_CHILD(node)))
	{
		balance_status += (node->children[RIGHT]->height + 1);
	}
	
	return balance_status;
}



static int IsBalanced(avl_node_t *node)
{
	int balance_status = 0;
	
	balance_status = GetBalanceStatus(node);
	
	return (RIGHT_HEAVY != balance_status && LEFT_HEAVY != balance_status);
}



static avl_node_t **GetBottomLeft(avl_node_t **node)
{
	avl_node_t **successor = NULL;
	
	if (1 == (HAS_LEFT_CHILD(*node)))
	{
		successor = GetBottomLeft(&(*node)->children[LEFT]);
		
		if (0 > GetBalanceStatus(*node))
		{
			--(*node)->height;
		}
		
		return successor;
	}
	
	return node;
}

static void SwapAndFree(avl_node_t **node, avl_node_t **successor, int direction)
{
	avl_node_t *tmp_node = NULL;
	
	tmp_node = *successor;
	
	(*node)->data = (*successor)->data;
	*successor = (*successor)->children[direction];
	
	free(tmp_node);
}



static avl_node_t **GetBottomRight(avl_node_t **node)
{
	avl_node_t **successor = NULL;
	
	if (1 == (HAS_RIGHT_CHILD(*node)))
	{
		successor = GetBottomRight(&(*node)->children[RIGHT]);
		
		if (0 < GetBalanceStatus(*node))
		{
			--(*node)->height;
		}
		
		return successor;
	}
	
	return node;
}
static void RemoveHelper(const void *data_key, avl_node_t **node,
						 int (*cmp_func)(const void *lhs, const void *rhs))
{
	avl_node_t **successor = NULL;
	
	if (NULL == *node)
	{
		return;
	}
	
	if (0 > cmp_func(data_key, (*node)->data))
	{
		RemoveHelper(data_key, &(*node)->children[LEFT], cmp_func);
	}
	
	else if (0 < cmp_func(data_key, (*node)->data))
	{
		RemoveHelper(data_key, &(*node)->children[RIGHT], cmp_func);
	}
	
	else if (0 == cmp_func(data_key, (*node)->data))
	{
		if (1 == (HAS_RIGHT_CHILD(*node)))
		{
			successor = GetBottomLeft(&(*node)->children[RIGHT]);
			SwapAndFree(node, successor, RIGHT);
		}
		
		else if (1 == (HAS_LEFT_CHILD(*node)))
		{
			successor = GetBottomRight(&(*node)->children[LEFT]);
			SwapAndFree(node, successor, LEFT);
		}
		
		else
		{
			free(*node);
			*node = NULL;
			
			return;
		}
	}
	
	UpdateHeight(*node);
		
	if (0 == IsBalanced(*node))
	{
		Balance(node);
	}
}

/*********/

void AVLRemove(avl_t *tree, const void *data_key)
{
	assert(NULL != tree);
	
	RemoveHelper(data_key, &tree->root, tree->cmp_func);
}











static void UpdateIfHeight(avl_node_t *node,children_t find_in_side)
{
	assert(NULL != node);
	
	if (LEFT == find_in_side && NULL != node->children[RIGHT] && (node->children[LEFT] > node->children[RIGHT]))
	{
		node->height -= 1;
	}
	else if (RIGHT == find_in_side && NULL != node->children[LEFT] && (node->children[RIGHT] > node->children[LEFT]))
	{
		node->height -= 1;
	}
}

static avl_node_t *FindRec(const avl_t *tree,const avl_node_t *node, void *key)
{
	int cmp_result = 0;
	avl_node_t *find_res = NULL;
	
	if(NULL == node)
	{
		return NULL;
	}
	
	cmp_result = tree->cmp_func(node->data, key);
	if(cmp_result > 0)
	{
		find_res = FindRec(tree,node->children[LEFT], key);
		return find_res;
	}
	else if(cmp_result < 0)
	{
		find_res = FindRec(tree,node->children[RIGHT], key);
		return find_res;
		
	}
	else if(0 == cmp_result)
	{
		find_res = (avl_node_t *)(node);
		return find_res;
	}

}

static avl_node_t *FindSuccessorLeftChild(avl_t *tree, avl_node_t *node,const void *key)
{
	avl_node_t *successor = NULL;
	
	if(NULL != node->children[RIGHT])
	{
		successor = FindSuccessorLeftChild(tree,node->children[RIGHT], key);
		return successor;
	}
	
	return node;
	
}

static avl_node_t *FindSuccessorRightChild(avl_t *tree, avl_node_t *node,const void *key)
{
	avl_node_t *successor = NULL;
	
	if(NULL != node->children[LEFT])
	{
		successor = FindSuccessorRightChild(tree,node->children[LEFT], key);
		return successor;
	}
	
	return node;
	
}

static void RemoveNode(avl_t *tree, avl_node_t **node_ptr, const void *data_key)
{
	int cmp_result = 0;
	avl_node_t *temp = NULL;
	avl_node_t *successor = NULL;
	
	/*finding remove_node*/
	if (*node_ptr == NULL)
	{
		return ;
	}
	
	cmp_result = tree->cmp_func((*node_ptr)->data, data_key);
	if(cmp_result > 0)
	{
		RemoveNode(tree,&((*node_ptr)->children[LEFT]), data_key);
	}
	else if(cmp_result < 0)
	{
		RemoveNode(tree,&((*node_ptr)->children[RIGHT]), data_key);
	}
	else if(0 == cmp_result)
	{
		/* finding successor */
		if (NULL != (*node_ptr)->children[LEFT] || NULL != (*node_ptr)->children[RIGHT])
		{	
			 if (NULL != (*node_ptr)->children[LEFT])
			{
				successor = FindSuccessorLeftChild(tree, (*node_ptr)->children[LEFT], data_key);
				/*swap and free*/
				(*node_ptr)->data = successor->data;
				RemoveNode(tree,&successor, (successor)->data);
			}
			else if(NULL != (*node_ptr)->children[RIGHT])
			{
				successor = FindSuccessorRightChild(tree, (*node_ptr)->children[RIGHT], data_key);
				/*swap and free*/
				(*node_ptr)->data = successor->data;
				RemoveNode(tree,&successor, (successor)->data);
			}
		}
		else
		{
			free(*node_ptr);
			*node_ptr = NULL;
			return;
		}
	}
	
	(*node_ptr)->height = UpdateHeight(*node_ptr);
	AssureBalance(node_ptr);
	
	
}


/*
void AVLRemove(avl_t *tree, const void *data_key)
{
	avl_node_t *left_holder = NULL;
	avl_node_t *right_holder = NULL;
	
	assert(NULL != tree);
	
	printf("before ******************\n");
	Print(tree);
	
	RemoveNode(tree, &(tree->root), data_key);
	
	/*tree->root->height = UpdateHeight(tree->root);
	AssureBalance(&(tree->root));*/
	
	printf("after ******************\n");
	Print(tree);

}
*/
ssize_t AVLGetHeight(const avl_t *tree)
{
	assert(NULL != tree);
	
	if (NULL == tree->root)
	{
		return -1;
	}
	else 
	{
		return tree->root->height;
	}
}

/*====================  AVLCount  =======================*/

static size_t CountRec(avl_node_t *root)
{
	if(root == NULL)
	{
		return 0;
	}
	return (1 + CountRec(root->children[LEFT]) + CountRec(root->children[RIGHT]));
}


size_t AVLCount(const avl_t *tree)
{
	assert(NULL != tree);
	
	if(NULL == tree->root)
	{
		return 0;
	}
	else
	{
		return CountRec(tree->root);
	}
}

/*====================  AVLIsEmpty  =======================*/
int AVLIsEmpty(const avl_t *tree)
{
	assert (NULL != tree);
	return (NULL == tree->root);	
}

/*====================  AVLFind  =======================*/


void *AVLFind(const avl_t *tree, void *key)
{
	avl_node_t *res = NULL;
	assert(NULL != tree);
	
	res = FindRec(tree, tree->root, key);
	if (NULL != res)
	{
		return res->data;
	}
	return NULL;
}
/*====================  AVLForEach  =======================*/
static int ForEachInOrder(avl_node_t *root, int (*action_callback)(void *, void *),void *param)
{
	int status = 0;
	if (NULL != root)
	{
		if (HAS_LEFT_CHILD(root))
		{
			status = ForEachInOrder(root->children[LEFT], action_callback,param);
			if (0 != status)
			{
				return status;
			}
		}
				
		status = action_callback(root->data, param);
		if (0 != status)
		{
			return status;
		}
			
		if (HAS_RIGHT_CHILD(root))
		{
			status = ForEachInOrder(root->children[RIGHT], action_callback,param);
			return status;
		}
	}
}

static int ForEachPostOrder(avl_node_t *root, int (*action_callback)(void *, void *),void *param)
{
	int status = 0;
	
	if( NULL != root)
	{
		if (HAS_LEFT_CHILD(root))
		{
		
			status = ForEachInOrder(root->children[LEFT], action_callback,param);
			if (0 != status)
			{
				return status;
			}
		}
		
		if (HAS_RIGHT_CHILD(root))
		{
			status = ForEachInOrder(root->children[RIGHT], action_callback,param);
			if (0 != status)
			{
				return status;
			}
		}
		status = action_callback(root->data, param);
		return status;
	}

}

static int ForEachPreOrder(avl_node_t *root, int (*action_callback)(void *, void *),void *param)
{
int status = 0;
	
	if( NULL != root)
	{
		status = action_callback(root->data, param);
		if (0 != status)
		{
			return status;
		}
		
		if (HAS_LEFT_CHILD(root))
		{
		
			status = ForEachPreOrder(root->children[LEFT], action_callback,param);
			if (0 != status)
			{
				return status;
			}
		}
		
		if (HAS_RIGHT_CHILD(root))
		{
			status = ForEachPreOrder(root->children[RIGHT], action_callback,param);
			return status;
		}
	}

}

int AVLForEach(avl_t *tree, int traverse_type, int (*action_callback)(void *, void *), void *param)
{
	int status = 0;
	
	assert(NULL != tree);
	assert(NULL != action_callback);

	switch (traverse_type)
	{
		case IN_ORDER:
			status = ForEachInOrder(tree->root, action_callback,param);
			break;
		case POST_ORDER:
			status = ForEachPostOrder(tree->root, action_callback,param);
			break;
		case PRE_ORDER: 
			status = ForEachPreOrder(tree->root, action_callback,param);
			break;
	}
	
	return status;	
}

