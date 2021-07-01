//
// Created by leogm99 on 1/7/21.
//

#include "WeaponDropUpdate.h"

WeaponDropUpdate::WeaponDropUpdate(uint8_t code, float posX, float posY, bool drop)
: weaponCode(code),
  x(posX),
  y(posY),
  drop(drop){
}

WeaponDropUpdate::~WeaponDropUpdate() {

}

void WeaponDropUpdate::serialize(std::function<void(std::vector<unsigned char>)> &callback) {

}
