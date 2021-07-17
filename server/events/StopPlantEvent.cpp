#include "StopPlantEvent.h"
#include "../WorldModel.h"

StopPlantEvent::StopPlantEvent(uint8_t id)
: ClientEvent(id){
}

void StopPlantEvent::updatePlayer(WorldModel &world) {
    world.stopBombHandling(clientId);
}

