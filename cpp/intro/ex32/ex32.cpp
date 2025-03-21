#include <iostream> // cout

using namespace std;
class B
{
public:
    B(int a_ = 8):m_a(a_){ cout << "B::Ctor" << endl; }    
   virtual ~B(){ cout << "B::Dtor" << endl; }
//Java style is not allowed in our coding convention
    virtual void Print1() const;
    void Print2() const;
    virtual void Print3() const;
private:
    int m_a;
};

void B::Print1() const
{ 
    cout << "B::Print1 B::m_a - " << m_a << endl;
}

void B::Print2() const
{
    cout << "B::Print2" << endl;
}

void B::Print3() const
{ 
    cout << "B::Print3" << endl; 
}    

class X: public B
{
public:
    X():m_b(0) { cout<< "X::Ctor" << endl; }

    ~X(){ cout << "X::Dtor" << endl;}

    virtual void Print1(int x = 7)const
    { 
        cout << "X::Print1 X::m_b - " << m_b << x << endl;
        B::Print1();
        cout << "X::Print1 end" << endl; 
    }

    void Print2() const { cout << "X::Print2" << endl; }
private:
    int m_b;
};

int main()
{
    B *b1= new B;
    B *b2= new X;

    cout<< endl << "main b1:" << endl;
    b1->Print1();
    b1->Print2();
    b1->Print3();

    cout << endl << "main b2:" << endl;
    b2->Print1();
    b2->Print2();
    b2->Print3();

    X *xx= static_cast<X*>(b2);
    cout << endl << "main xx:" << endl;
    xx->Print1();
    xx->Print2();
    b2->Print2();

    delete b1;
    delete b2;

    return 0;
}