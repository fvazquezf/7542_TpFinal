#include <iostream>
#include "NonMovable.h"
#include "Camera.h"

NonMovable::NonMovable(SdlTexture &texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY)
: Renderizable(texture, sizeW, sizeH, posX, posY){
    rescaling = 1;
}

void NonMovable::render(Camera &camera, size_t iteration) {
    Area src(0, 0, sizeW, sizeH);
    camera.renderInSight(texture, src, posX, posY, 0);
}

NonMovable::~NonMovable() {

}

NonMovable::NonMovable(NonMovable &&other)
: Renderizable(std::move(other)),
  rescaling(other.rescaling){
}

NonMovable &NonMovable::operator=(NonMovable &&other)  {
    if (this == &other){
        return *this;
    }
    sizeW = other.sizeW;
    sizeH = other.sizeH;
    posX = other.posX;
    posY = other.posY;
    rescaling = other.rescaling;
    return *this;
}

NonMovable::NonMovable(SdlTexture &texture, int sizeW, int sizeH, float posX, float posY, int rescaling)
: Renderizable(texture, sizeW, sizeH, posX, posY),
  rescaling(rescaling){
}
