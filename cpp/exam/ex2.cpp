#include <iostream>
   using namespace std;

   class Base
   {
   public:
    //Base(): m_i(0), m_iptr(&m_i) {  std::cout << "Base default ctor()"<< std::endl;};
       Base(int i): m_i(i), m_iptr(&m_i) { std::cout << "Base ctor()"<< std::endl;}
       
      virtual void foo() { cout << "Base::foo()" << endl; cout << *(m_iptr) << endl; }
       virtual void bar() { cout << m_i << endl; }
      

  protected:
    //virtual ~Base() = 0;

  private:
      int m_i;
      int *m_iptr;
  };

 // inline Base::~Base() {}

  class Derived: public Base
  {
  public:
    Derived(): Base(0), m_c(0), m_c2(0) {}
      Derived(int i, char c): m_c(c), Base(i), m_c2(c) {}
      Derived(const Derived &d): Base(d), m_c(d.m_c), m_c2(d.m_c2) {}
      void bar() { foo(); Base::foo(); }
    void foo() override {  cout << "Derived::foo()" << endl;cout << m_c << endl; }

  private:
    char m_c, m_c2;
  };

 class OtherDerived: public Base
  {
    public:
    OtherDerived(): Base(0) {}
    ~OtherDerived(){
      cout << "OtherDerived dtor" << endl;}
  };

  enum testEneum
  {
    T1 = 1,
    T2
  };

  class G
  {
    public:
      G() {m_b = T1; cout << "G Ctor" << endl;}
      ~G() { cout << "G Dtor" << endl;}
    private:
      //onst int m_a;
      testEneum m_b;
  };

  int main(int argc, char **argv)
  {
    Derived d;
    Base& b = d;
    b.foo();

        return 0;
 }