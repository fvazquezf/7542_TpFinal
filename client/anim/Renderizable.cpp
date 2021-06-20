#include "Renderizable.h"

Renderizable::Renderizable(SdlTexture& texture, float posX, float posY)
: texture(texture),
  posX(posX),
  posY(posY){
}

Renderizable::~Renderizable(){
}

void Renderizable::updatePosition(float x, float y) {
    posX = x;
    posY = y;
}
