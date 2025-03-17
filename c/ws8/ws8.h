#ifndef __WS8_H__
#define __WS8_H__

#define UNUSED(x) (void)(x)
#define MAX2(a, b) (a) > (b) ? (a) : (b)
#define MAX3(a, b, c) MAX2((c), MAX2((a),(b)))
#define MAX_DIGITS_IN_INT 12
#define SIZEOF_VAR(variable) (char *)(&variable+1) - (char *)(&variable)
#define SIZEOF_TYPE(type ) (char*)(((type *) 0) + 1) - (char *)((type *) 0)

typedef struct student 
{
   char name[10];
   int id;
   size_t grades_size;
   int * grades;
}
student_t;



typedef struct element 
{
   void * value_p;
   void (*print)(struct element *);
   void (*add)(int , struct element *);
   void (*clean)(struct element *);
}
element_t;

/*
* Adds given value to every element in an array of elemnts
* @params: array of elements, its size, the value to add
* @return: none
*
* assumes that if element value holds a string, 
* the string is dynamicly allocated to be able to add. 
*/
void AddToElementArray(element_t *array, size_t size, int add_value);

/*
* Cleanups every allocated element in array of elements
* @params: array of elements, its size
* @return: none
*/
void CleanupElementArray(element_t *array, size_t size);

/*
* Prints every element in array of elements
* @params: array of elements, its size
* @return: none
*/
void PrintElementArray(element_t *array, size_t size);

void PrintInt(element_t *el);
void PrintFloat(element_t *el);
void PrintString(element_t *el);
void PrintStudent(element_t *el);

void AddInt(int value_to_add, element_t *el);
void AddFloat(int value_to_add, element_t *el);
void AddString(int value_to_add, element_t *el);
void AddStudent(int value_to_add, element_t *el);

void CleanUpString(element_t *el);
void CleanUpStudent(element_t *el);
void DoNothing(element_t *el);

/*prints value stored in void pointer adress. */




#endif /*__WS8__*/

