 
#include <assert.h>

template <typename T>
class Point
{
public:
    Point(): m_x(0), m_y(0){}
    Point(T x, T y = 0): m_x(x), m_y(y){}
    Point(const Point& other): m_x(other.m_x), m_y(other.m_y){}
    Point& operator=(const Point& other){
        m_x = other.m_x;
        m_y = other.m_y;
        return *this;}
    Point& operator+=(const Point& other){
        m_x += other.m_x;
        m_y += other.m_y;
        return *this;}
    Point& operator/=(const Point& other){
        if(other.m_x == 0 || other.m_y == 0){
            throw "division by zero";
        }
        m_x /= other.m_x;
        m_y /= other.m_y;
        return *this;
    }
    Point operator+(const Point& other) const{
        return Point(m_x + other.m_x, m_y + other.m_y); 
    }
    Point operator-(const Point& other) const{
        return Point(m_x - other.m_x, m_y - other.m_y); 
    }
    bool operator==(const Point& other) const{
        return m_x == other.m_x && m_y == other.m_y;
    }

private:
    T m_x;
    T m_y;
};

int main()
{
 Point<int> p1(5,6);
    Point<int> p2(12,18);
    Point<int> p3;
    p3 = p1 + p2;
    Point<int> p4 = p3 - p1;
    Point<int> p5(0,0);
    assert(p4==p2);
    Point<int> p6(p1);
    p6 += 2;
    assert(p6 == Point<int>(6,7));
    p2 /= 3;
    assert(p2 == Point<int>(6,9)); 
}



