#include<cstdio>

class X
{
public:
    explicit X(int a_);
    void Foo();
   int getA() const { return m_a;};

private:
    int m_a;
};

X::X(int a_)
    : m_a(a_)
{
}

void X::Foo()
{
    printf("%d\n", m_a);
}

void Foo(const X &x_)
{
    printf("%d\n", x_.getA());
}

int main()
{
    X x1(1);

    x1.Foo();
    printf("%d\n", x1.getA());
    Foo(x1);

    return 0;
}