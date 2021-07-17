#include <memory>
#include "Weapon.h"


Weapon::Weapon(uint8_t weaponCode, int ammo, int range, int damage, int bounty):
    ammo(ammo),
    clip(ammo),
    damage(damage),
    bounty(bounty),
    weaponCode(weaponCode){
    this->range = static_cast<double>(range)/100;
    cooldown = 0;
}

Weapon::~Weapon() {

}

void Weapon::tickCooldown(){
    if (cooldown != 0) cooldown--;
}

void Weapon::reload(){
    clip = ammo;
}

int Weapon::getBounty(){
    return bounty;
}

uint8_t Weapon::getWeaponCode(){
    return weaponCode;
}

int Weapon::getClip(){
    return clip;
}

