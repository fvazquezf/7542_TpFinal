#include "EquipWeaponEvent.h"
#include "../WorldModel.h"

EquipWeaponEvent::EquipWeaponEvent(uint8_t id, uint8_t code)
: ClientEvent(id),
  weaponCode(code){
}

void EquipWeaponEvent::updatePlayer(WorldModel &world) {
    world.equipWeapon(clientId, weaponCode);
}

EquipWeaponEvent::~EquipWeaponEvent() {
}
