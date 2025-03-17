#include <stdio.h>
#include <sys/types.h>
#include "ds1_exam.c"

#define Q_SIZE 5

const int N = 10;
const int M = 10;

void TestFindMissingNum();
void TestIsInShape();
void TestQueueFuncs();
void TestHasIntersection();

typedef struct node node_t;
struct node
{
	void *data;
	node_t *next;
};

typedef struct queue
{
	char m_queue[Q_SIZE];
	size_t m_elements_in_q;
	size_t m_first_element_index;
}queue_t;

void OpenLoop(node_t *head);


int main()
{
	node_t node1, node2, node3, node4, node5, node6, node7, node8, node9, node10;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8, i = 9, j = 10;
	node_t *head = &node1;
	
	node1.data = &a;
	node1.next = &node2;	
	node2.data = &b;
	node2.next = &node3;
	node3.data = &c;
	node3.next = &node4; 
	node4.data = &d;
	node4.next = &node5;
	node5.data = &e;
	node5.next = &node6;
	node6.data = &f;
	node6.next = &node7;
	node7.data = &g;
	node7.next = &node8;
	node8.data = &h;
	node8.next = &node9;
	node9.data = &i;
	node9.next = &node10;
	node10.data = &j;
	node10.next = &node1;
	
	
	OpenLoop(head);
	
	printf("[ ");
	while(head != NULL)
	{
		printf("%d -> ", *((int *) (head->data)));
		head = head->next;
	}
	printf("NULL]\n");
	
	/**********end of open loop test */
	
	
	TestFindMissingNum();
/*	TestIsInShape();*/
	TestQueueFuncs();
	TestHasIntersection();
	TestSeparateTwoSll();
	
	return 0;
}

/* #1 in git/system_programming/src/fsa.c or vsa.c */

/* #2 in git/ds/src/sll/sll_exe.c */

/* #3 in notebook */

/* #4 in git/ds/src/sll/sll_exe.c and git/quizzes/quiz22.c */

/* #5 in git/quizzes/quiz24.c */

/* #6 in git/ds/src/sll/sll.c */

/* #7 in git/ds/src/dll/dll.c */

/* #8 */
int FindMissingNum(int arr[])
{
	int sum = 1024 * 1025 / 2;
	size_t i = 0;
	
	for (i = 0; i < 1024; ++i)
	{
		sum -= arr[i];
	}
	
	return sum;
}

void TestFindMissingNum()
{
	int arr[1024] = {0};
	int missing = 0;
	size_t i = 0;
	size_t flag = 0;
	
	printf("\nTEST FindMissingNum:\n\n");
	
	missing = 789;
	for (i = 0; i < 1025; ++i)
	{
		if (i == missing)
		{
			flag = 1;
		}
		else
		{
			arr[i - flag] = i;
		}
	}
	printf("%d\n", missing == FindMissingNum(arr));
	
	flag = 0;
	missing = 99;
	for (i = 0; i < 1025; ++i)
	{
		if (i == missing)
		{
			flag = 1;
		}
		else
		{
			arr[i - flag] = i;
		}
	}
	printf("%d\n", missing == FindMissingNum(arr));
	
	flag = 0;
	missing = 1024;
	for (i = 0; i < 1025; ++i)
	{
		if (i == missing)
		{
			flag = 1;
		}
		else
		{
			arr[i - flag] = i;
		}
	}
	printf("%d\n", missing == FindMissingNum(arr));
	
	flag = 0;
	missing = 0;
	for (i = 0; i < 1025; ++i)
	{
		if (i == missing)
		{
			flag = 1;
		}
		else
		{
			arr[i - flag] = i;
		}
	}
	printf("%d\n", missing == FindMissingNum(arr));
}


/* #9 */
int IsInShape(int bit_map[N][M], size_t row, ssize_t column)
{
	size_t counter = 0;
	
	if (1 == bit_map[row][column])
	{
		return 1;
	}
	else
	{
		--column;
	}
	
	for ( ; column >= 0; --column)
	{
		if (1 == bit_map[row][column] &&
			0 == bit_map[row][column + 1])
		{
			++counter;
		}
	}
	
	return 1 == (counter & 1);
}		

