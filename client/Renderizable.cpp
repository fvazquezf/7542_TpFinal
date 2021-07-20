#include "Renderizable.h"

Renderizable::Renderizable(SdlTexture& texture,
                           int sizeW,
                           int sizeH,
                           float posX,
                           float posY)
: texture(texture),
  sizeW(sizeW),
  sizeH(sizeH),
  posX(posX),
  posY(posY),
  angle(0) {
}

Renderizable::~Renderizable() {
}

void Renderizable::updatePosition(float x, float y) {
    posX = x;
    posY = y;
}

void Renderizable::updateAngle(int16_t newAngle) {
    angle = newAngle;
}

Renderizable::Renderizable(Renderizable &&other)
: texture(other.texture),
  sizeW(other.sizeW),
  sizeH(other.sizeH),
  posX(other.posX),
  posY(other.posY),
  angle(other.angle) {
}

Renderizable &Renderizable::operator=(Renderizable &&other)  {
    if (this == &other) {
        return *this;
    }

    posX = other.posX;
    posY = other.posY;
    angle = other.angle;
    return *this;
}
