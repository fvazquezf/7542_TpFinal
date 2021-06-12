#include <iostream>
#include "Knife.h"

Knife::Knife(SdlTexture& knifeTex)
: Weapon(knifeTex){
}

void Knife::draw(int posX, int posY, float angle) {
    Area src(0, 0, 32, 32);
    Area dst(posX, posY, 32, 32);
    int x, y;
    SDL_GetMouseState(&x, &y);
    float ang = atan2((float) (posY - y), (float) (posX - x)) * 180 / PI;
    texture.render(src, dst, ang, SDL_FLIP_NONE);
}

void Knife::makeSound() {
    std::cout << "SLASH\n";
}

Knife::~Knife() {
}
