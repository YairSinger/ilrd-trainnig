#include <stdio.h> 	/* printf */
#include <string.h> /* memcmp */
#include "sll.h"

#define RESET_COLOR "\033[1;0m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

struct point
{
	float x;
	float y;
	char label[5];
};

/*typedef int (*match_func)(const void *lhs, const void *rhs);*/

int IntCompare(const void *lhs, const void *rhs)
{
	return !memcmp(rhs,lhs,sizeof(int));
} 

void TestCreate();
void TestInsert();
void TestCount();
void TestGetData();
void TestSetData();
void TestRemove();
/*void TestFind();*/
void TestHasLoop();
void TestFindIntersection();
void TestSllFlip();


int main()
{
	sll_t *sll = SllCreate();
	sll_iter_t iter = NULL;
	int x = 5;
	int y = 8;
	printf("sll sizeof %lu\n" , sizeof(sll));
	printf("sll begin add %p\n" , (void *) SllBegin(sll));
	printf("sll end add %p\n" , (void *) SllEnd(sll));
	printf("No of nodes %lu\n", SllCount((const sll_t *) sll));
	
	iter = SllInsert(sll, SllBegin(sll), (const void *) &x);
	iter = SllInsert(sll, iter, (const void *) &y);
	iter = SllInsert(sll, iter, (const void *) &y);
	/*
	printf("iter points at node with %d value\n", *((int *) SllGetData(iter)));
	
	printf("after next node with %d value\n", *((int *) SllGetData(iter)));
	
	SllSetData( iter, (void *) &y);
	printf("after set data node with %d value\n", *((int *) SllGetData(iter)));
	
	
	printf("sll begin add %p\n" , (void *) SllBegin(sll));
	printf("sll end add %p\n" , (void *) SllEnd(sll));*/
	printf("No of nodes %lu\n", SllCount((const sll_t *) sll));
	iter = SllBegin(sll);
	iter = SllNext(iter);
	
	iter = SllRemove(sll, iter);
	printf("No of nodes %lu\n", SllCount((const sll_t *) sll));
	iter = SllRemove(sll, iter);
	printf("No of nodes %lu\n", SllCount((const sll_t *) sll));
	TestCreate();
	TestCount();
	TestInsert();
	TestGetData();
	TestSetData();
	TestRemove();
	/*TestFind();*/
	/*TestHasLoop();*/
	/*TestFindIntersection();*/
	/*TestSllFlip();*/
	
	
	SllDestroy(sll);
	
	return 0;
}
/*****************************************************************************/
void TestCreate()
{
	sll_t *sll = SllCreate();
	int fails_counter = 0;
	
	/*test 1*/
	if(NULL == sll)
	{
		++fails_counter;
		printf(RED"Test 1 CREATE FAILED\n"RESET_COLOR);
	}
	/*test 2 */
	if (0 != SllCount((const sll_t *) sll))
	{
		++fails_counter;
		printf(RED"Test 2 CREATE failed starts with %lu nodes\n"RESET_COLOR, SllCount((const sll_t *) sll));
	}
	if (0 == fails_counter)
	{
		printf(GREEN"Test CREATE PASSED\n"RESET_COLOR);
	}
	SllDestroy(sll);
}

/*******************************************************************************/
void TestInsert()
{
	sll_t *sll = SllCreate();
	int fails_counter = 0;
	int x = 5;
	int y = 8;
	sll_iter_t iter = NULL;
	sll_iter_t end_add = NULL;
	
	iter = SllInsert(sll, SllBegin(sll), (const void *) &x);
	/*test1 is count nodes increase */
	if (1 != SllCount((const sll_t *) sll))
	{
		++fails_counter;
		printf(RED"Test 1 INSERT FAILED  %lu nodes expected 1\n"RESET_COLOR, SllCount((const sll_t *) sll));
	}
	iter = SllInsert(sll, iter, (const void *) &y);
	
	
	/*test2*/
	if (2 != SllCount((const sll_t *) sll))
	{
	++fails_counter;
		printf(RED"Test 2 INSERT FAILED  %lu nodes expected 2\n"RESET_COLOR, SllCount((const sll_t *) sll));
	}
	
	/*test if the insert is before iter */
	iter = SllBegin(sll);
	if(	*((int *) SllGetData(iter)) != 8)
	{
			++fails_counter;
			printf(RED"Test 3 INSERT FAILED order of insert isnt before iter\n"RESET_COLOR);
	}
	
	iter = SllNext(iter);
	if (*((int *) SllGetData(iter)) != 5)
	{
		++fails_counter;
			printf(RED"Test 3 INSERT FAILED order of insert isnt before iter\n"RESET_COLOR);
	}
	iter = SllNext(iter);
	/*test if end updates when insert before end*/
	
	end_add = SllEnd(sll);
	iter = SllInsert(sll, iter, (const void *) &x);
	if (end_add == SllEnd(sll))
	{
			++fails_counter;
			printf(RED"Test 4 INSERT FAILED updating end address\n"RESET_COLOR);
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test INSERT PASSED\n"RESET_COLOR);
	}
	SllDestroy(sll);
}

