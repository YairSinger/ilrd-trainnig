#include <assert.h>
#include <stdlib.h> /* malloc  */
#include <stddef.h> /* size_t  */
#include "sll.h"

typedef struct node
{
	void *data;
	struct node *next;
}node_t;

struct sll
{
	sll_iter_t head;
	sll_iter_t tail;
};


sll_t *SllCreate(void)
{
	sll_t  *sll =( sll_t *) malloc(sizeof(sll_t));
	
	if (NULL == sll)
	{
		return NULL;
	}
	
	/*use calloc for dummy to set NULL in all members */	
	sll->head = (sll_iter_t) calloc (1,sizeof(node_t));
	
	if (NULL == sll->head)
	{
		free (sll);
		return NULL;
	}	
	
	sll->tail = sll->head;
	return sll;	
}












void SllDestroy(sll_t *sll)
{
		
	assert(NULL != sll);
	
	while(!SllIsSameIter(SllBegin(sll),SllEnd(sll)))
	{
		SllRemove(sll, SllBegin(sll));
	}
	
	free(SllBegin(sll)); /*remove dummy node*/
	sll->head = NULL;
	sll->tail = NULL;
	
	free(sll);
	sll = NULL;
}











sll_iter_t SllInsert(sll_t *sll, sll_iter_t where, const void *data)
{
	sll_iter_t new_node = (sll_iter_t) malloc(sizeof(node_t));
	
	assert(NULL != sll);
	assert(NULL != data);
	
	if (NULL == new_node)
	{
		return SllEnd(sll);
	}
	
	new_node->next = where->next;
	new_node->data = where->data;
	
	where->next = new_node;
	where->data = (void *) data;
	
	if(SllIsSameIter(where, SllEnd(sll)))/*if writing before end */
	{
		/*updat tail that new_node became dummy node*/
		sll->tail = new_node;
	}
	
	return where;
}









sll_iter_t SllRemove(sll_t *sll, sll_iter_t who)
{
	sll_iter_t next_holder = NULL;
	
	assert(!SllIsSameIter(who, SllEnd(sll)));
	
	next_holder = who->next; /*copy from next_holder before remove*/
	who->next = next_holder->next;
	who->data = (void *) next_holder->data;
	
	if (SllIsSameIter(next_holder, SllEnd(sll)))/*update tail if dummy moves to head */
	{
		sll->tail = who;
	}
	
	free(next_holder);
	next_holder = NULL;
	return who;

}



int SllIsEmpty(sll_t *sll)
{
	assert(NULL != sll);
	return (sll->head == sll->tail);
}





size_t SllCount(const sll_t *sll)
{
	sll_iter_t i = NULL;
	size_t counter = 0;
	
	assert(NULL != sll);
	
	for (i = SllBegin(sll); !SllIsSameIter(i, SllEnd(sll)); i = SllNext(i))
	{
		++counter;
	}
	return counter;
}









void *SllGetData(sll_iter_t iter)
{
	assert(NULL != iter);
	return (void *) iter->data;
}






void SllSetData(sll_iter_t iter, void *data)
{
	assert(NULL != iter);
	iter->data = data;
}






sll_iter_t SllBegin(const sll_t *sll)
{
	assert(NULL != sll);
	return sll->head;
}





sll_iter_t SllNext(sll_iter_t iter)
{
	assert(NULL != iter);
	return iter->next;
}





sll_iter_t SllEnd(const sll_t *sll)
{
	assert(NULL != sll);
	return sll->tail;
}





int SllIsSameIter(sll_iter_t iter1, sll_iter_t iter2)
{
	return (iter1 == iter2);
}






sll_iter_t SllFind(sll_iter_t from, sll_iter_t to , int (*match_func)(const void *lhs, const void *rhs), const void *rhs)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	
	while(!SllIsSameIter(from,to) && !match_func(from->data, rhs))
	{
		from = SllNext(from);
	}
	
	return from;
}












