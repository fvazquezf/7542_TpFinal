#include "Armory.h"


Armory::Armory(){
    arsenal.emplace(std::piecewise_construct,
                        std::forward_as_tuple(0),
                        std::forward_as_tuple(new Knife()));

    arsenal.emplace(std::piecewise_construct,
                    std::forward_as_tuple(2),
                    std::forward_as_tuple(new Pistol()));
    currentWeapon = 0;
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
    currentWeapon = weaponType;
    return 1;
}
