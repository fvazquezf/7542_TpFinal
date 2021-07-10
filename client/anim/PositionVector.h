#ifndef POSITIONVECTOR_H
#define POSITIONVECTOR_H


#include <cstdint>

class PositionVector {
public:
    PositionVector(float x, float y, int16_t angle);

    PositionVector(const PositionVector& other) = delete;
    PositionVector& operator=(const PositionVector& other) = delete;

    PositionVector(PositionVector&& other);
    PositionVector& operator=(PositionVector&& other);

    ~PositionVector();

    float x;
    float y;
    int16_t angle;
};


#endif
