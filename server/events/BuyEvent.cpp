#include <iostream>
#include "BuyEvent.h"
#include "../WorldModel.h"

BuyEvent::BuyEvent(uint8_t id, uint8_t weaponCode)
: ClientEvent(id),
  weaponCode(weaponCode){
}

void BuyEvent::updatePlayer(WorldModel &world) {
    world.buyWeapon(clientId, weaponCode);
}

BuyEvent::~BuyEvent() {

}
