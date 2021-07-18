#include "DroppedWeapons.h"
#include "../updates/WeaponDropUpdate.h"
#include "Weapon.h"

DroppedWeapons::DroppedWeapons(Broadcaster &updates)
: uniquifier(0),
  broadcaster(updates){
}

void DroppedWeapons::dropWeapon(uint8_t weaponCode, const b2Vec2 &position) {
    auto pos = position;
    droppedWeapons.emplace_back(weaponCode, uniquifier, pos);
    broadcaster.pushAll(std::shared_ptr<Update>(new WeaponDropUpdate(weaponCode, uniquifier, pos.x, pos.y)));
    ++uniquifier;
}

int8_t DroppedWeapons::pickUpAnyIfClose(const b2Vec2 &playerPosition) {
    int8_t code = -1;
    auto weapon = droppedWeapons.begin();
    while (weapon != droppedWeapons.end()){
        if ((std::get<2>(*weapon) - playerPosition).LengthSquared() < 1){
            broadcaster.pushAll(std::shared_ptr<Update>(new WeaponDropUpdate(std::get<0>(*weapon),
                                                                             std::get<1>(*weapon),
                                                                             std::get<2>(*weapon).x,
                                                                             std::get<2>(*weapon).y,
                                                                             false)));
            code = std::get<0>(*weapon);
            droppedWeapons.erase(weapon);
            break;
        } else {
            ++weapon;
        }
    }
    return code;
}

void DroppedWeapons::removeBomb(){
    auto weapon = droppedWeapons.begin();
    while (weapon != droppedWeapons.end()){
        if (std::get<0>(*weapon) == BOMB) {
            broadcaster.pushAll(std::shared_ptr<Update>(new WeaponDropUpdate(std::get<0>(*weapon),
                                                                             std::get<1>(*weapon),
                                                                             std::get<2>(*weapon).x,
                                                                             std::get<2>(*weapon).y,
                                                                             false)));
            droppedWeapons.erase(weapon);
            return;
        }
        ++weapon;
    }
}

DroppedWeapons::~DroppedWeapons() {
}

DroppedWeapons::DroppedWeapons(DroppedWeapons &&other)
: uniquifier(other.uniquifier),
  broadcaster(other.broadcaster),
  droppedWeapons(std::move(other.droppedWeapons)){
}

DroppedWeapons &DroppedWeapons::operator=(DroppedWeapons &&other)  {
    if (this == &other){
        return *this;
    }

    uniquifier = std::move(other.uniquifier);
    droppedWeapons = std::move(other.droppedWeapons);
    return *this;
} 
