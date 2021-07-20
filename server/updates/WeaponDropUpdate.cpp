#include "WeaponDropUpdate.h"

WeaponDropUpdate::WeaponDropUpdate(uint8_t code, size_t dropIdentifier, float posX, float posY, bool drop)
: weaponCode(code),
  dropIdentifier(dropIdentifier),
  x(posX),
  y(posY),
  drop(drop) {
}

WeaponDropUpdate::~WeaponDropUpdate() {

}

void WeaponDropUpdate::serialize(std::function<void(std::vector<unsigned char>)> &callback) {
    protocol.updateDrop(drop, dropIdentifier, weaponCode, x, y, callback);
}