/********************************************************************/
void TestRemove()
{
	sll_t *sll = SllCreate();
	int fails_counter = 0;
	int x = 1;
	int y = 2;
	int z = 3;
	sll_iter_t iter = NULL;
	sll_iter_t end_add = NULL;
	
	iter = SllInsert(sll, SllBegin(sll), (const void *) &z);
	iter = SllInsert(sll, SllBegin(sll), (const void *) &y);
	iter = SllInsert(sll, SllBegin(sll), (const void *) &x);
	
	iter = SllBegin(sll);
	end_add = SllEnd(sll);
	iter = SllRemove(sll, iter);
	if (2 != SllCount((const sll_t *) sll))
	{
	++fails_counter;
		printf(RED"Test 1 REMOVE FAILED  %lu nodes expected 2\n"RESET_COLOR, SllCount((const sll_t *) sll));
	}	
	
	if (*((int *) SllGetData(iter)) != 2)
	{
	++fails_counter;
		printf(RED"Test 2 REMOVE FAILED  iter point of %d while expected  is 2\n"RESET_COLOR, *((int *)SllGetData(iter)));
	}
	
	if (end_add != 	SllEnd(sll))
	{
	++fails_counter;
		printf(RED"Test 3 REMOVE FAILED  SllEnd address was changed\n"RESET_COLOR);
	}
	
	iter = SllNext(iter);/*removal of last valid node */
	iter = SllRemove(sll, iter);
	if (1 != SllCount((const sll_t *) sll))
	{
	++fails_counter;
		printf(RED"Test 4 REMOVE FAILED  %lu nodes expected 1\n"RESET_COLOR, SllCount((const sll_t *) sll));
	}
	
	if (end_add == 	SllEnd(sll))
	{
	++fails_counter;
		printf(RED"Test 5 REMOVE FAILED  SllEnd address didn't updated\n"RESET_COLOR);
	}
	iter = SllBegin(sll);
	iter = SllRemove(sll, iter);
	if (0 != SllCount((const sll_t *) sll))
	{
	++fails_counter;
		printf(RED"Test 1 REMOVE FAILED  %lu nodes expected 2\n"RESET_COLOR, SllCount((const sll_t *) sll));
	}	
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test REMOVE PASSED\n"RESET_COLOR);
	}
	SllDestroy(sll);
}

/***************************************************************************************/
void TestCount()
{
	sll_t *sll = SllCreate();
	int fails_counter = 0;
	int x = 5;
	sll_iter_t iter = NULL;
	size_t i = 0;
	
	for (i = 0; i < 5 ; ++i)
	{
		if  (i != SllCount((const sll_t *) sll))
		{
			fails_counter = 1;
		}
		
		iter = SllInsert(sll, SllBegin(sll), (const void *) &x);
	}
	
	if  (fails_counter != 0)
		{
			printf(RED"Test 1 COUNT FAILED count during insert\n"RESET_COLOR);
		}
	iter = SllBegin(sll);
	
	for (; i > 0 ; --i)
	{
		if  (i != SllCount((const sll_t *) sll))
		{
			++fails_counter ;
			printf(RED"Test 2 COUNT FAILED count during remove\n %lu vs %ld expected"RESET_COLOR, SllCount((const sll_t *) sll), i );
		}
		
		iter = SllRemove(sll, iter);
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test COUNT PASSED\n"RESET_COLOR);
	}
	SllDestroy(sll);
}

/*****************************************************************************/

