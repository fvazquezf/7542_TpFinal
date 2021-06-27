#include <iostream>
#include "Weapon.h"
#include "../anim/Character.h"

Weapon::Weapon(std::map<uint8_t, SdlTexture> &weaponTextureMap)
: weaponTextureMap(weaponTextureMap),
  currentWeapon(KNIFE){
}

Weapon::~Weapon() {
}

bool Weapon::changeWeapon(uint8_t id) {
    if (!weaponTextureMap.count(id)){
        return false;
    }
    this->currentWeapon = id;
    return true;
}

void Weapon::draw(float playerX, float playerY, float playerAngle, Camera &cam) {
    if (currentWeapon == KNIFE){
        playerX -= 0;
        playerY -= 0.5;
    } else if (currentWeapon == PISTOL){
        playerX -= 0;
        playerY -= 0.5;
    } else if (currentWeapon == AK47){
        playerX -= 0;
        playerY -= 0.5;
    } else if (currentWeapon == AWP){
        playerX -= 0;
        playerY -= 0.5;
    } else if (currentWeapon == BOMB){
        playerX -= 0;
        playerY -= 0.5;
    }
    cam.renderWeapon(playerX, playerY, playerAngle, 32, 32,
                     weaponTextureMap.at(currentWeapon));
}

Weapon::Weapon(Weapon &&other) noexcept
: weaponTextureMap(other.weaponTextureMap),
  currentWeapon(other.currentWeapon){
}

Weapon &Weapon::operator=(Weapon &&other) noexcept {
    if (this == &other){
        return *this;
    }

    currentWeapon = other.currentWeapon;
    return *this;
}

void Weapon::animate(Character &character) {
    if (currentWeapon == KNIFE){
        // i controla el numero de frames
        for (int i = 0; i <= 10; ++i){
            int16_t angle = parabolicMotion(i);
            auto offset = std::make_tuple(0, 0, angle);
            character.pushPositionOffset(std::move(offset));
        }
    }
}

int16_t Weapon::parabolicMotion(int nFrame) {
    return ((-MAX_ROT_KNIFE)/25.0f) * nFrame*nFrame + 2.0f * MAX_ROT_KNIFE/5.0f * nFrame;
}
