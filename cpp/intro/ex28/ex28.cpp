#include <iostream>
class X
{
public:
    X() : m_id(++s_cntr) {}
    int GetId() { std::cout << m_id << std::endl; return m_id;}
    static int s_cntr;
    int m_id;
private:
};

class Y
{
public:
    Y() : m_id(++s_cntr) {}
    int GetId() { std::cout << m_id << std::endl; return m_id;}
    static int getCntr(){return s_cntr;}
private:
    int m_id;
    static int s_cntr;
};

void test(const X& x){
    x.m_id++;

}

int X::s_cntr = 0;
int Y::s_cntr = 100;

int main()
{
    X x1;
    X x2;
    
     std::cout << Y::getCntr() << std::endl;

    x1.GetId();
    x2.GetId();
   

    return 0;   
}