int SllForEach(const sll_t *sll, int (*action_func)(void *data, void *param), void *param)
{
	sll_iter_t iter = NULL;
	int action_status = 0;
	size_t counter = 0;
	
	assert(NULL != sll);
	assert(NULL != action_func);
	
	
	iter = SllBegin(sll);
	while(0 == action_status && !SllIsSameIter(iter,SllEnd(sll)))
	{
	
		action_status = action_func(iter->data, param);
		iter = SllNext(iter);
		++counter;
	}
	
	if (0 == action_status)
	{	
		return 0;
	}
	else 
	{
		 return counter;
	}
}





void SllAppend(sll_t *dest, sll_t *src)
{
	sll_iter_t end_dest = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	/*if src is empty*/
	if (src->head == src->tail)
	{
		return;
	}
	
	end_dest = SllEnd(dest);
	
	end_dest->next = SllBegin(src)->next;
	end_dest->data = SllBegin(src)->data;
	
	dest->tail = src->tail;
	src->tail = src->head;
	src->head->data = NULL;
	src->head->next = NULL;	
}




/**************************************************************************/
/*
sll_iter_t SllFlip(sll_iter_t head)
{
	sll_iter_t pre = NULL;
	sll_iter_t cur = NULL;
	sll_iter_t nex = NULL;
	
	size_t sll_len = 0;
	size_t i = 0;
	
			
	assert(NULL != head);
	
	sll_len = SllCountFromIter(head, &pre);
	cur = head;
	nex = SllNext(head);
	
	for(i = 0; i <  sll_len - 1; ++i)
	{
		cur->next = pre;
		pre = cur;
		cur = nex;
		nex = SllNext(nex);
	}
	
	cur->next = pre;
	return cur;
}*/
/*********************************************************************/
/*sll_iter_t FindIntersection(sll_iter_t head1,sll_iter_t head2)
{
	size_t len1 = 0;
	size_t len2 = 0;
	sll_iter_t run1 = NULL;
	sll_iter_t run2 = NULL;
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	len1 = SllCountFromIter(head1, &run1);
	len2 = SllCountFromIter(head2, &run2);
		
	while (len1 > len2) /*move runners the same distance from end */
	/*{
		head1 = SllNext(head1);
		--len1;
	}
	
	while (len1 < len2)
	{
		head2 = SllNext(head2);
		--len2;
	}
	
	
	while (head1 != run1 && head1 != head2 ) /*run1 points on end of head1 */
	/*{
	/*	head1 = SllNext(head1);
		head2 = SllNext(head2);
	}
	
	return head1;
}
/**********************************************************************/
/*
size_t SllCountFromIter(sll_iter_t from,sll_iter_t *end_location)
{

	size_t counter = 0;
	
	while (NULL != from->next)
	{
		++counter;
		from = SllNext(from);
	}
	
	*end_location = from;
	return counter;
}
*/
/****************************************************************************/
/*void PrependList(sll_t *sll,sll_iter_t prepend_to)
{
	sll_iter_t last_valid_node = NULL;
	sll_iter_t iter = NULL;
	
	assert(NULL != sll);
	assert(NULL != prepend_to);
	
	iter = SllBegin(sll);
	iter = SllNext(iter);
	last_valid_node = SllBegin(sll);
	
	
	while(NULL != iter->next)
	{
		iter = SllNext(iter);
		last_valid_node = SllNext(last_valid_node);
	}
	
	last_valid_node->next = prepend_to;	
}
	
/*************************************************************************/

/*int HasLoop (const sll_iter_t head)
{
	sll_iter_t front_iter = NULL;
	sll_iter_t rear_iter = NULL;

	
	rear_iter = head;
	front_iter = SllNext(head);

	
	while (NULL != front_iter && NULL != front_iter->next && front_iter != rear_iter)
	{
		rear_iter = SllNext(rear_iter);
		front_iter = SllNext(front_iter);
		front_iter = SllNext(front_iter);
	}
	return (front_iter == rear_iter);
}	
	*/

