#include <iostream> // cout

struct X
{
    X(int a_, int b_);

    void Inc();
    void Dec();

    int m_a;
    int m_b;
};

X::X(int a_, int b_): m_a(a_), m_b(b_)
{}

void X::Inc()
{
    ++m_a;
    std::cout << "m_a: " << m_a << std::endl;
    ++m_b;
    std::cout << "m_b: " << m_b << std::endl;

}

void X::Dec()
{
    --m_a;
    std::cout << "m_a: " << m_a << std::endl;
    --m_b;
     std::cout << "m_b: " << m_b << std::endl;
}

void Inc()
{
    std::cout << "inc was called" << std::endl;
}

int main()
{
    X x1(7,-55);

    Inc();
    x1.Inc();
    x1.Inc();
    X x2(x1);
    x2.Dec();

    return 0;
}