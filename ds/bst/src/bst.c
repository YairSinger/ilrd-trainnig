#include <assert.h>
#include <stdlib.h> /*calloc */
#include <stdio.h>
#include "bst.h"

#define PTR_2_ITER(ptr) (bst_iter_t)(ptr) 
#define ITER_2_PTR(iter) (bst_node_t *)(iter)
#define IS_LEFT_CHILD(ptr) (((ptr)->parent)->children[LEFT]) == ptr ? 1 : 0
enum children
{
	LEFT,
	RIGHT,
	NUM_OF_CHILDREN
};

struct bst_node
{
	bst_node_t *parent;
	bst_node_t *children[NUM_OF_CHILDREN];
	
	void *data;
};

struct bst
{
	bst_node_t root_stub;
	int (*cmp_func)(const void *lhs, const void *rhs);
};
/***************************************************************/
/*mooves to lowest left branch from given root */
bst_node_t *BSTBeginFromRoot(bst_node_t *root)
{
	bst_node_t *runner = root;
	bst_node_t *next = root->children[LEFT];
	
	assert(NULL != root);
	
	while (NULL != next)
		{
			next = runner->children[LEFT];
			if (NULL!= next)
			{
				runner = next;
			}
		}
	return runner;
}

/***************************************************************/
/*mooves to lowest right branch from given root */
bst_node_t *BSTEndFromRoot(bst_node_t *root)
{
	bst_node_t *runner = root;
	bst_node_t *next = root->children[RIGHT];
	
	assert(NULL != root);
	
	while (NULL != next)
		{
			next = runner->children[RIGHT];
			if (NULL!= next)
			{
				runner = next;
			}
		}
	return runner;
}

/***************************************************************/
static int CompareFuncWraper(const bst_t *tree, bst_iter_t local, bst_iter_t new)
{
	assert(NULL != tree);
	
	if (BSTIsSameIter(local, BSTEnd(tree)))
	{
		return 1;
	}
	else
	{
		return (tree->cmp_func(BSTGetData(local), BSTGetData(new)));
	}
}



/********************************************************
*														*
*					API FUNCTIONS						*	
*														*	
*********************************************************/



/*====================  BSTCreate  =======================*/

bst_t *BSTCreate(int (*cmp_func)(const void *lhs, const void *rhs))
{
	bst_t *bst = NULL;
	
	assert(NULL != cmp_func);
	
	bst = (bst_t *) malloc(sizeof(bst_t));
	if(bst != NULL)
	{
		bst->root_stub.parent = NULL;
		bst->root_stub.children[RIGHT] = NULL;
		bst->root_stub.children[LEFT] = NULL;
		
		bst->cmp_func = cmp_func;		
	}
	
	return bst;
}

/*====================  BSTIsEmpty  =======================*/

int BSTIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);
	
	return (NULL == tree->root_stub.children[LEFT]);
}

/*====================  BSTIsSameIter  =======================*/

int BSTIsSameIter(bst_iter_t iter1, bst_iter_t iter2)
{
	assert(NULL != (ITER_2_PTR(iter1)));
	assert(NULL != (ITER_2_PTR(iter2)));
	
	return (iter1 == iter2);
}

/*====================  BSTInsert  =======================*/
bst_iter_t BSTInsert(bst_t *tree, const void *data)
{
	bst_iter_t new_node = (bst_iter_t)malloc(sizeof(bst_node_t));
	bst_iter_t runner = NULL;
	bst_node_t *next = NULL;
	int comp_result = 1; /*for first node as left child */
	
	assert(NULL != tree);
	
	runner = (PTR_2_ITER(&(tree->root_stub)));
	next = tree->root_stub.children[LEFT];
	
	if (NULL != (ITER_2_PTR(new_node)))
	{
		new_node->data = (void *)data;
		while (NULL != next) 
		{
			comp_result = CompareFuncWraper(tree, runner, new_node);
			if(0 < comp_result)
			{
				next = (ITER_2_PTR(runner))->children[LEFT];
			}
			else
			{
				next = (ITER_2_PTR(runner))->children[RIGHT];
			}
			
			if (NULL!= next)
			{
				runner = next;
			}
		}
			
		comp_result = CompareFuncWraper(tree, runner, new_node);
		if(0 < comp_result)
		{
			runner->children[LEFT] = new_node;	
		}
		else
		{
			runner->children[RIGHT] = new_node;
		}
		
		new_node->parent = runner;
		new_node->children[RIGHT] = NULL;
		new_node->children[LEFT] = NULL;
	}
	else 
	{
		new_node = BSTEnd(tree);
	}
	return new_node;

}

/*====================  BSTEnd  =======================*/


bst_iter_t BSTEnd(const bst_t *tree)
{
	assert (NULL != tree);
	return PTR_2_ITER(&(tree->root_stub));
}

/*====================  BSTBegin  =======================*/

bst_iter_t BSTBegin(const bst_t *tree)
{
	assert (NULL != tree);
	return PTR_2_ITER(BSTBeginFromRoot((bst_node_t *)&tree->root_stub));
}


/*====================  BSTGetData  =======================*/
void *BSTGetData(bst_iter_t iter)
{
	return ITER_2_PTR(iter)->data;
}


