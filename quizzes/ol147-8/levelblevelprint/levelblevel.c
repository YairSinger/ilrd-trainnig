#include <stdio.h>
#include "queue.h"


typedef struct node
{
	int data;
	struct node *children_left;
	struct node *children_right;
}node_t;

typedef struct tree
{
	node_t *root;
}tree_t;

void PrintAndDive(queue_t *queue)
{
	void *temp = QueuePeek(queue);
	QueueDequeue(queue);
	printf("%d\n",((node_t *)temp)->data);
	
	if(NULL != ((node_t *)temp)->children_left)
	{
		 QueueEnqueue(queue, ((node_t *)temp)->children_left);
	}
	
	if(NULL != ((node_t *)temp)->children_right)
	{
		 QueueEnqueue(queue, ((node_t *)temp)->children_right);
	}
}

void LevelBLevelPrint(tree_t *tree, queue_t *queue)
{
	QueueEnqueue(queue, tree->root);
	
	while (!QueueIsEmpty(queue))
	{
		PrintAndDive(queue);
	}
}

int main()
{
	queue_t *queue = QueueCreate();
	tree_t tree = {0};
	node_t nodes[5] = {0};
	 
	nodes[0].data = 1; 
	nodes[0].children_left = &nodes[1];
	nodes[0].children_right = &nodes[2];
	
	nodes[1].data = 2;
	nodes[1].children_left = &nodes[3];
	nodes[1].children_right = NULL;
	
	nodes[2].data = 3;
	nodes[2].children_left = &nodes[3];
	nodes[2].children_right = &nodes[4];
	
	nodes[3].data = 4;
	nodes[3].children_left = NULL;
	nodes[3].children_right = NULL; 
	
	nodes[4].data = 5;
	nodes[4].children_left = NULL; 
	nodes[4].children_right = NULL; 
	
	
	
	tree.root = &nodes[0];
	
	LevelBLevelPrint(&tree, queue);	
	
	return 0;
}
