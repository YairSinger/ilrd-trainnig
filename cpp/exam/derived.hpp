#ifndef DERIVED_EX2_HPP
#define DERIVED_EX2_HPP
#include "base.hpp"

class Derived: public Base
  {
  public:
      Derived(int i, char c);
      void bar();

  private:
    void foo()override;
    char m_c, m_c2;
  };

 



#endif /* DERIVED_EX2_HPP */