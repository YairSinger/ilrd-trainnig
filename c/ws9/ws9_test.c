#include <stdio.h>  /*printf*/
#include <stdlib.h> /* calloc */
#include <string.h> /* memcpy */
#include "ws9.h"

#define MEM1 13
#define MEM2 24


int main(void)
{
	const char values[MEM1] = {8,4,1,2,3,4,5,6,7,8,9,0,2};
	char memset_test[MEM1] = {0}, memset_test_ref[MEM1] = {0}; 
	char memcpy_test[MEM1] = {0}, memcpy_test_ref[MEM1] = {0} ;
	char memmove_test[MEM1] = {0}, memmove_test_ref [MEM1] = {0}; 
	
	 
	/*ex 1 */
	
  	Memset(memset_test, 'y', MEM1);
  	memset(memset_test_ref, 'y', MEM1);
  	
  	if (!memcmp(memset_test, memset_test_ref, MEM1))
  	{
  		printf("Memset passed\n");
  	}
  	else
  	{
  		printf("Memset failed\n");
  	}    	
  	
  		Memset(memset_test+1, 'z', MEM1-2);
  	memset(memset_test_ref+1, 'z', MEM1-2);
  	
  	if (!memcmp(memset_test, memset_test_ref, MEM1))
  	{
  		printf("Memset passed with offset\n");
  	}
  	else
  	{
  		printf("Memset failed with offset\n");
  	}    	
  	/*ex 2 */
  	Memcpy((void *) memcpy_test, (void *) memset_test, MEM1);
  	memcpy((void *) memcpy_test_ref, (void *) memset_test, MEM1);
  	 	
  	if (!memcmp(memcpy_test,memcpy_test_ref,MEM1))
  	{
  		printf("Memcpy passed\n");
  	}
  	else
  	{
  		printf("Memcpy failed\n");
  	}
  	
  	
  	/* ex 3 */
  	Memset(memmove_test, 'y', MEM1);
  	Memset(memmove_test_ref, 'y', MEM1);
  	
  	
  	/*adressess do not over lap */
  	Memmove((void *) memmove_test, (void *) values, MEM1);
  	Memmove((void *) memmove_test_ref, (void *) values, MEM1);
  		
  	if (!memcmp(memmove_test, memmove_test_ref, MEM1))
  	{
  		printf("Memmove passed adressess do not over lap\n");
  	}
  	else
  	{
  		printf("Memmove failed adressess do not over lap\n");
  	}
  	
  	
  	
  	/*src overlaps dest */
  	Memmove((void *) memmove_test, (void *)((BYTE *) memmove_test + 2), MEM1-5);
  	Memmove((void *) memmove_test_ref, (void *)((BYTE *)memmove_test_ref + 2), MEM1-5);
  	/*for (i = 0; i < MEM1; ++i)
  	{
  		printf(" [%lu] Memmove %c memmove %c\n",
  		 i, *(memmove_test+i),  *(memmove_test_ref+i));
  	}
  	*/
  	if (!memcmp(memmove_test, memmove_test_ref, MEM1))
  	{
  		printf("Memmove passed src overlaps dest\n");
  	}
  	else
  	{
  		printf("Memmove failed src overlaps dest\n");
  	}
  	
  	/*dest overlaps src  */
  	Memmove((void *) ((BYTE *)memmove_test + 2), (void *) memmove_test , MEM1-5);
  	Memmove((void *) ((BYTE *)memmove_test_ref + 2), (void *) memmove_test_ref, MEM1-5);
  	
  	if (!memcmp(memmove_test, memmove_test_ref, MEM1))
  	{
  		printf("Memmove passed dest overlaps src\n");
  	}
  	else
  	{
  		printf("Memmove failed dest overlaps src\n");
  	}
  	
  	return 0;
}

