#include <stdio.h>

void GenericSwap(void **ptr1, void **ptr2)
{
    void *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

int main()
{
    int x = 5, y = 6;
    char a = 'a', b = 'b';
    char *a_ptr = &a, *b_ptr = &b;
    int *x_ptr = &x, *y_ptr = &y;

    printf(" before %d, %d, %c , %c\n", *x_ptr, *y_ptr, *a_ptr, *b_ptr);
    GenericSwap((void **)&x_ptr,(void **)&y_ptr);
    GenericSwap((void **)&a_ptr,(void **)&b_ptr);
   printf(" after %d, %d, %c , %c\n", *x_ptr, *y_ptr, *a_ptr, *b_ptr);

    return 0;
}