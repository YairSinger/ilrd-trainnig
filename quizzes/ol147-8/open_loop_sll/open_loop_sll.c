#include <stdlib.h>
#include <stdio.h> 	/* printf */
#include "sll.h"

int IsListOpen(sll_iter_t head)
{
	sll_iter_t fast = head;
	sll_iter_t slow = head;
	
	assert(NULL != head);
	
	fast = fast->next;
	
	while (NULL != fast && NULL != fast->next && fast != slow)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	
	return (!(fast == slow));
}


sll_iter_t OpenLoopedList(sll_iter_t head)
{
	sll_iter_t fast = head;
	sll_iter_t slow = head;
	
	assert(NULL != head);
	assert(!IsOpen(head));
	
	fast = fast->next;
	/*find looped node distant from intersection the same number as from head*/ 
	while (fast != slow)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	
	fast = head; 
	
	/*find intersection and stop with slow at last node*/
	while (slow->next != fast->next)
	{
		slow = slow->next; /
		fast = fast->next;
	}
	
	slow->next = NULL;
	return head; 
}


