
#include "derived.hpp"

int main(int argc, char **argv)
{
    Derived d1(5,'x'); 
    Derived d2(3,'w');

    Base *b1 = &d1;
    
    b1->foo();
    
    // b1->bar();

    // Base *b2 = &d2;
    // *b2 = *b1;

    return 0;
}