#include <stdexcept>
#include "Armory.h"


Armory::Armory(DroppedWeapons& droppedWeapons)
: dropped(droppedWeapons){
    arsenal.emplace(std::piecewise_construct,
                    std::forward_as_tuple(1),
                    std::forward_as_tuple(new Pistol()));

    arsenal.emplace(std::piecewise_construct,
                    std::forward_as_tuple(2),
                    std::forward_as_tuple(new Knife()));

    // precios originales del juego, ver https://www.cs2d.com/weapons.php
    // igualmente esto debe ser configurable
    prices.emplace(RIFLE, 2500);
    prices.emplace(M3, 1700);
    prices.emplace(AWP, 4750);

    currentWeapon = 2;
}


bool Armory::attack(const b2Vec2 &player, int16_t angle, const b2Vec2 &enemy){
    return arsenal[currentWeapon]->attack(player, angle, enemy);
}

std::shared_ptr<Weapon> Armory::hit(){
    return arsenal[currentWeapon];
}

bool Armory::tickCooldown(){
    return arsenal[currentWeapon]->tickCooldown();
}

void Armory::resetCooldown(){
    arsenal[currentWeapon]->resetCooldown();
}

int Armory::equipWeapon(int weaponType){
    // aca tiene que haber un chequeo para ver si es valida esa weapon
    // si no compro una primary, deberia devolver falso, o el codigo que sea
    if (arsenal.count(weaponType) != 0)
        currentWeapon = weaponType;
    else {
        return -1;
    }
    return arsenal.at(currentWeapon)->getWeaponCode();
}

void Armory::dropPrimary(const b2Vec2& playerPosition){
    if (arsenal.count(0) > 0){
        dropped.dropWeapon(arsenal.at(0)->getWeaponCode(), playerPosition);
        arsenal.erase(0);
    }
}

bool Armory::tryBuying(uint8_t weaponCode, int& playerMoney, const b2Vec2& playerPosition) {
    int weaponPrice = prices.at(weaponCode);
    if (playerMoney >= weaponPrice){
        playerMoney -= weaponPrice;
        if (arsenal.count(0) > 0){
            dropped.dropWeapon(arsenal.at(0)->getWeaponCode(), playerPosition);
        }
        arsenal[0] = Weapon::getArmoryWeapon(weaponCode);
        return true;
    }
    return false;
}

bool Armory::pickUpWeapon(const b2Vec2& position){
    int8_t pickedWeapon = dropped.pickUpAnyIfClose(position);
    if (pickedWeapon == -1){
        return false;
    } else {
       if (arsenal.count(0) > 0){
           dropped.dropWeapon(arsenal.at(0)->getWeaponCode(), position);
       }
       arsenal[0] = Weapon::getArmoryWeapon(pickedWeapon);
       return true;
    }
}

Armory::Armory(Armory &&other) noexcept
: arsenal(std::move(other.arsenal)),
  prices(std::move(other.prices)),
  dropped(other.dropped){
}

Armory &Armory::operator=(Armory &&other) noexcept {
    if (this == &other){
        return *this;
    }
    arsenal = std::move(other.arsenal);
    prices = std::move(other.prices);
    return *this;
}
