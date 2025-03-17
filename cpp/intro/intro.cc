#include <cstdio> //printf
#include <iostream> //cout
#include "foo.hpp"


void Foo() {
    std::cout << "first" << std::endl;
}

void Foo(int i) {
    std::cout << "second: " <<  i << std::endl;
};

void Foo(char c) {
    std::cout << "third: "  << c << std::endl;
};  



int main()
{
    int x = 9;
    int *y = &x;

    Foo();
    Foo(5);
    Foo('5');

    Foo(*y);
    float k = 9.0;
    Foo((int)k);
    Foo((char)NULL);
    unsigned char f = 'h';
    Foo((char)f);



    return 0;
}