void TestIsInShape()
{
	int bit_map[10][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						   {0, 1, 1, 1, 0, 0, 0, 1, 0, 0},
						   {0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
						   {0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
						   {0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
						   {0, 1, 0, 1, 1, 1, 0, 0, 0, 1},
						   {0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
						   {0, 1, 0, 1, 0, 1, 0, 1, 0, 0},
						   {0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
						   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

	printf("\nTEST IsInShape:\n\n");
	
	printf("%d\n", 0 == IsInShape(bit_map, 0, 0));
	printf("%d\n", 1 == IsInShape(bit_map, 6, 6));
	printf("%d\n", 1 == IsInShape(bit_map, 4, 8));
	printf("%d\n", 0 == IsInShape(bit_map, 8, 7));
	printf("%d\n", 1 == IsInShape(bit_map, 3, 9));
}
	
/* #10 */



int QueuePushChar(queue_t *queue, char c)
{
	size_t index = 0;
	
	if (Q_SIZE == queue->m_elements_in_q)
	{
		return 1;
	}
	
	index = (queue->m_first_element_index +
			 queue->m_elements_in_q) %
			 Q_SIZE;
	queue->m_queue[index] = c;
	++queue->m_elements_in_q;
	
	return 0;
}

int QueuePopChar(queue_t *queue)
{
	if (0 == queue->m_elements_in_q)
	{
		return 1;
	}
	
	queue->m_first_element_index = (queue->m_first_element_index + 1) % Q_SIZE;
	--queue->m_elements_in_q;
	
	return 0;
}

void TestQueueFuncs()
{
	queue_t queue;
	
	printf("\nTEST QueueFuncs:\n\n");
	
	queue.m_elements_in_q = 0;
	queue.m_first_element_index = 0;
	
	QueuePushChar(&queue, 'N');
	printf("%d\n", 1 == queue.m_elements_in_q && 0 == queue.m_first_element_index);
	QueuePushChar(&queue, 'o');
	printf("%d\n", 2 == queue.m_elements_in_q && 0 == queue.m_first_element_index);
	QueuePushChar(&queue, 'a');
	printf("%d\n", 3 == queue.m_elements_in_q && 0 == queue.m_first_element_index);
	QueuePushChar(&queue, 'm');
	printf("%d\n", 4 == queue.m_elements_in_q && 0 == queue.m_first_element_index);
	QueuePushChar(&queue, '!');
	printf("%d\n", 5 == queue.m_elements_in_q && 0 == queue.m_first_element_index);
	QueuePushChar(&queue, '!');
	printf("%d\n", 5 == queue.m_elements_in_q && 0 == queue.m_first_element_index);
	
	QueuePopChar(&queue);
	printf("%d\n", 4 == queue.m_elements_in_q && 1 == queue.m_first_element_index);
	QueuePopChar(&queue);
	printf("%d\n", 3 == queue.m_elements_in_q && 2 == queue.m_first_element_index);
	QueuePopChar(&queue);
	printf("%d\n", 2 == queue.m_elements_in_q && 3 == queue.m_first_element_index);
	QueuePopChar(&queue);
	printf("%d\n", 1 == queue.m_elements_in_q && 4 == queue.m_first_element_index);
	QueuePopChar(&queue);
	printf("%d\n", 0 == queue.m_elements_in_q && 0 == queue.m_first_element_index);
}

void PrintSll(node_t *head)
{
	printf("[ ");
	while(head != NULL)
	{
		printf("%d ", head->num);
		head = head->next;
	}
	printf("]\n");
}

void TestHasIntersection()
{
	node_t node1, node2, node3, node4, node5, node6, node7, node8, node9;
	
	printf("\nTEST HasIntersection:\n\n");
	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = NULL;
	node7.next = &node8;
	node8.next = &node9;
	node9.next = &node3;
	
	if (1 == HasIntersection(&node1, &node7))
	{
		printf(GREEN"SUCCESS\n"RESET_COLOR);
	}
	else
	{
		printf(RED"FAILED\n"RESET_COLOR);
	}
	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = NULL;
	node7.next = &node8;
	node8.next = &node9;
	node9.next = NULL;
	
	if (0 == HasIntersection(&node1, &node7))
	{
		printf(GREEN"SUCCESS\n"RESET_COLOR);
	}
	else
	{
		printf(RED"FAILED\n"RESET_COLOR);
	}
	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = &node7;
	node7.next = &node8;
	node8.next = &node9;
	node9.next = NULL;
	
	if (1 == HasIntersection(&node1, &node7))
	{
		printf(GREEN"SUCCESS\n"RESET_COLOR);
	}
	else
	{
		printf(RED"FAILED\n"RESET_COLOR);
	}
	
	if (1 == HasIntersection(&node1, &node1))
	{
		printf(GREEN"SUCCESS\n"RESET_COLOR);
	}
	else
	{
		printf(RED"FAILED\n"RESET_COLOR);
	}
} 

void TestSeparateTwoSll(node_t *head1, node_t *head_2)
{	
	node_t node1, node2, node3, node4, node5, node6, node7, node8, node9;
	
	printf("\nTEST SaparateTwoSll:\n\n");
	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = NULL;
	node7.next = &node8;
	node8.next = &node9;
	node9.next = &node3;
	
	node1.num = 1;
	node2.num = 2;
	node3.num = 3;
	node4.num = 4;
	node5.num = 5;
	node6.num = 6;
	node7.num = 7;
	node8.num = 8;
	node9.num = 9;
	
	printf("\nSll1 before saparate:\n");
	PrintSll(&node1);
	printf("Sll2 before saparate:\n");
	PrintSll(&node7);
	
	SeparateTwoSll(&node1, &node7);
	
	printf("\nSll1 after saparate:\n");
	PrintSll(&node1);
	printf("Sll2 after saparate:\n");
	PrintSll(&node7);		
	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = NULL;
	node7.next = &node8;
	node8.next = &node9;
	node9.next = NULL;
	
	printf("\nSll1 before saparate:\n");
	PrintSll(&node1);
	printf("Sll2 before saparate:\n");
	PrintSll(&node7);
	
	SeparateTwoSll(&node1, &node7);
	
	printf("\nSll1 after saparate:\n");
	PrintSll(&node1);
	printf("Sll2 after saparate:\n");
	PrintSll(&node7);		
	
	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = &node7;
	node7.next = &node8;
	node8.next = &node9;
	node9.next = NULL;
	
	printf("\nSll1 before saparate:\n");
	PrintSll(&node1);
	printf("Sll2 before saparate:\n");
	PrintSll(&node7);
	
	SeparateTwoSll(&node1, &node7);
	
	printf("\nSll1 after saparate:\n");
	PrintSll(&node1);
	printf("Sll2 after saparate:\n");
	PrintSll(&node7);
	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = &node7;
	node7.next = &node8;
	node8.next = &node9;
	node9.next = NULL;
	
	printf("\nSll1 before saparate:\n");
	PrintSll(&node1);
	printf("Sll2 before saparate:\n");
	PrintSll(&node1);
	
	SeparateTwoSll(&node1, &node1);
	
	printf("\nSll1 after saparate:\n");
	PrintSll(&node1);
	printf("Sll2 after saparate:\n");
	PrintSll(&node1);
}		


