/***********************************************************
*PROJECT: DS Stack
*
*WRITER: Yair Singer
*
*REVIEWER: Shaked Weinberger
*
*STATUS:
*
*DATE: 
***********************************************************/
#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/*
@Description: Dynamically allocates a stack.
@Parameters:
			 1. [capacity] - maximum amount of elements.
			 2. [element_size] - non-zero byte size of each element.
@Return value: Pointer to the stack.
@Time Complexity: O(1)
@Undefined Behavior: [element_size] is 0.
*/
stack_t *StackCreate(size_t capacity, size_t element_size);

/*
@Description: Frees allocated stack.
@Parameters:
			 1. [stack_ptr] - a pointer to a stack.
@Return value: none.
@Time Complexity: O(1)
@Undefined Behavior: [stack_ptr] is NULL.
*/
void StackDestroy(stack_t *stack_ptr);

/*
@Description: Pushes an element into stack.
@Parameters:
			 1. [stack_ptr] - a pointer to a stack.
			 2. [element] - pointer of element (size of stack element) to push.
@Return value: None.
@Time Complexity: O(1)
@Undefined Behavior: [stack_ptr] is NULL.
                     [element] is NULL or not size of stack element.
                     Stack is full.
*/
void StackPush(stack_t *stack_ptr, const void *element); 

/*
@Description: remove the most recently added element.
@Parameters: 
             1. [stack_ptr] - a pointer to a stack.
@Return value: None.
@Time Complexity: O(1)
@Undefined Behavior: [stack_ptr] is NULL. 
                     Stack is empty.
*/
void StackPop(stack_t *stack_ptr); 

/*
@Description: Peeks into the top element of a stack.
@Parameters:
			 1. [stack_ptr] - a pointer to a stack.
			 2. [buffer] - a pointer of a buffer (size of stac
			 k element) to write into.
@Return value: None.
@Time Complexity: O(1)
@Undefined Behavior: [stack_ptr] is NULL.
                     [buffer] is NULL or not size of stack element.
                     Stack is empty.
*/
void StackPeek(stack_t *stack_ptr, void *buffer); 

/*
@Description: Returns the current size of the stack.
@Parameters:
			 1. [stack_ptr] - a pointer to a stack.
@Return value: current size.
@Time Complexity: O(1)
Undefined Behavior: [stack_ptr] is NULL.
*/
size_t StackSize(stack_t *stack_ptr);

/*
@Description: checks if the stack is empty or not
@Parameters:  
             1. [stack_ptr] - a pointer to a stack.
@Return value: boolean, 1 if true.
Time Complexity: O(1)
Undefined Behavior: [stack_ptr] is NULL.
*/
int StackIsEmpty(stack_t *stack_ptr); 

/*
@Description: Return the maximum size of elements the stack can store 
@Parameters:  
             1. [stack_ptr] - a pointer to a stack.
@Return value: Capacity size
Time Complexity: O(1)
Undefined Behavior: [stack_ptr] is NULL.
*/
size_t StackCapacity(stack_t *stack_ptr);

#endif /* __STACK_H__ */
