#include <stdio.h>  /*printf*/
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen */
#include <assert.h>
#include <limits.h>	/*INT_MIN, INT_MAX */
	
#include "ws8.h"

#define ARRAY_SIZE 4


char *StrCpy(char *dest, const char *src)
{
	char * dest_holder = dest;

	assert(NULL != dest);
	assert(NULL != src);
	
	while (*src != '\0')
	{
		*dest = *src;
		++dest;
		++src;
	}
	
	*dest = '\0';
	return dest_holder;
}

char *StrDuup(const char *s)
{
	
	char *arr = NULL;
	assert(NULL != s);
	arr = (char *)malloc(sizeof(char) * strlen(s)+1);
	return StrCpy(arr, s);
}



void TestPrintElementArray(element_t *array, size_t size)
{
	printf("print element array test:\n");
	PrintElementArray(array, size);
	printf("end of test\n\n");
}

void  TestAddToElementArray(element_t *array,
 size_t size, int add_value)
{
	printf("value to add: %d\n", add_value);
	printf("Before AddToElementArray test:\n\n");
	PrintElementArray(array, size);
	
	AddToElementArray(array, size, add_value);
	printf("After AddToElementArray test:\n");
	PrintElementArray(array, size);
	printf("end of test\n\n");
}


	
int main(int argc, char **argv, char **envp)
{
	char s = 'F';
	char *str1 = NULL;
	int arr[5] = {1, 4, 6, 20, 100};
	int *grad = NULL;
	float float_num1 = 3.14;
	
	student_t tzafrir = 
	{"Tzafrir", 304846421, 3, NULL};
		
	element_t gen_arr[ARRAY_SIZE] = 
	{{NULL, &PrintString, &AddString, &CleanUpString}
	,{NULL, &PrintInt, &AddInt, &DoNothing}
	,{NULL, &PrintFloat, &AddFloat, &DoNothing}
	,{NULL, &PrintStudent, &AddStudent,&CleanUpStudent}};
	
	UNUSED(argc);
	UNUSED(argv);
	UNUSED(envp);
	
	grad = (int *) malloc (sizeof(int) * 3);
	grad[0] = 80;
	grad[1] = 87;
	grad[2] = 90;
	tzafrir.grades = grad;
	
	str1 = StrDuup("abc");

	
	gen_arr[0].value_p = (char *)str1;
	gen_arr[1].value_p = (int *) &arr[2]; 
	gen_arr[2].value_p = (float *) &float_num1;
	gen_arr[3].value_p = (student_t *) &tzafrir;
	
  	TestPrintElementArray(gen_arr, ARRAY_SIZE);
  	
	TestAddToElementArray(gen_arr, ARRAY_SIZE, 10);
	TestAddToElementArray(gen_arr, ARRAY_SIZE, 0);
	
		
	CleanupElementArray(gen_arr, ARRAY_SIZE);
	
	printf("The max2 from %d and %d is: %d\n", 5, 3, MAX2(5, 3)); 
	printf("The max3 from %d and %d and %d is: %d\n", 5, 8, 3, MAX3(5, 8, 3));
	printf("The max3 from %d and %d and %d is: %d\n", 5, 3, 8, MAX3(5, 3, 8));
	printf("The max3 from %d and %d and %d is: %d\n", 3, 5, 8, MAX3(3, 5, 8));
	
	/*ex6 */
	if ((sizeof(float_num1) == SIZEOF_VAR(float_num1)) 
	&& (sizeof(gen_arr[0]) == SIZEOF_VAR(gen_arr[0]))
	&& (sizeof(s) != SIZEOF_VAR(arr[1]))) 	/* char vs int */
	{
		printf("SIZEOF macro passed test with float, float vs int and element_t \n");
	}
	else
	{
		printf("SIZEOF macro faild test \n");
	}
	
	printf("SIZEOF_TYPE macro results %lu for int, %lu for char\n", SIZEOF_TYPE(int), SIZEOF_TYPE(char));
  	return 0;
}
