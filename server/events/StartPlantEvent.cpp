#include "StartPlantEvent.h"
#include "../WorldModel.h"

StartPlantEvent::StartPlantEvent(uint8_t id)
: ClientEvent(id){
}

void StartPlantEvent::updatePlayer(WorldModel &world) {
    world.startPlanting(clientId);
}

