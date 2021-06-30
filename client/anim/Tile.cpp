#include "Tile.h"
#include "../Camera.h"

Tile::Tile(SdlTexture &texture, float posX, float posY)
: Renderizable(texture, posX, posY) {
}

void Tile::render(Camera &camera, size_t iteration) {
    // size de una tile
    Area src(0, 0, 32, 32);
    if (camera.isVisible(posX, posY) ){
        camera.renderInSight(texture, src, posX, posY, 0);
    }
}

Tile::~Tile() {

}

Tile::Tile(Tile &&other) noexcept
: Renderizable(std::move(other)){
}

Tile &Tile::operator=(Tile &&other) noexcept {
    if (this == &other){
        return *this;
    }

    posX = other.posX;
    posY = other.posY;
    return *this;
}
