#include <iostream>
//#include <stdio.h>

// struct X
// {
//    // explicit X(); // Initialization function without parameters is named default constructor (often abbreviated as: default ctor).
//     explicit X(int a_, int b_ = 8); // Regular (non default) Ctor.
//     ~X(); //Deinitialization function is called destructor (Dtor).
//     X(const X& other_); //Copy initialization function is called copy costructor or CCtor.
//     /*X& operator=(const X& other_); //Assignment operator.*/

//     int m_a;
//     const int m_b;

//     int getElemA();
// };


// struct Y
// {
//     X m_x; 
//     int m_i;
//     explicit Y();
//     Y& operator=(const Y& other_);
// };

// Y::Y():m_x(5,6), m_i(4){}
//  Y& Y::operator=(const Y& other_){
//     this->m_i = other_.m_i;
//     this->m_x.m_a = other_.m_x.m_a;
//  }


// /*X::X(): m_a(3), m_b(4) //Implementation of the default Ctor. Why the X::X? The code after the colon is called an initialization list.
// {
//     // m_a = 3; 
//     // m_b = 4;
//     std::cout << "this:" << this <<
//             " X default Ctor. m_a:" << m_a << 
//             " m_b:" << m_b << std::endl;
// }*/

// int X ::getElemA(){
//     return m_a;
// }

// X::X(int a_, int b_): m_a(a_), m_b(b_) //Implementation of the second Ctor. 
// {
//     std::cout<< "this:" << this <<
//         " X int int Ctor. m_a:" << m_a << 
//         " m_b:" << m_b << std::endl;
// }

// X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b) //Implementation of the copy Ctor.
// {
//     std::cout<< "this:" << this <<
//         " X copy Ctor. m_a:" << m_a << 
//         " m_b:" << m_b << std::endl;
// }

// /*X& X::operator=(const X& other_)
// {
//     m_a= other_.m_a;
//     //  m_b= other_.m_b;
//     std::cout << "this:" << this <<
//         " X assignment operator. m_a:" << m_a << 
//         " does not change m_b:" << m_b << std::endl;    
//     return *this;
// }*/

// X::~X()
// {
//     std::cout << "this:" << this <<
//         " X Dtor. m_a:" << m_a << 
//         " m_b:" << m_b << std::endl;    
// }

  template<typename T>
    T max(T a, T b){
        return (a > b) ? a : b;
    }

int main()
{
    /*X x1;*/
    // X x2(7);
    // X *px = new X(x2);
   /* px->operator= x1;
    px->m_a = 2;

     std::cout << "this x2:" <<
        " m_a:" << x2.m_a << 
        " m_b:" << x2.m_b << std::endl; */

    // X x3(9,10);
   /* X x4(x1);*/
    // int z = x3.getElemA();
    //  std::cout << z << " get alm" << std::endl; 


    /*x1 = x3;
     std::cout << "size: " << sizeof(X) << std::endl;    
    delete px; px = 0;
     double* xp= new double[10];
     std::cout << "xp[2]: " << &(xp[2]) << " value: " << xp[2] << std::endl; 
     std::cout << "xp[3]: " << &(xp[3]) << " value: " << xp[3] << std::endl; 
    delete[] xp;*/

//    Y y1;
//     y1.m_x.m_a=250;
//     Y y2(y1);
//     Y y3;

//     y3=y1;

const int i = 3;
int *ip = const_cast<int*> (&i);
//*ip = 5;

std::cout << max(i, *ip) << std::endl;
//printf("%d\n", i);
    return 0;
    
  
