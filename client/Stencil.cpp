#include <iostream>
#include "Stencil.h"
#include "sdlwrap/SdlTexture.h"

Stencil::Stencil(SdlWindow &window,
                 uint16_t coneAngle,
                 float circleRadius,
                 uint8_t opacity,
                 uint8_t triangleBrightness,
                 bool stencilOn)
: window(window),
  circleRadius(circleRadius),
  stencilOpacity(opacity),
  triangleBrightness(triangleBrightness),
  stencilOn(stencilOn) {
    height = std::sqrt(std::pow(window.getHeight(), 2) + std::pow(window.getWidth(), 2));
    base = 2 * height * tan((coneAngle * 3.1415 / 180) / 2);
}


Stencil::~Stencil() {

}

// triangulo isoceles (2 angulos iguales)
// la altura es sqrt((h/2)^2 + (w/2)^2)
// (la diagonal de la pantalla/2, siempre queda afuera de la vista)
// el punto principal siempre esta en la mitad (w/2, h/2)
void Stencil::createStencilTexture(int16_t playerAngle) {
    if (!stencilOn) {
        return;
    }

    float dirX = sin(playerAngle * 3.1415 / 180); // direccion en X de la mira del jugador
    float dirY = -cos(playerAngle * 3.1415 / 180); // direccion en Y de la mira del jugador
    float xBase = (window.getWidth() / 2) + height * dirX; // base del triangulo en X
    float yBase = (window.getHeight() / 2) + height * dirY; // base del triangulo en Y
    float basePerpendicularX = (base / 2) * -dirY; // direccion perpendicular al punto de la base (en X)
    float basePerpendicularY = (base / 2) * dirX; // direccion perpendicular al punto de la base (en Y)
    // el angulo del cono determina la longitud de la base, eso se calcula solo una vez
    window.drawCenteredTriangle(window.getWidth()/2, window.getHeight()/2,
                                xBase + basePerpendicularX,
                                yBase + basePerpendicularY,
                                xBase - basePerpendicularX,
                                yBase - basePerpendicularY,
                                0xff, 0xff, 0xff,
                                triangleBrightness);
    window.drawCenteredCircle(circleRadius, triangleBrightness);
    window.drawRectangle(stencilOpacity, window.getWidth(), window.getHeight());
}
