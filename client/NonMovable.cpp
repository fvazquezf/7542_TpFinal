#include <iostream>
#include "NonMovable.h"
#include "Camera.h"

NonMovable::NonMovable(SdlTexture &texture,
           int sizeW,
           int sizeH,
           float posX,
           float posY)
: Renderizable(texture, sizeW, sizeH, posX, posY){
}

void NonMovable::render(Camera &camera, size_t iteration) {
    // size de una tile
    Area src(0, 0, sizeW, sizeH);
    if (camera.isVisible(posX, posY) ){
        camera.renderInSight(texture, src, posX, posY, 0);
    }
}

NonMovable::~NonMovable() {

}

NonMovable::NonMovable(NonMovable &&other) noexcept
: Renderizable(std::move(other)){
}

NonMovable &NonMovable::operator=(NonMovable &&other) noexcept {
    if (this == &other){
        return *this;
    }
    sizeW = other.sizeW;
    sizeH = other.sizeH;
    posX = other.posX;
    posY = other.posY;
    return *this;
}
