#include <iostream>

class A {
public:
    static void F() { 
        std::cout << "a.f" << std::endl; 
    }
    
    void G() { 
        std::cout << "a.g" << std::endl; 
    }

    virtual void H() { 
        std::cout << "a.h" << std::endl; 
    }
};

class B : public A {
public:
    static void F() { 
        std::cout << "b.f" << std::endl; 
    }
    
    void G() { 
        std::cout << "b.g" << std::endl; 
    }

    void H() override { 
        std::cout << "b.h" << std::endl; 
    }
};

int main() {
    A a1;
    B b1;
    A* b2 = new B();

    a1.F();  // Static function should be called using class name
    a1.G();
    a1.H();

    b1.F();  // Static function should be called using class name
    b1.G();
    b1.H();

    b2->F();  // Static function cannot be called on a pointer to an instance
    b2->G();
    b2->H();

    delete b2;  // Free allocated memory
    return 0;
}
