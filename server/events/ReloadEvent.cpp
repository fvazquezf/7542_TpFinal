#include <iostream>
#include "ReloadEvent.h"
#include "../WorldModel.h"

ReloadEvent::ReloadEvent(uint8_t id)
: ClientEvent(id) {
}

void ReloadEvent::updatePlayer(WorldModel &world) {
    world.reloadWeapon(clientId);
}

ReloadEvent::~ReloadEvent() {

}
