#include <stdio.h>

#include "avl.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define PURPLE "\033[0;35m"

enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

typedef struct avl_node avl_node_t;

struct avl_node
{
    void *data;
    ssize_t height; 
    avl_node_t *children[NUM_OF_CHILDREN];
};

struct avl
{
    avl_node_t *root;
    int (*cmp_func)(const void *, const void *);
};


void TestAVLCreate(void);
void TestAVLInsert(void);
void TestAVLFind(void);
void TestAVLForEach(void);
void TestAVLRemove(void);

int main()
{
	TestAVLCreate();
	TestAVLInsert();
	TestAVLFind();
	TestAVLForEach();
	/*TestAVLRemove();*/
	
	return 0;
}

/**************************************************/

static int IntCmp(const void *n1, const void *n2)
{
	return *((int *) n1) - *((int *) n2);
}

void TestAVLCreate(void)
{
	avl_t *tree = AVLCreate(IntCmp);
	
	printf(PURPLE"\nTEST AVLCreate:\n"RESET_COLOR);
		
	if ( NULL != tree &&
		 AVLIsEmpty(tree) &&
	     0 == AVLCount(tree) &&
	     -1 == AVLGetHeight(tree))
	{
		printf(GREEN"SUCCESS\n"RESET_COLOR);
	}
	else
	{
		printf(RED"FAILED\n"RESET_COLOR);
	}
	
	AVLDestroy(tree);
}

/**************************************************/

void TestAVLInsert(void)
{
	avl_t *tree = AVLCreate(IntCmp);
	
	size_t count_error = 0;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8, i = 9, j = 10, k = 0;
	
	printf(PURPLE"\nTEST AVLInsert:\n"RESET_COLOR);
	
	AVLInsert(tree, &d); 
	AVLInsert(tree, &h);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &a);
	AVLInsert(tree, &i);
	AVLInsert(tree, &f);
	AVLInsert(tree, &g);
	AVLInsert(tree, &e);
	AVLInsert(tree, &j);
	
	PrintMirror(tree);
	if ( 10 != AVLCount(tree) ||
		 3 != AVLGetHeight(tree) ||
		 AVLIsEmpty(tree) )
	{
		++count_error;
	}
	
	AVLDestroy(tree);
	
	tree = AVLCreate(IntCmp);
	
	AVLInsert(tree, &a);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &d);
	AVLInsert(tree, &e);
	AVLInsert(tree, &f);
	AVLInsert(tree, &g);
	AVLInsert(tree, &h);
	AVLInsert(tree, &i);
	AVLInsert(tree, &j);
	
	if ( 10 != AVLCount(tree) ||
		 3 != AVLGetHeight(tree) ||
		 AVLIsEmpty(tree) )
	{
		++count_error;
	}
	
	AVLDestroy(tree);
	
	tree = AVLCreate(IntCmp);
	
	AVLInsert(tree, &a);
	
	if ( 1 != AVLCount(tree) ||
		 0 != AVLGetHeight(tree) ||
		 AVLIsEmpty(tree) )
	{
		++count_error;
	}
	
	AVLDestroy(tree);
	
	tree = AVLCreate(IntCmp);
	
	AVLInsert(tree, &d); 
	AVLInsert(tree, &h);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &a);
	AVLInsert(tree, &i);
	AVLInsert(tree, &f);
	AVLInsert(tree, &g);
	AVLInsert(tree, &e);
	AVLInsert(tree, &j);
	AVLInsert(tree, &d); 
	AVLInsert(tree, &h);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &a);
	AVLInsert(tree, &i);
	AVLInsert(tree, &f);
	AVLInsert(tree, &g);
	AVLInsert(tree, &e);
	AVLInsert(tree, &j);
	
	/*if ( 20 != AVLCount(tree) ||
		 4 != AVLGetHeight(tree) ||
		 AVLIsEmpty(tree) )
	{
		++count_error;
	}
	
	AVLDestroy(tree);
	
	tree = AVLCreate(IntCmp);
	
	AVLInsert(tree, &d); 
	AVLInsert(tree, &h);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &a);
	AVLInsert(tree, &i);
	AVLInsert(tree, &f);
	AVLInsert(tree, &g);
	AVLInsert(tree, &e);
	AVLInsert(tree, &j);
	AVLInsert(tree, &d); 
	AVLInsert(tree, &h);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &a);
	AVLInsert(tree, &i);
	AVLInsert(tree, &f);
	AVLInsert(tree, &g);
	AVLInsert(tree, &e);
	AVLInsert(tree, &j);
	
	if ( 20 != AVLCount(tree) ||
		 4 != AVLGetHeight(tree) ||
		 AVLIsEmpty(tree) )
	{
		++count_error;
	}*/
	
	AVLDestroy(tree);
	
		
	if (0 == count_error)
	{
		printf(GREEN"SUCCESS\n"RESET_COLOR);
	}
	else
	{
		printf(RED"FAILED"RESET_COLOR" you have %lu errors.", count_error);
	}
}

