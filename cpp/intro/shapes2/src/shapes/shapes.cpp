//#include <string.h>
#include "shapes.hpp"

#include <cmath> //pow
#include <iostream> // cout



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




int Shape:: getId(){
    return m_id;
}  

std::string Shape::getName(){
    return m_name;
} 

Shape::Shape(): m_id(10){
     m_name ="un_named";
}
Shape::Shape(int id, std::string name):m_id(id) , m_name(name){
    
}


Qudraliteral::Qudraliteral(Coordinate2Dim topL,
                                Coordinate2Dim topR,
                                Coordinate2Dim bottomL,
                                Coordinate2Dim bottomR): topLeft(topL), topRight(topR), bottomLeft(bottomL), bottomRight(bottomR)
{//add input validation 
}


double Qudraliteral::perimeter(void){
    return 2 * (topLeft.calculateDistance(topRight) + 
            topRight.calculateDistance(bottomRight));
            
}

double Qudraliteral ::surfaceArea(void){
    return topLeft.calculateDistance(topRight) * 
            topRight.calculateDistance(bottomRight);
}



/*********************************************/

Triengel::Triengel(Coordinate2Dim top,
                                Coordinate2Dim bottomL,
                                Coordinate2Dim bottomR): top(top), bottomLeft(bottomL), bottomRight(bottomR)
{//add input validation 
}

double Triengel::perimeter(void){
    return top.calculateDistance(bottomRight) + 
            top.calculateDistance(bottomLeft) + 
            bottomLeft.calculateDistance(bottomRight);
            
}

double Triengel ::surfaceArea(void){
    return (top.calculateDistance(bottomLeft) * 
            bottomLeft.calculateDistance(bottomRight) ) / 2;
}

int main(){
    Coordinate2Dim bl(0,0);
    Coordinate2Dim br(0,10);
    Coordinate2Dim tl(10,0);
    Coordinate2Dim tr(10,10);

    Qudraliteral qudr(tl,tr,bl,br);
    std::cout << " preimeter is: " << qudr.perimeter() << std::endl;
    std::cout << " surfaceArea is: " << qudr.surfaceArea() << std::endl;
    std::cout << " name is: " << qudr.getName() << std::endl;

    Triengel trie(tl,bl,br);
    std::cout << " preimeter is: " << trie.perimeter() << std::endl;
    std::cout << " surfaceArea is: " << trie.surfaceArea() << std::endl;
    std::cout << " name is: " << trie.getName() << std::endl;


}
