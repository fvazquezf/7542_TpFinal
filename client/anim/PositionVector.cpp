#include "PositionVector.h"

PositionVector::PositionVector(float x, float y, int16_t angle)
: x(x), y(y), angle(angle){
}

PositionVector::~PositionVector() {
}

PositionVector::PositionVector(PositionVector &&other)
: x(other.x), y(other.y), angle(other.angle){
}

PositionVector &PositionVector::operator=(PositionVector &&other) {
    if (this == &other) {
        return *this;
    }

    x = other.x;
    y = other.y;
    angle = other.angle;
    return *this;
}