void TestGetData()
{
	sll_t *sll = SllCreate();
	int fails_counter = 0;
	int x = 5;
	char y = 'g';
	struct point z = { 6.5, 5.5, "OK"};
	sll_iter_t iter = NULL;
	
	iter = SllInsert(sll, SllBegin(sll), (const void *) &x);
	iter = SllInsert(sll, SllBegin(sll), (const void *) &y);
	iter = SllInsert(sll, SllBegin(sll), (const void *) &z);
	iter = SllBegin(sll);
	/*
	if 	(0 != memcmp(SllGetData(iter),&z, sizeof(size_t)) 
	&& memcmp(*((struct point *) SllGetData(iter)) ,z, sizeof(struct point)))
	{
		++fails_counter ;
		printf(RED"Test 1 GETDATA FAILED wrone adress\n %p vs %p expected"RESET_COLOR, SllGetData(iter), &z);
		
	}
	*/
	iter = SllNext(iter);
	if 	(0 != memcmp(SllGetData(iter),&y, sizeof(size_t)) 
	&& *((char *) SllGetData(iter)) != 'g')
	
	{
		++fails_counter ;
		printf(RED"Test 2 GET DATA FAILED wrong adress\n %p vs %p expected"RESET_COLOR, SllGetData(iter), &y);
	}
	iter = SllNext(iter);
	if 	(0 != memcmp(SllGetData(iter),&x, sizeof(size_t))
	&& *((int *) SllGetData(iter)) != 5)
	{
		++fails_counter ;
		printf(RED"Test 2 GET DATA FAILED wrong adress\n"RESET_COLOR);
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test GET DATA PASSED\n"RESET_COLOR);
	}
	SllDestroy(sll);
	
}
	
/**********************************************************************/



void TestSetData()
{

	sll_t *sll = SllCreate();
	int fails_counter = 0;
	int x = 5;
	int x2 = 7;
	char y[4] = "" ;
	
	sll_iter_t iter = NULL;
	
	iter = SllInsert(sll, SllBegin(sll), (const void *) &y);
	iter = SllInsert(sll, SllBegin(sll), (const void *) &x);
	iter = SllBegin(sll);
	
	SllSetData( iter, (void *) &x2);
	if (0 != memcmp(SllGetData(iter),&x2, sizeof(int)))
	{
		++fails_counter ;
		printf(RED"Test 1 SET DATA FAILED changing int\n %d vs %d expected\n"RESET_COLOR,*((int *)SllGetData(iter)), x2);
	}
	
	iter = SllNext(iter);
	SllSetData( iter, "yes");
	if (0 != memcmp(SllGetData(iter),"yes", sizeof(char) * 3))
	{
		++fails_counter ;
		printf(RED"Test 2 SET DATA FAILED changing string\n"RESET_COLOR);
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test SET DATA PASSED\n"RESET_COLOR);
	}
	
	SllDestroy(sll);
}
/**************************************************************************************/
/*
void TestFind()
{
*/
	/*match_func fp = &IntCompare;*/

/*
	sll_t *sll_i = SllCreate();
	sll_t *sll_c = SllCreate();
	int fails_counter = 0;
	int arr[3] = {0,1,2};
	sll_iter_t iter_i = NULL;
	sll_iter_t iter_holder = NULL;
	
	
	
	
	iter_i = SllInsert(sll_i, SllBegin(sll_i), (const void *) &arr[2]);
	iter_i = SllInsert(sll_i, iter_i, (const void *) &arr[1]);
	iter_holder = iter_i;
	iter_i = SllInsert(sll_i, iter_i, (const void *) &arr[0]);
	
	iter_i = SllFind(SllBegin(sll_i), SllEnd(sll_i) , IntCompare, (const void *)arr);
	if (iter_holder != iter_i)
	{
		++fails_counter ;
		printf(RED"Test 1 FIND FAILED to find int\n"RESET_COLOR);
	}
	*/
	
	/*iter_c = SllInsert(sll_c, SllBegin(sll_c), (const void *) &str[2]);
	iter_c = SllInsert(sll_c, iter_c, (const void *) &str[1]);
	
	iter_c = SllInsert(sll_c, iter_c, (const void *) &str[0]);
	
	
	SllDestroy(sll_i);
}
*/	
/*******************************************************************/
/*
void TestSllFlip()
{
	sll_t *sll = SllCreate();
	int arr[4] = {0,1,2,3};
	int arr_flipped[4] = {0};
	sll_iter_t iter = NULL;
	size_t i = 0;
	int fails_counter = 0;

	iter = SllInsert(sll, SllBegin(sll), (const void *) &arr[0]);
	iter = SllInsert(sll, SllBegin(sll), (const void *) &arr[1]);
	iter = SllInsert(sll, SllBegin(sll), (const void *) &arr[2]);
	iter = SllInsert(sll, SllBegin(sll), (const void *) &arr[3]); /*head to 3210 end*/
