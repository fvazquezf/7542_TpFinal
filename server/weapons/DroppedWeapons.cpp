#include "DroppedWeapons.h"
#include "../updates/WeaponDropUpdate.h"

DroppedWeapons::DroppedWeapons(Broadcaster &updates)
: broadcaster(updates){
}

void DroppedWeapons::dropWeapon(uint8_t weaponCode, const b2Vec2 &position) {
    auto pos = position;
    droppedWeapons.emplace_back(weaponCode, pos);
    broadcaster.pushAll(std::shared_ptr<Update>(new WeaponDropUpdate(weaponCode, pos.x, pos.y)));
}

int8_t DroppedWeapons::pickUpAnyIfClose(const b2Vec2 &playerPosition) {
    auto weapon = droppedWeapons.begin();
    while (weapon != droppedWeapons.end()){
        if ((weapon->second - playerPosition).LengthSquared() < 5){
            broadcaster.pushAll(std::shared_ptr<Update>(new WeaponDropUpdate(weapon->first,
                                                                             weapon->second.x,
                                                                             weapon->second.y,
                                                                             false)));
            uint8_t code = weapon->first;
            droppedWeapons.erase(weapon);
            return code;
        } else {
            ++weapon;
        }
    }
    return -1;
}

DroppedWeapons::~DroppedWeapons() {
}
