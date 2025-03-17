#include <iostream>
#include "derived.hpp"
using namespace std;



    Derived::Derived(int i, char c): m_c(c), Base(i), m_c2(c) {}
    void  Derived::bar() { foo(); Base::foo(); }
    void Derived:: foo() {  cout << "Derived::foo()" << endl;cout << m_c << endl; }
   
  