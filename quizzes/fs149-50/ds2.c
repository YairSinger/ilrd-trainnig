#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include "stack.h"*/

enum children
{
    LEFT = 0,
    RIGHT
};

typedef struct node
{
    int data;
    struct node *next;
}node_t;

typedef struct bst_node
{
	int val;
    struct bst_node *parent;
    struct bst_node *children[2]; 
} bst_node_t;



/*iterative*/
node_t *FlipSll(node_t *head)
{
    node_t *prev = head;
    node_t *next = NULL;
    head = head->next;
    prev->next = NULL;

    while(head->next != NULL)
    {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    head->next = prev;
    return head;
}


/*recursive*/
node_t *Flipper(node_t *prev, node_t *cur, node_t *head)
{
    node_t *new_head = NULL;

    if (cur->next == NULL)
    {
        cur->next = prev;
        return cur;
    }

    new_head = Flipper(cur, cur->next, head);
    cur->next = prev;
    if(prev == head)
    {
        prev->next = NULL;
    }

    return new_head;
}

node_t *FlipSllRec(node_t *head)
{
    return Flipper(head,head->next,head);
}

size_t MaxSubArray(int *arr, size_t size)
{
    size_t sum = 0;
    size_t op_sum = 0;
    size_t i = 0, r_inx = 0;

    while(i < size)
    {
        if (arr[i] >= 0)
        {
            if(r_inx == i - 1)
            {
                ++r_inx;
                sum += arr[i];
            }
            else
            {
                op_sum += arr[i];
            }
        }
        else
        {
            if (r_inx == i -1)
            {
                if (arr[i] + sum > 0)
                {
                    op_sum = sum + arr[i];
                }
            }
            else
            {
                if(op_sum >= sum)
                {
                    r_inx = i-1;
                    sum = op_sum;
                    op_sum = 0;
                }
                else
                {
                    op_sum = 0;
                }
            }
        }
        ++i;    
    }

    return sum > op_sum ? sum : op_sum;
}

void TestEx2()
{
    int arr[] = {-2,1,-3,4,-1,2,3,-5,4};
	int arr2[] = {-2,1,-3,4,-1,2,1,-5,4};
    int fails = 0;
    if (MaxSubArray(arr,9) != 8)
    {
        ++fails;
        printf("\nfailed arr, %lu\n", MaxSubArray(arr,9));

    }
     if (MaxSubArray(arr2,9) != 6)
    {
        ++fails;
        printf("\nfailed arr2 %lu \n", MaxSubArray(arr2,9) );
    }

    if(fails == 0)
    {
        printf("pass MaxSubArray\n");
    }
}

/*int SortStack(stack_t *stack)
{
	int temp = 0;
	int movver = 0;
	int movver2 = 0;
	stack_t *helper = NULL;
	assert(NULL != stack);
	if (!StackIsEmpty(stack))
	{
		helper = StackCreate(StackCapacity(stack), sizeof(int));
		if(NULL == helper )
		{
			return -1;
		}

		StackPeek(stack, &movver);
		StackPop(stack);
		StackPush(helper, (const void *) &movver);

		while(!StackIsEmpty(stack))
		{
			StackPeek(stack, &movver);
			StackPeek(helper, &movver2);
			if(movver >= movver2)
			{
				StackPop(stack);
				StackPush(helper, (const void *) &movver);
			}
			else
			{
				temp = movver;
				StackPop(stack);
				while (movver2 > temp && !StackIsEmpty(helper))
				{
					StackPop(helper);
					StackPush(stack, (const void *) &movver2);
					StackPeek(helper, &movver2);
				}
				
				StackPush(helper, (const void *) &temp);
			}
		}

		while (!StackIsEmpty(helper))
		{
			StackPeek(helper, &movver2);
			StackPop(helper);
			StackPush(stack, (const void *) &movver2);
		}

		StackDestroy(helper);
	}

	return 0;
}

void TestEx3()
{
	stack_t *st1 = StackCreate(5, sizeof(int));
	stack_t *st2 = StackCreate(5, sizeof(int));
	stack_t *printing_stack = StackCreate(5, sizeof(int));
	int arr2[] = {0,1,2,3,4};
	int arr1[] = {30,5,10,-2,40};
	int temp = 0;
	size_t i = 0;

	for (i = 0; i < 5; ++i)
	{
		StackPush(st1, (const void *)&arr1[i]);
		StackPush(st2, (const void *)&arr2[i]);
	}

	printf("before sort\n");

	while (!StackIsEmpty(st1))
	{
		StackPeek(st1, &temp);
		printf("%d, ", temp);
		StackPop(st1);
		StackPush(printing_stack, (const void *) &temp);
	}

	printf("\n");

	while (!StackIsEmpty(printing_stack))
	{
		StackPeek(printing_stack, &temp);
		StackPop(printing_stack);
		StackPush(st1, (const void *) &temp);
	}

	temp = SortStack(st1);
	if (temp)
	{
		printf("returned -1 from StackSort\n");
	}

	printf("after sort\n");

	while (!StackIsEmpty(st1))
	{
		StackPeek(st1, &temp);
		printf("%d, ", temp);
		StackPop(st1);
		StackPush(printing_stack, (const void *) &temp);
	}

	printf("\n");

	while (!StackIsEmpty(printing_stack))
	{
		StackPeek(printing_stack, &temp);
		StackPop(printing_stack);
		StackPush(st1, (const void *) &temp);
	}

	StackDestroy(st1);
	StackDestroy(st2);
	StackDestroy(printing_stack);
}
*/

void TestEx1()
{
    node_t a = {0};
    node_t b = {0};
    node_t c = {0};
    node_t d = {0};
    
    node_t *runner = &d;



    a.data = 1;
    a.next = NULL; 
    
    b.data = 2;
    b.next = &a;

    c.data = 3;
    c.next = &b;

    d.data = 4;
    d.next = &c;
    
    printf("before \n");

    while(runner != NULL)
    {
        printf("%d,", runner->data);
        runner = runner->next;
    }

    runner = &d;
    printf("\n after \n");
    runner = FlipSll(&d);

    while(runner != NULL)
    {
        printf("%d,", runner->data);
        runner = runner->next;
    }

     printf("\n after rec flip \n");

    runner = FlipSllRec(&a);

     while(runner != NULL)
    {
        printf("%d,", runner->data);
        runner = runner->next;
    }

}



int SortCharsInFile(const char *file_name, char *result)
{
    long arr[256] = {0};
    size_t i = 0;
    FILE * fd = NULL;
    char c = '\0'; 

    assert(NULL != file_name);
    assert(NULL != result);

    fd = fopen(file_name, "r");
    if(NULL == fd )
    {
       printf("error open file\n");
       return -1;
    }

    while (EOF != (c = fgetc(fd)))
    {
        arr[c + 128] += 1;
    }

    fclose(fd);
    for(i = 0; i < 256; ++i)
    {
        while ( arr[i] > 0)
        {
            *result = i - 128;
            arr[i] -= 1;
            ++result;
        }
    }
    return 0;
}



int IterativeInsert(bst_node_t *root, int data)
{
    bst_node_t *runner = NULL;
    assert(NULL != root);

    runner = root;
    while(NULL != runner)
    {
        if(runner->val > data)
        {
            runner = runner->children[0];
        }
        else
        {
            runner = runner->children[1];
        }
    }

    runner = (bst_node_t*)malloc(sizeof(bst_node_t));
    if(NULL == runner )
    {
        return -1;
    }

    runner->val = data;
    runner = runner->children[0];
    runner = runner->children[1];
    return 0;
}

int RecursiveBstInsert(bst_node_t *root, int data)
{
    bst_node_t *runner = root;
    if(runner != NULL)
    {
        if (runner->val > data)
        {
            return RecursiveBstInsert(runner->children[LEFT], data);
        }
        else
        {
            return RecursiveBstInsert(runner->children[RIGHT], data);        
        }
    }
    else
    {
        runner = (bst_node_t*) malloc(sizeof(bst_node_t));
        if(NULL == runner)
        {
            return -1;
        }
        runner->val = data;
        runner->children[LEFT] = NULL;
        runner->children[RIGHT] = NULL;
        return 0;
    }
}

bst_node_t *CreateNode(bst_node_t *new_node_parent, int val)
{
    bst_node_t *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
   
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    new_node->parent = new_node_parent;
    new_node->val = val;
    return new_node;
}

void TestBstInsert()
{
    bst_node_t *root = (bst_node_t *)malloc(sizeof(bst_node_t));
    int insert[] = {12,2};
    root->parent = NULL;
    root->val = 8;
    root->children[LEFT] = CreateNode(root->children[LEFT],5);
    root->children[RIGHT] = CreateNode(root->children[RIGHT],10);
    root->children[LEFT]->children[LEFT] = CreateNode(root->children[LEFT]->children[LEFT], 1);
    root->children[LEFT]->children[RIGHT] = CreateNode(root->children[LEFT]->children[RIGHT], 6);
    root->children[LEFT]->children[LEFT]->children[LEFT] = CreateNode(root->children[LEFT]->children[LEFT]->children[LEFT] , 0);
    root->children[LEFT]->children[LEFT]->children[RIGHT] = CreateNode(root->children[LEFT]->children[LEFT]->children[RIGHT] , 3);  

}
int FixedSizeBstInsert(int *arr, size_t size, int data)
{
    size_t i = 0;

    while (i < size && arr[i] != __INT_MAX__)
    {
        if(arr[i] > data)
        {
            i = 2 *(i + 1) - 1;
        }
        else
        {
            i = 2 * (i + 1);
        }
    }

    if (i >= size)
    {
        return -1; /* full bst*/
    }
    else
    {
        arr[i] = data;
        return 0;
    }
}


 size_t Reverse_String(char *str, size_t start_inx)
{
    size_t end_inx = 0;
    size_t returned = 0;
    char word[100] = {'\0'};
    while(str[start_inx] == ' ')
    {
        ++start_inx;
    }
    end_inx = start_inx;

    while(str[end_inx] != ' ' && str[end_inx] != '\0')
    {
        ++end_inx;
    }


    if ('\0' != str[end_inx])
    {
        strncpy(word, &str[start_inx],end_inx - start_inx);
        returned = Reverse_String(&str[end_inx], end_inx);
        strncpy(&str[returned], word, end_inx - start_inx);
        str[end_inx] = ' ';
        return returned + end_inx + 1;
    }
    else
    {
        strncpy(word, &str[start_inx],end_inx - start_inx);
        strncpy(&str[0], word, end_inx - start_inx);
        str[end_inx] = ' ';
        return end_inx + 1;
    }

}



void ReverseString2(char *str, int read_inx, int write_inx, int len)
{
    char c = '\0';
    if (str == NULL || read_inx == len)
    {
        return;
    }

    c = str[read_inx];

    ReverseString2(str, read_inx + 1, write_inx - 1, len);
    str[write_inx] = c;
    return;
}

void ReverseString(char *str)
{
    int len = strlen(str);
     ReverseString2(str, 0, len - 1, len);
}


void TestEx7(void)
{
    char str[20] = {'\0'};
    char res[20] = {'\0'};

    strcpy(str, "abcde ");
    strcpy(res, " edcba");
    ReverseString(str);

    if (0 != strcmp(res, str))
    {
        printf("failed reverese string\n");
        printf("%s vs %s expected\n", str,res);
    }
    else
    {
        printf("passed Reverse_String\n");
    }

}

void Swap(char *str, size_t inx1, size_t inx2)
{
    char temp = str[inx1];
    str[inx1] = str[inx2];
    str[inx2] = temp;
}

void Permute(char * str, size_t swapping_inx, size_t size)
{

    size_t runner = swapping_inx;
    size_t i = 0;
    if (swapping_inx == size)
    {
        while(i < size)
        {
            printf("%s\n", &str[i]);
            ++i;
        }
        return;
    }
    else
    {
        while(runner < size)
        {
            Swap(str, swapping_inx, runner);
            Permute(str, swapping_inx + 1, size);
            Swap(str, swapping_inx, runner);
            ++runner;
        }        
    }
}

void PermuteRec(char *str)
{
    Permute(str, 0, strlen(str));
}



/*void TestBst()
{
    bst_node_t *root = CreatBst();
    int insert = 5;

    printf("Before insert\n");
    
    PrintBst(root);

    int res = IterativeInsert(root, insert);



}*/

void Stack_insert(stack_t *stack, int *data)
{
	int peek = 0; 
	if (StackIsEmpty(stack))
	{
		StackPush(stack, data);
	}
	else
	{
		StackPeek(stack, &peek);
		if (*data >= peek)
		{
			StackPop(stack);
			Stack_insert(stack, data);
			StackPush(stack, &peek);
		}
		else
		{
			StackPush(stack, data);	
		}
	}
}

int MaxSumOfSubArr(int *arr, size_t size)
{
    int sum = 0;
    int max_sum = 0;
    size_t i = 0;

    assert(arr);

    while (arr[i] < 0)
    {
        ++i;
    }

    while (i < size)    
    {
        sum += arr[i];

        if (sum < 0)
        {
            sum = 0;
        }

        if (sum > max_sum)
        {
            max_sum = sum;
        }
        
        ++i;
    }
    
    return max_sum;
}


void TestFiles(void)
{
    char result[100] = {0};

    SortCharsInFile("text.txt", result);

    printf("Files:\n");

    printf("%s\n", result);

}
int main()
{
    char str[4] = {'\0'};
    strcpy(str, "abc");
    /*TestEx1();
    TestEx2();
    TestFiles();*/
    TestEx7();
    PermuteRec(str);


    return 0;
}



