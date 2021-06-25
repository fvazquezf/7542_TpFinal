#include <iostream>
#include "Weapon.h"

Weapon::Weapon(std::map<uint8_t, SdlTexture> &weaponTextureMap)
: weaponTextureMap(weaponTextureMap),
  currentWeapon(KNIFE){
}

Weapon::~Weapon() {
}

void Weapon::changeWeapon(uint8_t id) {
    if (!weaponTextureMap.count(id)){
        return;
    }
    this->currentWeapon = id;
}

void Weapon::draw(float playerX, float playerY, float playerAngle, Camera &cam) {
    if (currentWeapon == 0){
        playerX -= 0;
        playerY -= 0.5;
    }
    cam.renderWeapon(playerX, playerY, playerAngle, 32, 32, weaponTextureMap.at(0));
}
