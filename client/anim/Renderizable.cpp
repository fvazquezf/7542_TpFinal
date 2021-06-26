#include "Renderizable.h"

Renderizable::Renderizable(SdlTexture& texture, float posX, float posY)
: texture(texture),
  posX(posX),
  posY(posY),
  angle(0){
}

Renderizable::~Renderizable(){
}

void Renderizable::updatePosition(float x, float y) {
    posX = x;
    posY = y;
}

void Renderizable::updateAngle(int16_t newAngle) {
    angle = newAngle;
}

Renderizable::Renderizable(Renderizable &&other) noexcept
: texture(other.texture),
  posX(other.posX),
  posY(other.posY),
  angle(other.angle){
}

Renderizable &Renderizable::operator=(Renderizable &&other) noexcept {
    if (this == &other){
        return *this;
    }

    posX = other.posX;
    posY = other.posY;
    angle = other.angle;
    return *this;
}
