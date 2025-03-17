
#include <stdio.h>  /* printf */
#include "avl.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

typedef int (*cmp_func)(const void *list_data, const void *user_data);


int AscendingInts(const void *list_data, const void *input)
{
	return *((int *) list_data) - *((int *)input);		
}

int DecreaseIntByParam(void *data, void *param)
{
	if(60 == *((int*)data) )
	{
		return -1;
	}
	else
	{
		(*((int*)data) -= *((int*)param));
		return 0;
	}
}


void TestCreate();
void TestInsertCountIsEmptyFind();
void TestBSTForEach();


int main()
{
	TestCreate();
	TestInsertCountIsEmptyFind();
	
	return 0;
}


/***************************************/
void TestCreate()
{
	cmp_func cmp_ints = AscendingInts;
	avl_t *tree = AVLCreate(cmp_ints);
	int fails = 0;
		 
	if (NULL == tree)
 	{
 		++fails;
		printf(RED"AVLCreate list CREATE FAILED  \n"RESET_COLOR);
 	}
 	
 	if (1 != AVLIsEmpty(tree))
 	{
 		++fails;
		printf(RED"AVLCreate list CREATE FAILED not empty\n"RESET_COLOR);
 	}
 	
 	
 	
 	if (0 != AVLCount(tree))
 	{
 		++fails;
		printf(RED"AVLCreate FAILED. Size is %lu vs 0 expected\n"RESET_COLOR,AVLCount(tree));
 	}
 	if (-1 !=  AVLGetHeight(tree))
 	{
 		++fails;
		printf(RED"AVLCreate FAILED, Height  %lu vs -1 expected\n"RESET_COLOR,AVLGetHeight(tree));
 	}
 	
 	if (0 == fails)
	{
		printf(GREEN"AVLCreate PASSED\n"RESET_COLOR);
	}
	
	AVLDestroy(tree);
	
}

/*************************************************/
void TestInsertCountIsEmptyFind()
{
	cmp_func cmp_ints = AscendingInts;
	avl_t *tree = AVLCreate(cmp_ints);
	
	int arr[20] = {100,109,140,170,106,107,103,104,105,90,95,94,98,97,89,84,87,86,85,88};
	int sorted_arr[20] = {84,85,86,87,88,89,90,94,95,97,98,100,103,104,105,106,107,109,140,170};
	int fails = 0;
	int insert_status = 0;
	size_t i = 0;
	
	
	if (NULL == tree)
 	{
 		++fails;
		printf(RED"AVLCreate list CREATE FAILED  \n"RESET_COLOR);
 	}
 	
 	for(i = 0; i < 20; ++i)
 	{
 		insert_status = AVLInsert(tree, (const void *)(&arr[i]));

	 	if (0 != AVLIsEmpty(tree))
	 	{
	 		++fails;
			printf(RED"AVLInsert FAILED, Empty after insert\n"RESET_COLOR);
	 	}
	 	
	 	if ((i + 1) != AVLCount(tree))
	 	{
	 		++fails;
			printf(RED"AVLInsert FAILED, size %lu vs %lu expected\n"RESET_COLOR,AVLCount(tree), (i + 1));
	 	}
 		
 		if ((void *)(&arr[i]) != AVLFind(tree,(void *)(&arr[i]) ))
	 	{
	 		++fails;
			printf(RED"AVLInsert FAILED, data stored is different from given\n"RESET_COLOR);
	 	}
	 	
	}
		
	if (4 !=  AVLGetHeight(tree))
 	{
 		++fails;
		printf(RED"AVLInsert FAILED, Height  %lu vs 4 expected\n"RESET_COLOR,AVLGetHeight(tree));
 	}	
 	if (0 == fails)
	{
		printf(GREEN"{AVLInsert, AVLGetHeight, AVLCount} \n"RESET_COLOR);
	}
	
	AVLDestroy(tree);
}

	/*remove last valid */
	
/*	iter = BSTPrev(BSTEnd(tree));
	BSTRemove(iter);
	if(19 != BSTGetSize(tree))
	{
		++fails;
		printf(RED"BSTSIZE  BSTRemove FAILED, %lu vs 19 expected\n"RESET_COLOR,BSTGetSize(tree));	
	}
	
	for(i = 0, iter = BSTBegin(tree); i < 19; ++i)
	{
		if(*((int *)BSTGetData(iter)) != sorted_arr[i])
		{
			++fails;
			printf(RED"BSTRemove last valid FAILED, %d vs %d expected\n"RESET_COLOR,*((int *)BSTGetData(iter)), sorted_arr[i]);	
		}
		iter = BSTNext(iter);
	}
	
	/*remove first valid */