/*	iter = SllBegin(sll);
	for (i = 0; 0 != SllIsSameIter(iter, SllEnd(sll)); ++i)
	{
		arr_flipped[i] = *((int *) SllGetData(iter));
		iter = SllNext(iter);
	}
	
	
	for (iter = SllFlip(iter), i = 0; i < 4; ++i)
	{
		arr_flipped[i] = *((int *) SllGetData(iter));
		iter = SllNext(iter);
	}
	
	for(i = 0; i < 4; ++i)
	{
		if (arr[i] != arr_flipped[i])
		{
		++fails_counter ;
		printf(RED"Test 1 SllFlip FAILED to flip 4 nodes list %d flipped %d\n"RESET_COLOR, arr[i], arr_flipped[i]);
		}
	}	
	if (0 == fails_counter)
	{
		printf(GREEN"Test SllFlip PASSED\n"RESET_COLOR);
	}
	
	SllDestroy(sll);
}


*/



/********************************************************************/
/*void TestHasLoop()
{
	sll_t *sll = SllCreate();
	int x = 5;
	int fails_counter = 0;
	sll_iter_t iter = NULL;
	
	iter = SllInsert(sll, SllBegin(sll), (const void *) &x);
	iter = SllInsert(sll, SllBegin(sll), (const void *) &x);
	iter = SllInsert(sll, SllBegin(sll), (const void *) &x);
	iter = SllInsert(sll, SllBegin(sll), (const void *) &x);
	
	if (0 != HasLoop((const sll_iter_t) SllBegin(sll)))
	{
		++fails_counter ;
		printf(RED"Test 1 HasLoop FAILED with opened loop list\n"RESET_COLOR);
	}
	
	PrependList(sll,SllBegin(sll));
	if (1 != HasLoop((const sll_iter_t) SllBegin(sll)))
	{
		++fails_counter ;
		printf(RED"Test 2 HasLoop FAILED with looped list\n"RESET_COLOR);
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test HasLoop PASSED\n"RESET_COLOR);
	}
	
	
}
*/
/*************************************************************************/

/*void TestFindIntersection()
{
	sll_t *sll1 = SllCreate();
	sll_t *sll2 = SllCreate();
	int x = 5;
	int y = 4;
	int fails_counter = 0;
	sll_iter_t iter = NULL;
	
	iter = SllInsert(sll1, SllBegin(sll1), (const void *) &x);
	iter = SllInsert(sll1, SllBegin(sll1), (const void *) &x);
	iter = SllInsert(sll1, SllBegin(sll1), (const void *) &x);
	iter = SllInsert(sll1, SllBegin(sll1), (const void *) &x);

	iter = SllInsert(sll2, SllBegin(sll2), (const void *) &y);
	iter = SllInsert(sll2, SllBegin(sll2), (const void *) &y);
	iter = SllInsert(sll2, SllBegin(sll2), (const void *) &y);
	iter = SllInsert(sll2, SllBegin(sll2), (const void *) &y);
	iter = SllInsert(sll2, SllBegin(sll2), (const void *) &y);
	iter = SllInsert(sll2, SllBegin(sll2), (const void *) &y);
	iter = SllInsert(sll2, SllBegin(sll2), (const void *) &y);
	iter = SllInsert(sll2, SllBegin(sll2), (const void *) &y);
	
	if (SllEnd(sll1) != FindIntersection(SllBegin(sll1),SllBegin(sll2)))
	{
		++fails_counter ;
		printf(RED"Test 1 FIND_INTERSECTION FAILED with non intersect lists\n"RESET_COLOR);
	}
	
	PrependList(sll1,SllBegin(sll2)); /*make sll1 include all sll2 at its end */
	/*if (SllEnd(sll1) == FindIntersection(SllBegin(sll1),SllBegin(sll2)))
	{
		++fails_counter ;
		printf(RED"Test 2 FIND_INTERSECTION FAILED with intersect lists\n"RESET_COLOR);
	}
	
	if (0 == fails_counter)
	{
		printf(GREEN"Test FIND_INTERSECTION PASSED\n"RESET_COLOR);
	}
	
	/*SllDestroy(sll1);
	SllDestroy(sll2);*/
/*
}*/	

