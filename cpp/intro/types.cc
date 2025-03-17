#include <iostream>

struct X
{
   int data; /* data */
   int value;
};



int main(){

   int j = 0;
   const int i = 5;
   int const i2 = 4;
   int const* i3 = &i2;
   struct X p1 = {1,2};
   struct X p2 = {3,2};

   struct X* const p = &p1;

   

   p = &p2;
   p->data = 2;


   struct X const x1 = p1;
   x1.data = -1;

const struct X *p4 = &p1;
   p4->data = 5;
   p4 = &p2;
   const struct X* * const p = &p4;
   int const* (* const f )(int*)= foo;
}