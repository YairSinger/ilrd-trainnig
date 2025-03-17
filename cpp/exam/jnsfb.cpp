#include <iostream>
using namespace std;

class A
{
    public:
        A() : m_a(5), m_iptr(&m_a) { }
        A(const A& other_) { *this = other_; }
        A& operator=(const A& other_) { m_a = other_.m_a; return *this; }
        static  void Print(const A& obj){cout << obj.m_a << endl;}

    private:
        int m_a;
        int *m_iptr;
        void foo() { cout << "Base::foo()" << endl; cout << *(m_iptr) << endl; }
};

void Print(const A& obj){cout << "global::Print" << endl;}


int main()
{
    A obj;
    Print(obj);
    A obj2(obj);
    A::Print(obj2);
    return 0;
}