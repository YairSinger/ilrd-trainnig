#include <cmath> //pow
#include <iostream> // cout
#include "coordinate.hpp"


 Coordinate2Dim::Coordinate2Dim(int x, int y){
    m_x = x;
    m_y = y;
 }

  int Coordinate2Dim::getX(){
    return m_x;
  }

int Coordinate2Dim::getY(){
    return m_y;
}

 float Coordinate2Dim::calculateDistance(const Coordinate2Dim& other){
      return sqrt(pow(fabs(m_x - other.m_x), 2) + pow(fabs(m_y - other.m_y), 2));
 }


int main(){
    Coordinate2Dim a(0,3);
    Coordinate2Dim b(4,0);

    std::cout << " a is : " << a.getX() << " and: " << a.getY() << std::endl;
    std::cout << " b is : " << b.getX() << " and: " << b.getY() << std::endl;
    std::cout << " distance is : " << b.calculateDistance(a) << std::endl;
    return 0;
}