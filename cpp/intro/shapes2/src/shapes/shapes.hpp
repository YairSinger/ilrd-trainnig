#ifndef __ILRD_SHAPES_H__
#define __ILRD_SHAPES_H__
#include <cstring>
#include <iostream>


class Coordinate2Dim{
    private:
        int m_x;
        int m_y;
    public:
        Coordinate2Dim(int x, int y);
        int getX();
        int getY();
        float calculateDistance(const Coordinate2Dim& other);

};


enum Color{
    BLUE,
    RED,
    YELLOW,
    BLACK,
    WHITE
};



class Shape{

    private:
      //  Color m_color;
        int m_id;
        std::string m_name;
    public:
        explicit Shape();
        explicit Shape(int id, std::string name);
        int getId();  
        std::string getName();
        virtual double perimeter(void);
        virtual double surfaceArea(void); 
            

};

class Qudraliteral:public Shape{
    public:
      double perimeter(void) override; 
      double surfaceArea(void) override; 
        explicit Qudraliteral(Coordinate2Dim topL,
                                Coordinate2Dim topR,
                                Coordinate2Dim bottomL,
                                Coordinate2Dim bottomR);
        
    
    private:
        Coordinate2Dim topLeft;
        Coordinate2Dim topRight;
        Coordinate2Dim bottomLeft;
        Coordinate2Dim bottomRight;

};

class Triengel: public Shape{
public:
       double perimeter(void) override; 
       double surfaceArea(void) override;
       explicit Triengel(Coordinate2Dim top,
                             Coordinate2Dim bottomL,
                             Coordinate2Dim bottomR);
        
    
    private:
        Coordinate2Dim top;        
        Coordinate2Dim bottomLeft;
        Coordinate2Dim bottomRight;

};

#endif /* __ILRD_SHAPES_H__ */