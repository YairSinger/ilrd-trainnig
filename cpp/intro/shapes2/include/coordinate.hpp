#ifndef __ILRD_COORDINATE_H__
#define __ILRD_COORDINATE_H__
#include "coordinate.hpp"

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


#endif /* __ILRD_COORDINATE_H__ */