#include <stdio.h> /*fputs, printf */
#include "dvector.h"

typedef struct point
{
	int x;
	int y;
}point_t;

d_vector_t *TestDVectorCreate();
void TestDVectorDestroy(d_vector_t *vector_ptr);
void TestDVectorPushBack(d_vector_t *vector_ptr);
void TestDVectorGetElementAccess(d_vector_t *vector_ptr);
void TestDVectorPopBack(d_vector_t *vector_ptr);

int main()
{
	d_vector_t *res = NULL;
	res = TestDVectorCreate();
	TestDVectorPushBack(res); 
	TestDVectorGetElementAccess(res);
	TestDVectorPopBack(res);
	DVectorShrink(res);
	if (5 == DVectorCapacity(res) )
	{
		printf("DVectorShrink PASSED\n");
	}
	else
	{
		printf("DVectorShrink FAILED\ncapacity  %lu", DVectorCapacity(res));	
	}
	DVectorReserve(res, 10);
	if (10 == DVectorCapacity(res))
	{
		printf("DVectorReserve PASSED\n");
	}
	else
	{
		printf("DVectorReserve FAILED\ncapacity  %lu", DVectorCapacity(res));	
	}
	if (10 == DVectorCapacity(res))
	{
		printf("DVectorCapacity PASSED\n");
	}
	else
	{
		printf("DVectorCapacity FAILED\ncapacity  %lu", DVectorCapacity(res));	
	}
	if (5 == DVectorSize(res))
	{
		printf("DVectorSize PASSED\n");
	}
	else
	{
		printf("DVectorSize FAILED\ncapacity  %lu", DVectorSize(res));
	}
	
	
	
	TestDVectorDestroy(res);
	return 0;
}

d_vector_t *TestDVectorCreate()
{
	point_t cordi_a = {0, 1};

	d_vector_t *v_ptr = DVectorCreate(5, sizeof(cordi_a));
	
	
	if (NULL == v_ptr)
	{
		fputs("faild to create vector\n", stderr);
	}	
	
	if (5 == DVectorCapacity(v_ptr) && DVectorSize(v_ptr) == 0)
	{
		printf("DVectorCreate PASSED\n");
	}
	else
	{
		printf("capacity %lu vs 5 expected\n size %lu vs 0 expected\n", DVectorCapacity(v_ptr), DVectorSize(v_ptr));
	} 
	return v_ptr;
}

void TestDVectorDestroy(d_vector_t *vector_ptr)
{
	DVectorDestroy(vector_ptr);
}


void TestDVectorPushBack(d_vector_t *vector_ptr)
{
	point_t cordi_a = {0, 1}, cordi_b = {-5, 8};
	if(0 == DVectorPushBack(vector_ptr, &cordi_a) && 1 == DVectorSize(vector_ptr) && 5 == DVectorCapacity(vector_ptr))
	{
		printf("DVectorPushBack PASSED\n");
	}
	else
	{
		printf("DVectorPushBack FAILED\n");
		printf("size %lu expected 1\n", DVectorSize(vector_ptr));
		printf("capacity %lu expected 5\n",DVectorCapacity(vector_ptr)); 
	}
	DVectorPushBack(vector_ptr, &cordi_b);
	DVectorPushBack(vector_ptr, &cordi_b);
	DVectorPushBack(vector_ptr, &cordi_b);
	DVectorPushBack(vector_ptr, &cordi_b);
	DVectorPushBack(vector_ptr, &cordi_b);	
	if (10 != DVectorCapacity(vector_ptr))
	{
		printf("DVectorPushBack FAILED to increase capacity\n");
	}
}


void TestDVectorGetElementAccess(d_vector_t *vector_ptr)
{

	 if (((point_t *)DVectorGetElementAccess(vector_ptr, 1))->x != -5)
	 {
	 	printf("DVectorGetElementAccess FAILED\n");
	 	printf("%d\n", ((point_t *)DVectorGetElementAccess(vector_ptr, 1))->x);
	 }
	 else
	 {
	 	((point_t *)DVectorGetElementAccess(vector_ptr, 1))->x = -3;
	 	if (((point_t *)DVectorGetElementAccess(vector_ptr, 1))->x == -3)
	 	{
	 		printf("DVectorGetElementAccess PASSED\n");
	 	}
	 	else
	 	{
	 		printf("DVectorGetElementAccess FAILED\n");
	 	printf("%d\n vs -3 expected", ((point_t *)DVectorGetElementAccess(vector_ptr, 1))->x);
	 	}
	 }
}


void TestDVectorPopBack(d_vector_t *vector_ptr)
{
	DVectorPopBack(vector_ptr);
	if (5 == DVectorSize(vector_ptr))
	{
		printf("DVectorPopBack PASSED\n");
	}
	else
	{
		printf("DVectorPopBack FAILED\n");
	}
}