/*====================  BSTRemove  =======================*/
void BSTRemove(bst_iter_t iter)
{
	bst_node_t *runner = ITER_2_PTR(iter);
			
	if(runner->children[LEFT] != NULL) 
	{
		runner = runner->children[LEFT];
		runner = BSTEndFromRoot(runner);
		
		/*swap between runner and iter*/
		(ITER_2_PTR(iter))->data = runner->data;
		if(IS_LEFT_CHILD(runner))
		{
			(runner->parent)->children[LEFT] = runner->children[LEFT];
		}
		else
		{
			(runner->parent)->children[RIGHT] = runner->children[LEFT]; 
		}
		
		if (NULL != runner->children[LEFT])
		{ 
			(runner->children[LEFT])->parent = runner->parent;
		}
		
		free(runner);
	}
	else if (runner->children[RIGHT] != NULL)
	{
		runner = runner->children[RIGHT];
		runner = BSTBeginFromRoot(runner);
		
		/*swap between runner and iter*/
		(ITER_2_PTR(iter))->data = runner->data;
		
		if(IS_LEFT_CHILD(runner))
		{
			(runner->parent)->children[LEFT] = runner->children[RIGHT]; 
		}
		else
		{
			(runner->parent)->children[RIGHT] = runner->children[RIGHT]; 
		}
		
		if (NULL != runner->children[RIGHT])
		{
			(runner->children[RIGHT])->parent = runner->parent;
		}

		free(runner);
	}
	else			/*0 children to iter */
	{
		if (1 == (IS_LEFT_CHILD(ITER_2_PTR(iter)))) 
		{
			((ITER_2_PTR(iter))->parent)->children[LEFT] = NULL;
		}
		else
		{
			((ITER_2_PTR(iter))->parent)->children[RIGHT] = NULL;
		}
		
		free(ITER_2_PTR(iter));
	}
}

/*====================  BSTPrev  =======================*/
bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_node_t *runner = ITER_2_PTR(iter);
	
	if(NULL != runner->children[LEFT])
	{
		runner = runner->children[LEFT];
		runner = BSTEndFromRoot(runner);
	}
	else
	{
		while(1 == (IS_LEFT_CHILD(runner)))
		{
			runner = runner->parent;
		}
		
		runner = runner->parent;
	}
	
	return PTR_2_ITER(runner);
}

/*====================  BSTNext  =======================*/
bst_iter_t BSTNext(bst_iter_t iter)
{
	bst_node_t *runner = ITER_2_PTR(iter);
	
	if(NULL != runner->children[RIGHT])
	{
		runner = runner->children[RIGHT];
		runner = BSTBeginFromRoot(runner);
	}
	else
	{
		while(0 == (IS_LEFT_CHILD(runner)))
		{
			runner = runner->parent;
		}
		
		runner = runner->parent;
	}
	
	return PTR_2_ITER(runner);
}


/*====================  BSTGetSize  =======================*/

size_t BSTGetSize(const bst_t *tree)
{
	size_t counter = 0;
	bst_iter_t iter = NULL;
	bst_iter_t end = NULL;
	
	assert(NULL != tree);
	
	end = BSTEnd(tree);
	for(iter = BSTBegin(tree); !BSTIsSameIter(iter,end); iter = BSTNext(iter))
	{
		++counter;
	}
	return counter;
}


/*====================  BSTDestroy  =======================*/
void BSTDestroy(bst_t *tree)
{
	bst_iter_t iter = NULL;
	bst_iter_t end = NULL;
	
	assert(NULL != tree);
	
	end = BSTEnd(tree);
	iter = BSTBegin(tree);
	
	while(!BSTIsSameIter(BSTBegin(tree),end))
	{
		BSTRemove(iter);
		iter = BSTBegin(tree);		
	}
	
	free(tree);
	tree = NULL;
}


/*====================  BSTFind  =======================*/
bst_iter_t BSTFind(const bst_t *tree, void *key)
{
	bst_node_t temp = {0};
	bst_iter_t new_node = &temp;
	bst_iter_t runner = NULL;
	bst_node_t *next = NULL;
	int comp_result = 1; /*for first node as left child */
	
	assert(NULL != tree);
	assert(NULL != key);
		
	runner = (PTR_2_ITER(&(tree->root_stub)));
	next = tree->root_stub.children[LEFT];
	
	new_node->data = (void *)key;
	while (NULL != next && 0 != comp_result) 
	{
		comp_result = CompareFuncWraper(tree, runner, new_node);
		if(0 < comp_result)
		{
			next = (ITER_2_PTR(runner))->children[LEFT];
		}
		else if (0 > comp_result)
		{
			next = (ITER_2_PTR(runner))->children[RIGHT];
		}
		
		if (NULL!= next)
		{
			runner = next;
		}
	}
	if (0 != comp_result)
	{
		return BSTEnd(tree);
	}
	else
	{
		return runner;
	}
}

/*====================  BSTForEach  =======================*/

int BSTForEach(bst_iter_t from, bst_iter_t to, int (*action_func)(void *data, void *param), void *param)
{
	int status = 0;
	bst_iter_t runner = from;
	
	assert(NULL != action_func);
	
	while (!BSTIsSameIter(runner,to) && 0 == status)
	{
		status = action_func(BSTGetData(runner), param);
		runner = BSTNext(runner);
	}
	
	return status;
}
