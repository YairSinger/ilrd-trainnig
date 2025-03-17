#ifndef __STACK_B_H__
#define __STACK_B_H__

#include <stddef.h> /* size_t, NULL */

typedef struct Stack stack_t;
/*
Name: StackCreate
Description: Creates a new stack_t structure with the specified capacity and element size
arguments: size_t capacity - the maximum number of elements that the stack can hold
           size_t element_size - the size in bytes of each element in the stack
return: A pointer to a newly allocated stack_t structure if successful, NULL otherwise
Bugs: None known
Time complexity: O(1)
Space complexity: O(1)
*/
stack_t *StackCreate(size_t capacity, size_t element_size);

/*
Name: StackDestroy
Description: Destroys the specified stack_t structure and frees any memory allocated to it
arguments: stack_t *my_stack - a pointer to a stack_t structure previously created by StackCreate
return: None
Bugs: None known
Time complexity: O(1)
Space complexity: O(1)
*/
void StackDestroy(stack_t *my_stack);

/*
Name: StackPush
Description: Adds an element to the top of the specified stack
arguments: stack_t *my_stack - a pointer to a stack_t structure previously created by StackCreate
           const void *element - a pointer to the element to be added to the top of the stack
return: None
Bugs: None known
Time complexity: O(1)
Space complexity: O(1)
*/
void StackPush(stack_t *my_stack, const void *element);

/*
Name: StackPop
Description: Removes the element at the top of the specified stack
arguments: stack_t *my_stack - a pointer to a stack_t structure previously created by StackCreate
return: None
Bugs: None known
Time complexity: O(1)
Space complexity: O(1)
*/
void StackPop(stack_t *my_stack);

/*
Name: StackPeek
Description: Returns a pointer to the element at the top of the specified stack, without modifying the stack
arguments: const stack_t *my_stack - a pointer to a stack_t structure previously created by StackCreate
return: A pointer to the element at the top of the stack if successful, NULL otherwise
Bugs: None known
Time complexity: O(1)
Space complexity: O(1)
*/
void *StackPeek(const stack_t *my_stack);

/*
Name: StackIsEmpty
Description: Determines whether the specified stack is empty
arguments: const stack_t *my_stack - a pointer to a stack_t structure previously created by StackCreate
return: 1 if the stack is empty, 0 otherwise
Bugs: None known
Time complexity: O(1)
Space complexity: O(1)
*/
int StackIsEmpty(const stack_t *my_stack);

/*
Name: StackSize
Description: Returns the current number of elements in the specified stack
arguments: const stack_t *my_stack - a pointer to a stack_t structure previously created by StackCreate
return: The number of elements in the stack
Bugs: None known
Time complexity: O(1)
Space complexity: O(1)
*/
size_t StackSize(const stack_t *my_stack);

/*
Name: StackCapacity
Description: Returns the maximum number of elements that the specified stack can hold
arguments: const stack_t *my_stack - a pointer to a stack_t structure previously created by StackCreate
return: The capacity of the stack
Bugs: None known
Time complexity: O(1)
Space complexity: O(1)
*/
size_t StackCapacity(const stack_t *my_stack);

#endif
