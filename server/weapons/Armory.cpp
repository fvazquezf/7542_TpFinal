#include <stdexcept>
#include "Armory.h"
#include "../../common/ConfigVariables.h"


Armory::Armory(DroppedWeapons& droppedWeapons, const std::map<int, int>& matchConfig)
: dropped(droppedWeapons){
    arsenal.emplace(std::piecewise_construct,
                    std::forward_as_tuple(1),
                    std::forward_as_tuple(new Pistol(matchConfig.at(PISTOL_AMMO),
                                                    matchConfig.at(PISTOL_RANGE), 
                                                    matchConfig.at(PISTOL_ACCURACY),
                                                    matchConfig.at(PISTOL_DAMAGE))));

    arsenal.emplace(std::piecewise_construct,
                    std::forward_as_tuple(2),
                    std::forward_as_tuple(new Knife(matchConfig.at(KNIFE_RANGE), 
                                                    matchConfig.at(KNIFE_ACCURACY),
                                                    matchConfig.at(KNIFE_DAMAGE),
                                                    matchConfig.at(KNIFE_FIRERATE))));
                                                

    prices.emplace(AWP, matchConfig.at(AWP_PRICE));
    prices.emplace(RIFLE, matchConfig.at(RIFLE_PRICE));
    prices.emplace(M3, matchConfig.at(SHOTGUN_PRICE));
    
    awp = std::shared_ptr<Weapon>(new Awp(matchConfig.at(AWP_AMMO), 
                                          matchConfig.at(AWP_RANGE), 
                                          matchConfig.at(AWP_ACCURACY), 
                                          matchConfig.at(AWP_DAMAGE),
                                          matchConfig.at(AWP_FIRERATE)));
    
    rifle = std::shared_ptr<Weapon>(new Rifle(matchConfig.at(RIFLE_AMMO), 
                                              matchConfig.at(RIFLE_RANGE), 
                                              matchConfig.at(RIFLE_ACCURACY), 
                                              matchConfig.at(RIFLE_DAMAGE),
                                              matchConfig.at(RIFLE_FIRERATE)));

    shotgun = std::shared_ptr<Weapon>(new Shotgun(matchConfig.at(SHOTGUN_AMMO), 
                                                  matchConfig.at(SHOTGUN_RANGE), 
                                                  matchConfig.at(SHOTGUN_ACCURACY), 
                                                  matchConfig.at(SHOTGUN_DAMAGE)));


    currentWeapon = 2;
}


bool Armory::attack(const b2Vec2 &player, int16_t angle, const b2Vec2 &enemy){
    return arsenal[currentWeapon]->attack(player, angle, enemy);
}

void Armory::reload(){
    arsenal.at(currentWeapon)->reload();
}

std::shared_ptr<Weapon> Armory::hit(){
    return arsenal[currentWeapon];
}

bool Armory::canShoot(){
    return arsenal[currentWeapon]->canShoot();
}

void Armory::tickCooldown(){
    arsenal[currentWeapon]->tickCooldown();
}

void Armory::resetCooldown(){
    arsenal[currentWeapon]->resetCooldown();
}

void Armory::giveBomb(std::shared_ptr<Weapon> bomb){
    arsenal[3] = bomb;
}

bool Armory::startPlanting(){
    if (arsenal.count(3) == 0) return false;
    currentWeapon = 3;
    Bomb* bomb = static_cast<Bomb*>(arsenal[3].get());
    bomb->startPlanting();
    return true;
}

bool Armory::stopPlanting(){
    if (arsenal.count(3) == 0) return false;
    Bomb* bomb = static_cast<Bomb*>(arsenal[3].get());
    if (bomb->isActive()) {
        arsenal.erase(3);
        currentWeapon = 1;
    } 
    if (bomb->isPlanting()){
        bomb->stopPlanting();
    }
    return true;
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
    currentWeapon = 2;
}

bool Armory::tryBuying(uint8_t weaponCode, int& playerMoney, const b2Vec2& playerPosition) {
    int weaponPrice = prices.at(weaponCode);
    if (playerMoney >= weaponPrice){
        playerMoney -= weaponPrice;
        if (arsenal.count(0) > 0){
            dropped.dropWeapon(arsenal.at(0)->getWeaponCode(), playerPosition);
        }
        selectWeapon(weaponCode);
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
       selectWeapon(pickedWeapon);
       return true;
    }
}

int Armory::getClip() const {
    return arsenal.at(currentWeapon)->getClip();
}


Armory::Armory(Armory &&other) noexcept
: arsenal(std::move(other.arsenal)),
  prices(std::move(other.prices)),
  dropped(other.dropped),
  currentWeapon(2){
}

Armory &Armory::operator=(Armory &&other) noexcept {
    if (this == &other){
        return *this;
    }
    arsenal = std::move(other.arsenal);
    prices = std::move(other.prices);
    currentWeapon = 2;
    return *this;
}

void Armory::selectWeapon(uint8_t weaponCode){
    switch (weaponCode) {
        case RIFLE:
            arsenal[0] = rifle;
            break;
        case M3:
            arsenal[0] = shotgun;
            break;
        case AWP:
            arsenal[0] = awp;
            break;
    }
}
