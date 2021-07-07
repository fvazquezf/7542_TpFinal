#ifndef STENCIL_H
#define STENCIL_H


#include <cstdint>
#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"

class Stencil {
private:
    SdlWindow& window;
    uint16_t coneAngle;
    float circleRadius;
    uint8_t stencilOpacity;
    float height;
    float base;
    float diagonalLength;
public:
    Stencil(SdlWindow& window, uint16_t coneAngle, float circleRadius, uint8_t opacity);
    void createStencilTexture(int16_t playerAngle);
    void applyFilter();

    ~Stencil();
};


#endif
