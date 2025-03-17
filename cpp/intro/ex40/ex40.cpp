#include <iostream>

template<typename T>
class Square {
public:
    // Constructor
    Square(T sideLength) : sideLength(sideLength) {}

    // Getter for side length
    T getSideLength() const {
        return sideLength;
    }

    // Setter for side length
    void setSideLength(T newSideLength) {
        sideLength = newSideLength;
    }

     friend std::ostream& operator<< (std::ostream& os, const Square& square) {
        os << "Square with side length: " << square.sideLength;
        return os;
     }

private:
    T sideLength; // Side length of the square
};

class A
{
public:
    A(int a, std::string b) : m_a(a), m_b(b) {}
    

    friend std::ostream& operator<< (std::ostream& os, const A& a) {
        os << a.m_a * 3 << " " << a.m_b;
        return os;
    }
private:
    int m_a;
    std::string m_b;
};


int main () {
    Square<int> square(5);
    std::cout << square << std::endl;

    Square<A> square2(A(3, "hello"));
    std::cout << square2 << std::endl;
    return 0;
}