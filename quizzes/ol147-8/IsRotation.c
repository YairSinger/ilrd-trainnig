#include <string.h> 	/*strlen */
#include <stdio.h> 		/*printf */
#include <assert.h> 


int IsRotation(char *s1, char *s2)
{
	size_t i = 0, j = 0;
	
	size_t len = strlen(s1);
	

	assert(NULL != s1);
	assert(NULL != s2);
	
	if (strlen(s2) != len)
	{
		return 0;
	}
	
	for (i = 0;i < len; ++i)
	{
		for(j = 0 ; s1[j] == s2[(i + j) % len] && j < len ; ++j) 
		{
			/*empty loop */
		}
		
		if(j == len)
		{
			return 1;
		}
	}
	
	return 0;
	
}

int main()
{
	char s1[] = "121256";
	char s2[] = "561212";
	char s3[] = "612334";
	char s4[] = "125612";
	
	printf("s1 and s2 result %d\n", IsRotation(s1, s2));
	printf("s1 and s3 result %d\n", IsRotation(s1, s3));
	printf("s1 and s4 result %d\n", IsRotation(s1, s4));
	
	return 0;
}
