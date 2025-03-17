#include <iostream>
#include "base.hpp"
using namespace std;

      Base::Base(int i): m_i(i), m_iptr(&m_i) { std::cout << "Base ctor()"<< std::endl;}

      void Base::foo() { cout << "Base::foo()" << endl; cout << *(m_iptr) << endl; }
      void Base::bar() { cout << m_i << endl; }
      inline Base::~Base() {}
      
