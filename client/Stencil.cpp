#include <iostream>
#include "Stencil.h"
#include "sdlwrap/SdlTexture.h"

Stencil::Stencil(SdlWindow &window, uint16_t coneAngle, float circleRadius, uint8_t opacity)
: window(window),
  coneAngle(coneAngle),
  circleRadius(circleRadius),
  stencilOpacity(opacity){

}

void Stencil::applyFilter(int16_t playerAngle) {
    int16_t angleLow = playerAngle - coneAngle/2;
    if (angleLow > 360){
        angleLow -= 360;
    }
    int16_t angleHigh = playerAngle + coneAngle/2;
    if (angleHigh > 360) {
        angleHigh -= 360;
    }

    std::cout << angleLow << " " << angleHigh << std::endl;
    int16_t x2 = 3000 * sin(angleLow * 3.14f/180.0f);
    int16_t y2 = -3000 * cos(angleLow * 3.14f/180.0f);
    int16_t x3 = 3000 * sin(angleHigh * 3.14f/180.0f);
    int16_t y3 = -3000 * cos(angleHigh * 3.14f/180.0f);
    std::cout << x2 << " " << y2 << " " << x3 << " " << y3 << std::endl;
    window.drawCenteredTriangle(x2, y2, x3, y3, 0, 0, 0, 0);
}

Stencil::~Stencil() {

}