/**************************************************/

void TestAVLFind(void)
{
	avl_t *tree = AVLCreate(IntCmp);
	
	size_t count_error = 0;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8, i = 9, j = 10, k = 0;
	
	printf(PURPLE"\nTEST AVLFind:\n"RESET_COLOR);
	
	AVLInsert(tree, &d); 
	AVLInsert(tree, &h);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &a);
	AVLInsert(tree, &i);
	AVLInsert(tree, &f);
	AVLInsert(tree, &g);
	AVLInsert(tree, &e);
	AVLInsert(tree, &j);
		
	k = 3;
	
	if (&c != (int *) AVLFind(tree, &k)) 	
	{
		++count_error;
	}
	
	k = 10;
	
	if (&j != (int *) AVLFind(tree, &k)) 	
	{
		++count_error;
	}
	
	k = 0;
	
	if (NULL != (int *) AVLFind(tree, &k)) 	
	{
		++count_error;
	}
	
	k = 1;
	
	if (&a != (int *) AVLFind(tree, &k)) 	
	{
		++count_error;
	}
	
	k = 7;
	
	if (&g != (int *) AVLFind(tree, &k)) 	
	{
		++count_error;
	}
	
	k = 11;
	
	if (NULL != (int *) AVLFind(tree, &k)) 	
	{
		++count_error;
	}
	
	k = 5;
	
	if (&d == (int *) AVLFind(tree, &k)) 	
	{
		++count_error;
	}
	
	AVLDestroy(tree);
		
	if (0 == count_error)
	{
		printf(GREEN"SUCCESS\n"RESET_COLOR);
	}
	else
	{
		printf(RED"FAILED"RESET_COLOR" you have %lu errors.", count_error);
	}
	
}

/******************************************/

int PrintInt(void *data, void *null)
{
	printf("%d ", *((int *) data));
	
	return 0;
}

int AddOne(void *data, void *null)
{
	++*((int *) data);
	
	return 0;
}

void TestAVLForEach(void)
{
	avl_t *tree = AVLCreate(IntCmp);
	
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8, i = 9, j = 10, k = 0;
	
	printf(PURPLE"\nTEST AVLForEach:\n"RESET_COLOR);
	
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
    AVLInsert(tree, &e);
	AVLInsert(tree, &j);
	AVLInsert(tree, &d); 
	AVLInsert(tree, &a);
	AVLInsert(tree, &i);
	AVLInsert(tree, &f);
	AVLInsert(tree, &g);
	AVLInsert(tree, &h);
	
	printf("PreOrder:\n");
	AVLForEach(tree, PRE_ORDER, PrintInt, NULL);
	printf("\nInOrder:\n");
	AVLForEach(tree, IN_ORDER, PrintInt, NULL);
	printf("\nPostOrder:\n");
	AVLForEach(tree, POST_ORDER, PrintInt, NULL);
	
	printf("\nPreOrder+1;\n");
	AVLForEach(tree, PRE_ORDER, AddOne, NULL);
	AVLForEach(tree, PRE_ORDER, PrintInt, NULL);
	
	printf("\nInOrder+1;\n");
	AVLForEach(tree, IN_ORDER, AddOne, NULL);
	AVLForEach(tree, IN_ORDER, PrintInt, NULL);
	
	printf("\nPostOrder+1;\n");
	AVLForEach(tree, POST_ORDER, AddOne, NULL);
	AVLForEach(tree, POST_ORDER, PrintInt, NULL);
	printf("\n");
	
	AVLDestroy(tree);
}

