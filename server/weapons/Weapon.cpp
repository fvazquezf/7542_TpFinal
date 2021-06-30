#include <memory>
#include <stdexcept>
#include "Weapon.h"
#include "Shotgun.h"
#include "Awp.h"

Weapon::Weapon(uint8_t weaponCode) {
    damage = 1;
    cooldown = 1;
    this->weaponCode = weaponCode;
}

Weapon::~Weapon() {

}

std::shared_ptr<Weapon> Weapon::getArmoryWeapon(uint8_t weaponCode) {
    switch (weaponCode) {
        case AK47:
            throw std::invalid_argument("Invalid weapon code\n");
        case M3:
            return std::shared_ptr<Weapon>(new Shotgun());
        case AWP:
            return std::shared_ptr<Weapon>(new Awp());
        default:
            throw std::invalid_argument("Invalid weapon code\n");
    }
}

uint8_t Weapon::getWeaponCode(){
    return weaponCode;
}
