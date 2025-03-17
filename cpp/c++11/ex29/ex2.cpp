#include <iostream>

class X
{
public:
    explicit X(): m_i(0) {}
    explicit X(int i): m_i(i) {}
    explicit X(int i, int j): m_i(i + j) {}
    operator int() const { return m_i; }
    void Print() const { 
        std::cout << " Print: " <<  m_i << std::endl; 
        s_i = m_i;
    }
    void static PrintS(X& x_) { std::cout << " Print: " <<  s_i + x_.m_i << std::endl; }

private:
    int m_i;
    static int s_i;
};


class A
{
    public:
    int m_i;
    virtual int inc() { return ++m_i; }
    virtual int dec() { return --m_j; }

    protected:
    virtual int setm_j(int j_) { return m_j = j_; }

    private:
    int m_j;

};

class B :public A
{
    public:
    int m_i;
    virtual int inc() { return ++m_i + 3; }
    
    private:
    virtual int setm_j(int j_)
     { return this->setm_j(j_); }
    
};

void Fifi(X x_){
    std::cout << "Fifi: " << x_<< std::endl;
}

int main()
{
    X x1(7);
    Fifi(x1);
    Fifi(X(7));
    //Fifi(9);
    return x1 * 3;
    
    
}