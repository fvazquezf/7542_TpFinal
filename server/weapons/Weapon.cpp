#include <memory>
#include <stdexcept>
#include "Weapon.h"
#include "Shotgun.h"
#include "Awp.h"
#include "Rifle.h"

Weapon::Weapon(uint8_t weaponCode, int ammo, int range, int damage):
    weaponCode(weaponCode),
    ammo(ammo),
    damage(damage),
    clip(ammo){
    this->range = static_cast<double>(range)/100;
    cooldown = 0;
}

Weapon::~Weapon() {

}

void Weapon::reload(){
    clip = ammo;
}

uint8_t Weapon::getWeaponCode(){
    return weaponCode;
}

int Weapon::getAmmo(){
    return ammo;
}

