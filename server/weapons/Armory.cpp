#include "Armory.h"


Armory::Armory(){
    arsenal.emplace(std::piecewise_construct,
                        std::forward_as_tuple(0),
                        std::forward_as_tuple(Knife()));

    arsenal.emplace(std::piecewise_construct,
                    std::forward_as_tuple(2),
                    std::forward_as_tuple(Pistol()));
}


bool Armory::attack(const b2Vec2 &player, int16_t angle, const b2Vec2 &enemy){
    return arsenal[currentWeapon].attack(player, angle, enemy);
}

Weapon& Armory::hit(){
    return arsenal[currentWeapon];
}

bool Armory::tickCooldown(){
    return arsenal[currentWeapon].tickCooldown();
}

void Armory::resetCooldown(){
    arsenal[currentWeapon].resetCooldown();
}

void Armory::equipKnife(){
    currentWeapon = 0;
}

int Armory::equipPrimary(){
    currentWeapon = 1;
    return true;
}

void Armory::equipSecondary(){
    currentWeapon = 2;
}

bool Armory::equipBomb(){
    currentWeapon = 3;
    return true;
}

