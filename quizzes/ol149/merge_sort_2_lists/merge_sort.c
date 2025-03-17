#include <assert.h>
#include <stdlib.h> /*calloc */
#include <stdio.h>


typedef struct node
{
	int data;
	struct node *next;
}node_t;

static void Split(node_t *head1, node_t *head2, size_t count)
{
	node_t *new_end = NULL;
	size_t i = 0;
	head2 = head1;
	
	for (i = 0; i < (count/2 - 1); ++i)
	{
		head2 = head2->next;
	}
	
	new_end = head2;
	head2 = head2->next;
	new_end->next = NULL;
}



static node_t *Merge(node_t *head1, node_t *head2)
{
	node_t *run1 = head1;
	node_t *run2 = head2;
	node_t res = {0};
	node_t *res_ptr = &res;
	
	while (NULL != run1->next && NULL != run2->next)
	{
		if (run1->data < run2->data)
		{
			res_ptr->next = run1;
			res_ptr = run1;
			run1 = run1->next;
		}
		else
		{
			res_ptr->next = run2;
			res_ptr = run2;
			run2 = run2->next;
		}
	}
	
	NULL == run1->next ? (res_ptr->next) = run2 : (res_ptr->next) = run1;
	
	return res.next;
}



static node_t *MergeSortRec(node_t *head)
{
	size_t count = 1;
	node_t *head2 = head;
	
	while (NULL != head2->next)
	{
		++count;
		head2 = head2->next;
	} 
	
	if(count > 1)
	{
		Split(head, head2,count);
		
		head = MergeSortRec(head);
		head2 = MergeSortRec(head2);
		return Merge(head, head2);		
	}
	else
	{
		return head;
	}
}



node_t *MergeSort(node_t *head1, node_t *head2)
{
	node_t *holder = head1;
	while(NULL != head1->next)
	{
		head1 = head1->next;
	}
	
	head1->next = head2;
	
	return MergeSortRec(holder);	
}

static node_t *CreatNode(int value_in_node)
{
	node_t *new = (node_t *)malloc(sizeof(node_t));
	new->data = value_in_node;
	return new;
}

int main()
{
	size_t i = 0;
	node_t *head1 = NULL, *head2 = NULL;
	node_t *temp = NULL;
	
	head1 = CreatNode(1);
	head1->next = CreatNode(5);
	head1->next->next = CreatNode(2);
	
	head2 = CreatNode(4);
	head2->next = CreatNode(9);
	head2->next->next = CreatNode(8);
	 
	head1 = MergeSort(head1, head2);
	while (NULL != head1)
	{
		printf("%d", head1->data);
		temp = head1;
		head1 = head1->next;
		free(temp);
	}	
	
	return 0;
}
