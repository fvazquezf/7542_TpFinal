#include "Weapon.h"

Weapon::Weapon(SdlTexture &texture)
: texture(texture){
}

Weapon::~Weapon() {
}

void Weapon::draw(int posX, int posY) {
    draw(posX, posY, 0);
}
