#include <iostream>

enum E { AA, BB, CC, DD};
enum E2 { TT,KK};

class A{
  public:
  A(int value) : m_x(value) {}
  bool operator>(const A& other) const { return m_x > other.m_x; }
   int m_x;
  private:
    A(const A&) = delete;
    A& operator=(const A&) = delete;
   
};

//template<typename T>
// void foo(T t) 
// {
//  std::cout << "Generic for"<< typeid(t).name() << std::endl;

// }

// template<>
// void foo<int>(int t) 
// {
//  std::cout << "int for"<< std::endl;

// }

//   int i = 5;
//   int && ir = 6;
//   int& ip = ir; 
// void foo(int) {
//   std::cout << "int" << std::endl;
// }
// template<typename T>
// void foo(T) {
//   std::cout << "template" << std::endl;
// }

void foo(const double& value) {
  std::cout << "const double" << value <<std::endl;
}

void bar(double& value) {
  std::cout << "double" << value << std::endl;
}
  
int main(){

  // enum E e = static_cast<E>(2);
  // enum E2 e2 =static_cast<E2>(CC);
  // enum E2 e22 = KK;
  // //++e;
  // int i = e;

  // std::cout << e2<< std::endl;  
  // if(e2 == TT) std::cout << "true" << std::endl;
  
  // foo(4.2);
  // foo(4);
  // foo<int>(5);
 
  // int j = 9;
  // ip = j;
  int i = 5;
  foo((i));
  bar(reinterpret_cast<double&> (i));
  return 0;
}