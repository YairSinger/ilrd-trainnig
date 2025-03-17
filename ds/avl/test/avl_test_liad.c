#include <stdio.h> 	/* printf, size_t		*/
#include <string.h> /* memcmp 				*/
#include <stdlib.h> /* malloc , free, rand, srand			*/
#include <time.h>   /* time , clock */
#include <sys/types.h> /* ssize_t*/

#include "avl.h" 		

static int CmpFunc(const void *lhs,const void *rhs)
{
	return *(int *)lhs - *(int *)rhs;
}

int main()
{
	avl_t *tree = AVLCreate(CmpFunc);
	int values[] = {944, 29, 1756, 232};
	size_t arr_size = 4, i;
	
	for (i = 0; i < arr_size; ++i)
	{
		AVLInsert(tree, &values[i]);
	}
	printf("***********Original tree:************\n");
	Print(tree);
	
	for (i = 0; i < arr_size; ++i)
	{
		printf("***********Deleting %d************\n", values[i]);
		AVLRemove(tree, &values[i]);
		printf("Size expected: %ld, got: %ld\n", arr_size - i - 1, AVLCount(tree));
		printf("Find expected: 1, got: %d\n", AVLFind(tree, &values[i]) == NULL);
		Print(tree);		
	}
	
	return 0;
}
