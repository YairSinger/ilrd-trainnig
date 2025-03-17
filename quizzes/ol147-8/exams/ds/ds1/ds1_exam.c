
#define WORD sizeof(size_t)



typedef struct node_sll
{
	void *data
	struct node_sll *next;
}node_t;

typedef struct node_dll
{
	void *data
	struct node_dll *prev;
	struct node_dll *next;
}dll_node_t;

void FsaAlloc(fsa_t *fsa)
{
	void *alloc = NULL;
	
	assret(NULL != fsa);
	
	if (0 == fsa->next_free)
	{
		return NULL;
	}
	
	alloc = (void *)((char *)fsa + fsa->next_free);
	fsa->next_free = *((size_t)alloc);
	return alloc;

}


void FsaFree(fsa_t *fsa, void *block)
{
	assert(NULL 1= fsa);
	if(fsa->magic_number != 0xdabb1e)
	{
		return;
	}
	
	*((size_t)block) = fsa->next_free;
	fsa->next_free = ((char *)block - (char *)fsa);
}


#define WORD sizeof(size_t)
#define IS_FREE(run) 0 != (((header_t *)(run))->size & 1)
#define PURE_SIZE(run) (((header_t *)(run))->size & ~1)
#define IS_LAST(runner, vsa) (runner - ((char *)vsa + sizeof(vsa_t))  + PURE_SIZE(runner)) == vsa->pool_size
#define NEXT_BLOCK(runner) (char *)runner + sizeof(header_t) + ((header_t *)runner)->block_size

void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	char *first_header = NULL;
	char*runner = NULL;
	size_t size_holder = 0;
	
	assert(NULL != vsa);
	
	/*round up block_size to word size allignment*/
	block_size = block_size % WORD == 0 ? block_size : WORD *((block_size/WORD)+ 1));
	runner = (char *)vsa + sizeof(vsa_t) ;
	first_header = runner;
	
	while(runner - first_header + PURE_SIZE(runner) <= vsa->pool_size)
	{
		if (IS_FREE(runner) && PURE_SIZE(runner) >= block_size)
		{
			size_holder = PURE_SIZE(runner) - sizeof(header_t) - block_size;
			((header_t *)runner)->block_size = block_size + 1; 	/*signed as alloced block*/
			if(size_holder >= sizeof(header_t))
			{
				*((size_t *)run + block_size + sizeof(header_t)) = size_holder;
			}
			
			runner -= sizeof(header_t);
			return runner;
		}
		else if(IS_FREE(runner) && !IS_LAST(runner, vsa) && IS_FREE(NEXT_BLOCK(runner)))
		{
			Defrag(runnner);
		}
		
		runnner = NEXT_BLOCK(runner);
	}
	
	return NULL;	
}

void VSAFree(void *block)
{
	assert (NULL != block);
	
	((header_t)((char *)block-sizeof(header_t)))->block_size -= 1; 
}


/***************  ex 2  **************************/

node_t *Flip(node_t *head)
{
	node_t *prev = NULL;
	node_t *next = head->next;
		
	while(head != NULL)
	{
		next = head->next;
		head->next = prev;
		
		prev = head;
		head = next;
	}
	
	return prev;
}

/***************  ex 4  **************************/
node_t *HasLoop(node_t *head)
{
	node_t *fast = head->next;
	node_t *slow = head;
  
	while(fast != slow && NULL != fast && NULL != fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	
	if(fast == slow)
	{
		return fast;
	}
	return NULL;
}

void OpenLoop(node_t *head)
{
	node_t *run1 = head;
	node_t *run2 = head;
	
	run1 = HasLoop(head);
	
	if (NULL != run1)
	{
		while (run1 != run2->next) 
		{
			run1 = run1->next;
			run2 = run2->next;
		}
		
		run1->next = NULL;
	}
}

/***************  ex 5  **************************/


int HasIntersection(node_t *head1, node_t *head2)
{
	node_t *run1 = head1;
	node_t *run2 = head2;
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	while(run1 != run2)
	{
		run1 = (NULL == run1) ? head2 : run1->next;
		run2 = (NULL == run2) ? head1 : run2->next;
	}
	
	return (NULL != run1);
}



node_t *FindIntersection(node_t *head1, node_t *head2)
{
	node_t *run1 = head1;
	node_t *run2 = head2;
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	while(run1 != run2)
	{
		run1 = (NULL == run1) ? head2 : run1->next;
		run2 = (NULL == run2) ? head1 : run2->next;
	}
	
	return run1;
}


void SeparateTwoSll(node_t *head1, node_t *head2)
{
	node_t intersection = FindIntersection(head1,head2);
	
	if (NULL == intersection)
	{
		return;
	}
	
	if(head1 != intersection)
	{
		while (head1->next != intersection)
		{
			head1 = head1->next;
		}
		
		head1->next = NULL;
		return;
	}
	else if (head2 != intersection)
	{
		while (head2->next != intersection)
		{
			head2 = head2->next;
		}
		
		head2->next = NULL;
		return;
	}
	
}

/***************  ex 6  **************************/
node_t *RemoveNode(node_t *node)
{
	node_t *temp = node->next;
	node->data = temp->data;
	node->next = temp->next;
	
	free(temp);
	temp = NULL;
	
	return node;
}

/***************  ex 7  **************************/
int InsertBefore(dll_node_t *before, void *data)
{
	dll_node_t *new = NULL; 
	
	assert(NULL != before);

	new = (dll_node_t *)malloc(sizeof(dll_node_t));

	if (NULL != new)
	{
		new->data = data;
		new->prev = before->prev;
		new->next = before;
		
		(new->prev)->next = new;
		before->prev = new;
		return 0;	
	}
	
	return 1;
}

Void RemoveNode (dll_node_t *remove)
{
	assret (NULL != remove);
	
	(remove->prev)->next = remove->next;
	(remove->next)->prev = remove->prev;
	
	free(remove);
	remove = NULL;
}

/***************  ex 8  **************************/

size_t FindMissingNum(size_t arr[])
{
	size_t i = 0;
	size_t length = 1024;
	size_t res = 0;
	size_t expected = ((length + 1) * (0 + 1024)) / 2;

	for (i = 0; i < length; ++i)
	{
		res += arr[i];
	}
	
	return (expected - res);
}


/***************  ex 9 **************************/

typedef struct point
{
	int x;
	int y;
} point_t;

int IsInShape(int **bitmap, point_t p)
{
	int is_in = 0;
	
	if (bitmap[p.x][p.y])
	{
		return 1;
	}
	
	while (p.x > 0)
	{
		if (bitmap[p.x][p.y])
		{
			is_in = !is_in;
		}
		
		--p.x;
	}
	
	return is_in;
}

/***************  ex 10  **************************/
int QueuePushChar(queue_t *queue, char c) 
{
	 assert(NULL != queue);
	 
	 if(queue->m_elements_in_q == Q_SIZE)
	 {
	 	return 1;
	 }
	
	 queue->m_queue[(queue->m_first_index + queue->m_elements_in_q) % Q_SIZE] = c;
	 queue->m_elements_in_q += 1;
	 return 0;
}
int QueuePopChar(queue_t *queue)
{
	assert (NULL != queue);
	
	if(0 == queue->m_elements_in_q)
	{
		return 1;
	}
	
	queue->m_first_index = (queue->m_first_index + 1) % Q_SIZE;
	queue->m_elements_in_q -= 1;
	return 0;
}



