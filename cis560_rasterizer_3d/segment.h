#ifndef SEGMENT_H
#define SEGMENT_H
#include <glm/glm.hpp>
#include <array>

class Segment
{
public:
    std::array<float, 2> startPoint;
    std::array<float, 2> endPoint;

public:
    //avoid create new copy, and keep input value safe, so const and &
    Segment(const std::array<float, 2>& startPoint, const std::array<float, 2>& endPoint);
    bool isIntersection(float* x, float y);
};

#endif // SEGMENT_H
