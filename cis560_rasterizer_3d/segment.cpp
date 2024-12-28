#include "segment.h"

Segment::Segment(const std::array<float, 2>& startPoint, const std::array<float, 2>& endPoint):
    startPoint(startPoint), endPoint(endPoint)
{}

bool Segment::isIntersection(float* x, float y){
    // if startpoint y == endpoint y
    if(startPoint[1] == endPoint[1]){
        return false;
    }

    //if y less than the min y or y larger than the max y
    float y_min = std::min(startPoint[1], endPoint[1]);
    float y_max = std::max(startPoint[1], endPoint[1]);

    if( y < y_min || y> y_max){
        return false;
    }

    //calculate the value of x
    *x = startPoint[0] + (y- startPoint[1])/(endPoint[1]-startPoint[1])*(endPoint[0] - startPoint[0]);

    return true;
}