/******************************************/

/*static void PrintTree(avl_node_t *node, int space) 
{

    int i = 0;

      if (node == NULL) 
      {
        return;
      }

      PrintTree(node->children[RIGHT], space  + 1 ); 

      for (; i < space; i++) 
      {
        printf("                 ");   
      }
      
      printf("data:%d, (height:%ld)\n", *(int *)node->data, node->height);
      
      PrintTree(node->children[LEFT], space + 1); 
}
*/

/*void Print(avl_t *tree)
{

    PrintTree(tree->root, 0);
    
}*/

void TestAVLRemove(void)
{
	avl_t *tree = AVLCreate(IntCmp);
	
	size_t count_error = 0;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8, i = 9, j = 10, k = 0;
	
	printf(PURPLE"\nTEST AVLRemove:\n"RESET_COLOR);
	
	AVLInsert(tree, &d); 
	AVLInsert(tree, &h);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &a);
	AVLInsert(tree, &i);
	AVLInsert(tree, &f);
	AVLInsert(tree, &g);
	AVLInsert(tree, &e);
	AVLInsert(tree, &j);
	
	AVLRemove(tree, &e);
	AVLRemove(tree, &g);
	AVLRemove(tree, &j);
	
	if ( 7 != AVLCount(tree) ||
		 2 != AVLGetHeight(tree) ||
		 AVLIsEmpty(tree) )
	{
		++count_error;
	}
	
	AVLDestroy(tree);
	
	tree = AVLCreate(IntCmp);
	
	AVLInsert(tree, &d); 
	AVLInsert(tree, &h);
	AVLInsert(tree, &b);
	AVLInsert(tree, &c);
	AVLInsert(tree, &a);
	AVLInsert(tree, &i);
	AVLInsert(tree, &f);
	AVLInsert(tree, &g);
	AVLInsert(tree, &e);
	AVLInsert(tree, &j);
	
	AVLRemove(tree, &h);
	AVLRemove(tree, &g);
	AVLRemove(tree, &e);
	
	if ( 7 != AVLCount(tree) ||
		 2 != AVLGetHeight(tree) ||
		 AVLIsEmpty(tree) )
	{
		++count_error;
	}
	
	AVLRemove(tree, &i);
	AVLRemove(tree, &f);
	AVLRemove(tree, &j);
	AVLRemove(tree, &d);
	
	if ( 3 != AVLCount(tree) ||
		 1 != AVLGetHeight(tree) ||
		 AVLIsEmpty(tree) )
	{
		++count_error;
	}
	
	AVLRemove(tree, &b);
	AVLRemove(tree, &c);
	
	if ( 1 != AVLCount(tree) ||
		 0 != AVLGetHeight(tree) ||
		 AVLIsEmpty(tree) )
	{
		++count_error;
	}
	
	AVLRemove(tree, &a);
	
	if ( 0 != AVLCount(tree) ||
		 -1 != AVLGetHeight(tree) ||
		 !AVLIsEmpty(tree) )
	{
		++count_error;
	}
	
	AVLDestroy(tree);
		
	if (0 == count_error)
	{
		printf(GREEN"SUCCESS\n"RESET_COLOR);
	}
	else
	{
		printf(RED"FAILED"RESET_COLOR" you have %lu errors.", count_error);
	}
}	





