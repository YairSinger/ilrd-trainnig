#include <assert.h>
#include <stddef.h> 	/* size_t 			*/
#include <stdlib.h> 	/* malloc 			*/
#include <assert.h> 
#include "dll.h"


#define ITER_2_NODE_PTR (struct node *)
#define NODE_PTR_2_ITER (dll_iter_t)


struct node
{
	void *data;
	struct node *prev;
	struct node *next;
};

struct dll
{
	struct node begin;
	struct node end; 
};

dll_t *DllCreate(void)
{
	dll_t *dll = (dll_t *) malloc(sizeof(dll_t));
	
	if (NULL == dll)
	{	
		return NULL;
	}
	dll->begin.data = NULL;
	dll->begin.prev = NULL;
	dll->begin.next = &(dll->end);
	
	dll->end.data = NULL;
	dll->end.prev = &(dll->begin);
	dll->end.next = NULL;
	
	return dll;
}

void DllDestroy(dll_t *dll)
{
	assert(NULL != dll);
	
	while (!DllIsEmpty(dll))
	{
		DllRemove(DllBegin(dll));
	}
	
	dll->begin.data = NULL;
	dll->begin.prev = NULL;
	dll->begin.next = NULL;
	
	dll->end.data = NULL;
	dll->end.prev = NULL;
	dll->end.next = NULL;	
	
	free(dll);
}
/**************************************************************************/


dll_iter_t DllInsert(dll_t *dll, const dll_iter_t where, const void *data)
{
	struct node *new_node = NULL;
	struct node *where_ptr = NULL;
	
	assert(NULL != dll);
	assert(NULL != ITER_2_NODE_PTR (where));
	
	where_ptr = ITER_2_NODE_PTR (where);
	new_node = (struct node *) malloc (sizeof(struct node));
	
	if (NULL == new_node)
	{
		return DllEnd(dll);
	}
	new_node->data = (void *) data;
	new_node->prev = where_ptr->prev;
	new_node->next = where_ptr;
	
	new_node->prev->next = new_node;
	where_ptr->prev = new_node;
	
	
	return NODE_PTR_2_ITER (new_node);
}
/********************************************************************/


dll_iter_t DllRemove(dll_iter_t who)
{
	struct node * prev_node = NULL;
	struct node * next_node = NULL;
	
	assert(NULL != ITER_2_NODE_PTR (who));
	
	prev_node = (ITER_2_NODE_PTR (who))->prev;
	next_node = (ITER_2_NODE_PTR (who))->next;
	
	prev_node->next = next_node;
	next_node->prev = prev_node;
	
	free(ITER_2_NODE_PTR (who));
	
	return NODE_PTR_2_ITER(next_node);
}
/*********************************************************************/


size_t DllSize(const dll_t *dll)
{
	dll_iter_t i = NULL;
	dll_iter_t end = NULL;
	size_t counter = 0;
	
	assert(NULL != dll);
	for(i = DllBegin(dll),end = DllEnd(dll); !DllIsSameIter(i,end); i = DllNext(i))
	{
		++counter;
	}
	
	return counter;	
}

/******************************************************************/


void *DllGetData(const dll_iter_t iter)
{
	assert(NULL != ITER_2_NODE_PTR (iter));
	
	return (ITER_2_NODE_PTR (iter))->data;
}

/********************************************************************/


int DllIsEmpty(const dll_t *dll)
{
	assert(NULL != dll);
	return DllIsSameIter(DllBegin(dll), DllEnd(dll));
}


/*******************************************************************/

void DllSetData(dll_iter_t iter, const void *data)
{
	assert(NULL != ITER_2_NODE_PTR (iter));
	
	(ITER_2_NODE_PTR (iter))->data =(void *) data;	
}

/********************************************************************/

int DllIsSameIter(const dll_iter_t iter1, const dll_iter_t iter2)
{
	assert(NULL != 	ITER_2_NODE_PTR (iter1));
	assert(NULL != 	ITER_2_NODE_PTR (iter2));
	
	return (ITER_2_NODE_PTR (iter1) == ITER_2_NODE_PTR (iter2));
}

/********************************************************************/

dll_iter_t DllBegin(const dll_t *dll)
{
	assert(NULL != dll);
	
	return NODE_PTR_2_ITER ((dll->begin.next));
}

/********************************************************************/