/*	iter = BSTBegin(tree);
	BSTRemove(iter);
	
	if(18 != BSTGetSize(tree))
	{
		++fails;
		printf(RED"BSTRemove begin FAILED, %lu vs 19 expected\n"RESET_COLOR,BSTGetSize(tree));	
	}
	
	for(i = 1, iter = BSTBegin(tree); i < 19; ++i)
	{
		if(*((int *)BSTGetData(iter)) != sorted_arr[i])
		{
			++fails;
			printf(RED"BSTRemove begin FAILED, %d vs %d expected\n"RESET_COLOR,*((int *)BSTGetData(iter)), sorted_arr[i]);	
		}
		iter = BSTNext(iter);
	}
	
	/*remove node with 100 valid */
	
	/*iter = BSTFind(tree, (void *)(&sorted_arr[11]));
	*/	
	/*
	iter = BSTBegin(tree);
	for(i = 1, iter = BSTBegin(tree); i < 11; ++i)
	{
		iter = BSTNext(iter);
	}*/
	/*BSTRemove(iter);

	for(i = 1, iter = BSTBegin(tree); i < 10; ++i)
	{
		if(*((int *)BSTGetData(iter)) != sorted_arr[i])
		{
			++fails;
			printf(RED"BSTRemove root FAILED, %d vs %d expected\n"RESET_COLOR,*((int *)BSTGetData(iter)), sorted_arr[i]);	
		}
		iter = BSTNext(iter);
	}
	iter = BSTNext(iter);
	for(i = 12; i < 17; ++i)
	{
		if(*((int *)BSTGetData(iter)) != sorted_arr[i])
		{
			++fails;
			printf(RED"BSTRemove root FAILED, %d vs %d expected\n"RESET_COLOR,*((int *)BSTGetData(iter)), sorted_arr[i]);	
		}
		iter = BSTNext(iter);
	}
	if (0 == fails)
	{
		printf(GREEN"BSTRemove PASSED\n"RESET_COLOR);
	}
	fails = 0;
	
	iter = BSTFind(tree, (void *)(&sorted_arr[11]));
	if(iter != BSTEnd(tree))
	{
		++fails;
		printf(RED"BSTFind FAILED. NON exist key did not returned BSTEnd \n"RESET_COLOR);	
	}
	iter = BSTFind(tree, (void *)(&sorted_arr[12]));
	if(*((int *)BSTGetData(iter)) != sorted_arr[12])
	{
		++fails;
		printf(RED"STFind FAILED., %d vs %d expected\n"RESET_COLOR,*((int *)BSTGetData(iter)), sorted_arr[12]);	
	}
	
	iter = BSTFind(tree, (void *)(&sorted_arr[5]));
	if(*((int *)BSTGetData(iter)) != sorted_arr[5])
	{
		++fails;
		printf(RED"STFind FAILED., %d vs %d expected\n"RESET_COLOR,*((int *)BSTGetData(iter)), sorted_arr[5]);	
	}
	
	iter = BSTFind(tree, (void *)(&sorted_arr[1]));
	if(*((int *)BSTGetData(iter)) != sorted_arr[1])
	{
		++fails;
		printf(RED"STFind FAILED.smallest value, %d vs %d expected\n"RESET_COLOR,*((int *)BSTGetData(iter)), sorted_arr[1]);	
	}
	iter = BSTFind(tree, (void *)(&sorted_arr[4]));
	if(*((int *)BSTGetData(iter)) != sorted_arr[4])
	{
		++fails;
		printf(RED"STFind FAILED.smallest value, %d vs %d expected\n"RESET_COLOR,*((int *)BSTGetData(iter)), sorted_arr[4]);	
	}
	if (0 == fails)
	{
		printf(GREEN"STFind PASSED\n"RESET_COLOR);
	}

	
	BSTDestroy(tree);
}

void TestBSTForEach()
{
	bst_t *tree = BSTCreate(AscendingInts);
	grades_t grades_list[5] =  {{95,32,"yair"},
								{98,23,"Adi"},
								{82,18,"Shai"},
								{70,60,"Giora"},
								{80,40,"Dafna"}};
	int arr[20] = {100,109,140,170,106,107,103,104,105,90,95,94,98,97,89,84,87,86,85,88};
	int sorted_arr[20] = {84,85,86,87,88,89,90,94,95,97,98,100,103,104,105,106,107,109,140,170};
	int fails = 0;
	int param = 30;
	int status = 0;
	bst_iter_t iter = NULL;
	size_t i = 0;
	
	for(i = 0; i < 20; ++i)
 	{
 		iter = BSTInsert(tree, (const void *)(&arr[i]));
 	}
 	
 	status = BSTForEach(BSTBegin(tree), BSTEnd(tree), DecreaseIntByParam, (void *)(&param));
	if (0 != status )
	{
		printf(RED"BSTForEach  action func FAILED.returned%d vs 0 expected\n"RESET_COLOR,status);
	}

	for(i = 0, iter = BSTBegin(tree); i < 20; ++i)
	{
		if(*((int *)BSTGetData(iter)) != (sorted_arr[i] - 30))
		{
			++fails;
			printf(RED"BSTForEach FAILED, %d vs %d expected\n"RESET_COLOR,*((int *)BSTGetData(iter)), (sorted_arr[i] - 30));	
		}
		iter = BSTNext(iter);
	}
	
	param = 100;
	status = BSTForEach(BSTBegin(tree), BSTEnd(tree), DecreaseIntByParam, (void *)(&param));
	if (0 == status )
	{
		printf(RED"BSTForEach  action func returned 0 when action func returned non zero\n"RESET_COLOR);
	}
	for(i = 0, iter = BSTBegin(tree); i < 20; ++i)
	{
		if(*((int *)BSTGetData(iter)) != (sorted_arr[i] - 30) && i > 5)
		{
			++fails;
			printf(RED"BSTForEach FAILED, %d vs %d expected\n"RESET_COLOR,*((int *)BSTGetData(iter)), (sorted_arr[i] - 30));	
		}
		iter = BSTNext(iter);
	}
	if (0 == fails)
	{
		printf(GREEN"BSTForEach PASSED\n"RESET_COLOR);
	}
	
	BSTDestroy(tree);
}*/



