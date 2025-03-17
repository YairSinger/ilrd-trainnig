#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	void *data;
	struct node *next;
} node_t;

node_t *FindTheNthElelment(node_t *head, size_t nth)
{
	size_t i = 0;
	size_t *queue_buffer = (size_t *) calloc (nth +1, sizeof(size_t));
	node_t *runner = head;
	node_t *result = NULL;
	if (NULL == queue_buffer)
	{
		return NULL;
	}
	
	for (i = 0; runner != NULL; runner = runner->next, i = ((i+1) % (nth + 1)))
	{
		*(queue_buffer + i) = (size_t)runner;
	}
	
	if (0 == *(queue_buffer + nth)) /*nth is bigger than list length */
	{
		free(queue_buffer); 
		return NULL;
	}
	
	result =(node_t *)*(queue_buffer + i);
	free(queue_buffer); 
	return (result);
}

void Find(node_t *head, size_t nth, size_t *counter, node_t **res)
{
		
	if (NULL != head->next)
	{
		Find(head->next, nth, counter, res);
	}
	
	
	if(nth == *counter && NULL == *res)
	{
		*res = head;		
	}
	else
	{
		*counter += 1;
	}
}



node_t *FindTheNthElelment2(node_t *head, size_t nth)
{
	size_t counter = 0;
	node_t *res = NULL;
	Find(head, nth,&counter,&res);
	
	return res;

}


int main()
{
	int arr[] = {5,4,3,2,1};
	node_t a = {NULL, NULL};
	node_t b = {NULL, NULL};
	node_t c = {NULL, NULL};
	node_t d = {NULL, NULL};
	node_t e = {NULL, NULL};
	node_t * res = NULL;
	
	
	a.data = (void *) arr;
	b.data =(void *) (arr + 1);
	c.data =(void *) (arr + 2);
	d.data =(void *) (arr + 3);
	e.data = (void *) (arr + 4);
	
	a.next = NULL;
	b.next = &a;
	c.next = &b;
	d.next = &c;
	e.next = &d;
	res = FindTheNthElelment2(&e, 0);
	printf("0 from end is%d\n",*((int *)res->data));
	res = FindTheNthElelment2(&e, 1);
	
	printf("1 from end is%d\n",*((int *)res->data));
	res = FindTheNthElelment2(&e, 2);
	
	printf("2 from end is%d\n",*((int *)res->data));
	res = FindTheNthElelment2(&e, 3);
	
	printf("3 from end is%d\n",*((int *)res->data));
	res = FindTheNthElelment2(&e, 4);
	
	printf("4 from end is%d\n",*((int *)res->data));


	return 0;
}
