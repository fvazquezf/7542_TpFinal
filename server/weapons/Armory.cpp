#include <stdexcept>
#include "Armory.h"
#include "../../common/ConfigVariables.h"


Armory::Armory(std::shared_ptr<Bomb> bomb, DroppedWeapons& droppedWeapons, const std::map<int, int>& matchConfig)
: dropped(droppedWeapons),
  bomb(bomb){
    arsenal.emplace(std::piecewise_construct,
                    std::forward_as_tuple(SECONDARY),
                    std::forward_as_tuple(new Pistol(matchConfig.at(PISTOL_AMMO),
                                                    matchConfig.at(PISTOL_RANGE), 
                                                    matchConfig.at(PISTOL_ACCURACY),
                                                    matchConfig.at(PISTOL_DAMAGE),
                                                    matchConfig.at(PISTOL_BOUNTY))));

    arsenal.emplace(std::piecewise_construct,
                    std::forward_as_tuple(MELEE),
                    std::forward_as_tuple(new Knife(matchConfig.at(KNIFE_RANGE), 
                                                    matchConfig.at(KNIFE_ACCURACY),
                                                    matchConfig.at(KNIFE_DAMAGE),
                                                    matchConfig.at(KNIFE_FIRERATE),
                                                    matchConfig.at(KNIFE_BOUNTY))));
                                                

    prices.emplace(AWP, matchConfig.at(AWP_PRICE));
    prices.emplace(RIFLE, matchConfig.at(RIFLE_PRICE));
    prices.emplace(M3, matchConfig.at(SHOTGUN_PRICE));
    
    awp = std::shared_ptr<Weapon>(new Awp(matchConfig.at(AWP_AMMO), 
                                          matchConfig.at(AWP_RANGE), 
                                          matchConfig.at(AWP_ACCURACY), 
                                          matchConfig.at(AWP_DAMAGE),
                                          matchConfig.at(AWP_FIRERATE),
                                          matchConfig.at(AWP_BOUNTY)));
    
    rifle = std::shared_ptr<Weapon>(new Rifle(matchConfig.at(RIFLE_AMMO), 
                                              matchConfig.at(RIFLE_RANGE), 
                                              matchConfig.at(RIFLE_ACCURACY), 
                                              matchConfig.at(RIFLE_DAMAGE),
                                              matchConfig.at(RIFLE_FIRERATE),
                                              matchConfig.at(RIFLE_BOUNTY)));

    shotgun = std::shared_ptr<Weapon>(new Shotgun(matchConfig.at(SHOTGUN_AMMO), 
                                                  matchConfig.at(SHOTGUN_RANGE), 
                                                  matchConfig.at(SHOTGUN_ACCURACY), 
                                                  matchConfig.at(SHOTGUN_DAMAGE),
                                                  matchConfig.at(SHOTGUN_BOUNTY)));


    currentWeapon = MELEE;
}


bool Armory::attack(const b2Vec2 &player, int16_t angle, const b2Vec2 &enemy){
    return arsenal[currentWeapon]->attack(player, angle, enemy);
}

void Armory::reload(){
    arsenal.at(currentWeapon)->reload();
}

int Armory::bounty(){
    return arsenal.at(currentWeapon)->getBounty();
}


std::shared_ptr<Weapon> Armory::hit(){
    return arsenal[currentWeapon];
}

bool Armory::canShoot(bool isAttacking){
    return arsenal[currentWeapon]->canShoot(isAttacking);
}

void Armory::tickCooldown(){
    arsenal[currentWeapon]->tickCooldown();
}

void Armory::resetCooldown(){
    arsenal[currentWeapon]->resetCooldown();
}

void Armory::giveBomb(){
    selectWeapon(BOMB);
}

bool Armory::startPlanting(int id, const b2Vec2& pos){
    if (arsenal.count(EXPLOSIVE) == 0) return false;
    currentWeapon = EXPLOSIVE;
    bomb->startPlanting(id, pos);
    return true;
}

bool Armory::startDefusing(){
    bomb->startDefusing();
    return false;
}

bool Armory::stopPlanting(){
    if (arsenal.count(EXPLOSIVE) == 0) return false;
    if (bomb->getState() == ACTIVE) {
        arsenal.erase(EXPLOSIVE);
        currentWeapon = MELEE;
    } 
    if (bomb->getState() == PLANTING){
        bomb->stopPlanting();
    }
    return true;
}

bool Armory::stopDefusing(){
    bomb->stopDefusing();
    return false;
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

bool Armory::tryBuying(uint8_t weaponCode, int& playerMoney, const b2Vec2& playerPosition) {
    int weaponPrice = prices.at(weaponCode);
    if (playerMoney >= weaponPrice){
        playerMoney -= weaponPrice;
        if (arsenal.count(PRIMARY) > 0){
            dropped.dropWeapon(arsenal.at(PRIMARY)->getWeaponCode(), playerPosition);
        }
        selectWeapon(weaponCode);
        return true;
    }
    return false;
}

int Armory::pickUpWeapon(const b2Vec2& position, bool isCt){
    int8_t pickedWeapon = dropped.pickUpAnyIfClose(position);
    if (pickedWeapon == -1){
        return pickedWeapon;
    } else {
        if (pickedWeapon == BOMB && isCt){
            dropped.dropWeapon(pickedWeapon, position);
        }
        if (arsenal.count(PRIMARY) > 0 && pickedWeapon != BOMB){
            dropped.dropWeapon(arsenal.at(PRIMARY)->getWeaponCode(), position);
        }
       selectWeapon(pickedWeapon);
       return pickedWeapon;
    }
}

void Armory::dropWeapons(const b2Vec2& playerPosition){
    if (arsenal.count(PRIMARY) > 0){
        dropped.dropWeapon(arsenal.at(PRIMARY)->getWeaponCode(), playerPosition);
        arsenal.erase(PRIMARY);
    }
    if (arsenal.count(EXPLOSIVE) > 0){
        dropped.dropWeapon(arsenal.at(EXPLOSIVE)->getWeaponCode(), playerPosition);
        arsenal.erase(EXPLOSIVE);
    }
    currentWeapon = MELEE;
}

int Armory::getClip() const {
    return arsenal.at(currentWeapon)->getClip();
}


Armory::Armory(Armory &&other)
: arsenal(std::move(other.arsenal)),
  prices(std::move(other.prices)),
  dropped(other.dropped),
  currentWeapon(MELEE){
}

Armory &Armory::operator=(Armory &&other)  {
    if (this == &other){
        return *this;
    }
    arsenal = std::move(other.arsenal);
    prices = std::move(other.prices);
    currentWeapon = MELEE;
    return *this;
}

void Armory::selectWeapon(uint8_t weaponCode){
    switch (weaponCode) {
        case RIFLE:
            arsenal[PRIMARY] = rifle;
            break;
        case M3:
            arsenal[PRIMARY] = shotgun;
            break;
        case AWP:
            arsenal[PRIMARY] = awp;
            break;
        case BOMB:
            arsenal[EXPLOSIVE] = bomb;
            break;
    }
}
