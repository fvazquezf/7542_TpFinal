#include <iostream>
#include "PickUpEvent.h"
#include "../WorldModel.h"

PickUpEvent::PickUpEvent(uint8_t id)
: ClientEvent(id) {
}

void PickUpEvent::updatePlayer(WorldModel &world) {
    world.pickUpWeapon(clientId);
}

PickUpEvent::~PickUpEvent() {

}
