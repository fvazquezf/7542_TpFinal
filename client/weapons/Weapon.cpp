#include <iostream>
#include "Weapon.h"
#include "../anim/Character.h"
#include "../SoundManager.h"

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

void Weapon::draw(float x, float y, float angle, Camera &cam) {
    x -= 0; // offsets a mano para posicionar bien las armas
    y -= 0.5;
    cam.renderWeapon(x, y, angle, WEAPON_WIDTH, WEAPON_HEIGHT,
                     weaponTextureMap.at(currentWeapon));
}

Weapon::Weapon(Weapon &&other)
: weaponTextureMap(other.weaponTextureMap),
  currentWeapon(other.currentWeapon){
}

Weapon &Weapon::operator=(Weapon &&other)  {
    if (this == &other){
        return *this;
    }

    currentWeapon = other.currentWeapon;
    return *this;
}

void Weapon::animate(Character &character, float distanceToCenter, float angle) {
    if (currentWeapon == KNIFE){
        // i controla el numero de frames
        for (int i = 0; i <= 10; ++i){
            int16_t angle = parabolicMotion(i);
            auto offset = std::make_tuple(0, 0, angle);
            character.pushPositionOffset(std::move(offset));
        }
    } else {
        std::pair<float, float> shootingRecoilDir = {-SDL_sin(angle * 3.14/180.0f), SDL_cos(angle * 3.14 / 180.0f)};
        for (int i = 0; i <= 10; ++i) {
            auto jerk = parabolicMotion(i)/1000;
            auto offset = std::make_tuple(shootingRecoilDir.first * jerk, shootingRecoilDir.second * jerk, 0);
            character.pushPositionOffset(std::move(offset));
        }
    }
    manageSound(distanceToCenter);
}

float Weapon::parabolicMotion(int nFrame) {
    return ((-MAX_ROT_KNIFE)/25.0f) * nFrame*nFrame + 2.0f * MAX_ROT_KNIFE/5.0f * nFrame;
}

void Weapon::manageSound(float distanceToCenter) const {
    if (currentWeapon == KNIFE){
        SoundManager::playSound(SoundManager::KNF_S, distanceToCenter);
    } else if (currentWeapon == PISTOL){
        SoundManager::playSound(SoundManager::GLOCK_S, distanceToCenter);
    } else if (currentWeapon == M3){
        SoundManager::playSound(SoundManager::M3_S, distanceToCenter);
    } else if (currentWeapon == AWP) {
        SoundManager::playSound(SoundManager::AWP_S, distanceToCenter);
    } else if (currentWeapon == AK47){
        SoundManager::playSound(SoundManager::AK47_S, distanceToCenter);
    }
}