dll_iter_t DllEnd(const dll_t *dll)
{
	assert(NULL != dll);
	
	return NODE_PTR_2_ITER (&(dll->end));
}

/*******************************************************************/

dll_iter_t DllPrev(dll_iter_t iter)
{
	assert(NULL != ITER_2_NODE_PTR (iter));
	
	return NODE_PTR_2_ITER((ITER_2_NODE_PTR (iter))->prev);
}

/*******************************************************************/


dll_iter_t DllNext(dll_iter_t iter)
{
	assert(NULL != ITER_2_NODE_PTR (iter));
	
	return NODE_PTR_2_ITER((ITER_2_NODE_PTR (iter))->next);
}


/*********************************************************/
dll_iter_t DllPushBack(dll_t *dll, const void *data)
{
	assert(NULL != dll);
	return DllInsert(dll, DllEnd(dll), data);	
}

/********************************************************************/

dll_iter_t DllPushFront(dll_t *dll, const void *data)
{
	assert(NULL != dll);
	
	return DllInsert(dll, DllBegin(dll), data);
}

/*******************************************************************/

void *DllPopBack(const dll_t *dll)
{
	void *data = NULL;
	
	assert(NULL != dll);
	
	data = DllGetData(DllPrev(DllEnd(dll)));
	DllRemove(DllPrev(DllEnd(dll)));
	return data;
}

/*****************************************************************/
void *DllPopFront(const dll_t *dll)
{
	void *data = NULL;
	
	assert(NULL != dll);
	
	data = DllGetData(DllBegin(dll));
	DllRemove(DllBegin(dll));
	return data;	
}


/************************************************************/
dll_iter_t DllFind(const dll_iter_t from, const dll_iter_t to, const is_match_func is_match, const void *param)
{
	dll_iter_t runner;
	assert(NULL != ITER_2_NODE_PTR(from));
	assert(NULL != ITER_2_NODE_PTR(to));
	assert(NULL != is_match);
	
	runner = from;
	

	while (!DllIsSameIter(runner, to) && !is_match(runner->data, param))
	{
		runner = DllNext(runner);
	}
	
	return runner;
}

/************************************************************/


int DllMultiFind(const dll_iter_t from, const dll_iter_t to , const is_match_func is_match, const void *param, dll_t *out_dll){
	int res = 0;
	dll_iter_t find_res = from;
	dll_iter_t push_res = NULL;
	
	
	while (!DllIsSameIter(find_res = DllFind(find_res, to,is_match, param), to) && 0 == res )/*stops when fails to insert to lls out */
	{
		
		push_res = DllPushBack(out_dll,(const void *) DllGetData(find_res));
		res = DllIsSameIter(push_res,DllEnd(out_dll));
		find_res = DllNext(find_res);
	}
	
	return res;

}

/**************************************************************/

int DllForEach(dll_iter_t from, const dll_iter_t to, const action_func action, const void *param)
{
	dll_iter_t iter = NULL;
	int action_status = 0;
	
	iter = ITER_2_NODE_PTR(from);
	
	assert(NULL != ITER_2_NODE_PTR(from));
	assert(NULL != ITER_2_NODE_PTR(to));
	assert(NULL != action);
	
	while(0 == action_status && !DllIsSameIter(iter,ITER_2_NODE_PTR(to)))
	{
		action_status = action((ITER_2_NODE_PTR(iter))->data,(void *) param);
		iter = DllNext(iter);
	}
	
	return action_status;
}

/*************************************************************/

void DllSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to)
{
	struct node *where_p = ITER_2_NODE_PTR(where);
	struct node *from_p = ITER_2_NODE_PTR(from);
	struct node *to_p = ITER_2_NODE_PTR(to);
	struct node *where_prev_holder = NULL;
	struct node *to_prev_holder = NULL;
	
	assert(NULL != where_p);
	assert(NULL != from_p);
	assert(NULL != to_p);
	
	where_prev_holder = where_p->prev;
	to_prev_holder = to_p->prev;
	
	/*linkin new nodes to where */
	where_p->prev->next = from_p;
	where_p->prev = to_p->prev;

	/*cutting loose from-to from old list */
	from_p->prev->next = to_p; 
	to_p->prev = from_p->prev;
	
	/*updating from's and to's new neighbors*/
	from_p->prev = where_prev_holder;
	to_prev_holder->next = where_p;
}
	
