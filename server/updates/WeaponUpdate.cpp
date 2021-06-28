#include "WeaponUpdate.h"

WeaponUpdate::WeaponUpdate(uint8_t id, uint8_t weaponId)
: id(id),
  weaponId(weaponId){
}

void WeaponUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    protocol.updatePlayerWeapon(weaponId, id, callback);
}

WeaponUpdate::~WeaponUpdate() {
}
