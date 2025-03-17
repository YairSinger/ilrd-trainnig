#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct node
{
    int data;    
    struct node *next;
}node_t;

node_t *AddOneToSll(node_t *head)
{
    node_t *pre_9 = NULL;
    node_t *runner = NULL;
    node_t *last_valid = head;
    node_t *new_head = head;
    

    assert(NULL != head);

    runner = last_valid->next;

    while (NULL != runner)
    {
        if (9 == runner->data)
        {
            if (NULL != pre_9)
            {
                pre_9 = last_valid;
            }
        }
        else
        {
            pre_9 = NULL;
        }
        last_valid = runner;
        runner = runner->next;    
    }

    last_valid->data = (last_valid->data + 1) % 10;

    if(NULL != pre_9)
    {
        if (9 == pre_9->data)
        {
            new_head = (node_t *)malloc(sizeof(node_t));
            if (NULL != new_head)
            {
                new_head->next = pre_9;
                new_head->data = 1;
            }
            else
            {
                return NULL; /*malloc falied*/
            }
        }

        while (pre_9 != last_valid)
        {
            pre_9->data = (pre_9->data + 1) % 10;
            pre_9 = pre_9->next;
        }
    }

    return new_head;
}


node_t *AddOneToSll2(node_t *head)
{
    node_t *first_9 = NULL;
    node_t *runner = head;
    node_t *new_head = head;
    
    assert(NULL != head);

    while (NULL != runner) /*finding first 9 */
    {
      if (9 == runner->data)
        {
            if (NULL == first_9)
            {
                first_9 = runner;
            }
        }
        else
        {
            first_9 = NULL;
        }

        runner = runner->next;
    }

    if (NULL == first_9)
    {
        runner = head;
         while (NULL != runner->next)
         {
            runner = runner->next;
         }
        runner->data += 1;
    }
    else
    {
        if (head == first_9)
        {
            new_head = (node_t *)malloc(sizeof(node_t));
            if (NULL != new_head)
            {
                new_head->next = first_9;
                new_head->data = 1;
            }
            else
            {
                return NULL; /*malloc falied*/
            }
            runner = new_head;
        }
        else
        {
            runner = head;
        }

        while (first_9 != runner->next && NULL != runner->next)
         {
            runner = runner->next;
         }
        runner->data = (runner->data + 1 ) % 10;
        runner = runner->next;
        while (NULL != runner)
         {
            runner->data = 0;
            runner = runner->next;
         }

    }
    return new_head;
}
void PrintSll(node_t *head)
{
    while(NULL != head)
    {
        printf("%d\n", head->data);
        head = head->next;
    }
}

node_t *Flip(node_t *head)
{
	node_t *prev = NULL;
	node_t *next = head->next;
		
	while (head != NULL)
	{
		next = head->next;
		head->next = prev;
		
		prev = head;
		head = next;
	}
	
	return prev;
}

node_t *AddOneToSll3(node_t *head)
{
	node_t *runner = NULL;
	node_t *new_node = NULL;
	node_t *prev = NULL;
	head = Flip(head);
	
	runner = head;
	do
	{
		prev = runner; 
		runner->data = (runner->data + 1) % 10;
		runner = runner->next;
	}while(runner != NULL && 0 == prev->data);
	
	if(runner == NULL && 0 == prev->data)
	{
		new_node = (node_t *)malloc(sizeof(node_t));
		if (NULL == new_node)
		{
			return NULL;
		}
		
		new_node->data = 1;
		new_node->next = NULL;
		prev->next = new_node;
	}
	
	head = Flip(head);
	return head;
}


int main()
{
    node_t nodes[4] = {0};
    node_t *result = NULL;

    nodes[0].data = 9;
    nodes[0].next = NULL;

    nodes[1].data = 9;
    nodes[1].next = &nodes[2];

    nodes[2].data = 9;
    nodes[2].next = &nodes[3];

    nodes[3].data = 9;
    nodes[3].next = NULL;

    result = AddOneToSll3(nodes);

    PrintSll(result);


    return 0;
}
