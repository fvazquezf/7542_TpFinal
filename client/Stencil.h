#ifndef STENCIL_H
#define STENCIL_H


#include <cstdint>
#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"

class Stencil {
private:
    SdlWindow& window;
    float circleRadius;
    uint8_t stencilOpacity;
    uint8_t triangleBrightness;
    float height;
    float base;
public:
    Stencil(SdlWindow& window,
            uint16_t coneAngle,
            float circleRadius,
            uint8_t opacity,
            uint8_t triangleBrightness);
    void createStencilTexture(int16_t playerAngle);

    ~Stencil();
};


#endif
