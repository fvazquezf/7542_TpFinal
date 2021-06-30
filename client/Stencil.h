#ifndef STENCIL_H
#define STENCIL_H


#include <cstdint>
#include "sdlwrap/SdlWindow.h"

class Stencil {
private:
    SdlWindow& window;
    uint16_t coneAngle;
    float circleRadius;
    uint8_t stencilOpacity;
public:
    Stencil(SdlWindow& window, uint16_t coneAngle, float circleRadius, uint8_t opacity);

    void applyFilter(int16_t playerAngle);

    ~Stencil();
};


#endif
