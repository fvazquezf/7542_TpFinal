#include "StartAttackEvent.h"
#include "../WorldModel.h"

StartAttackEvent::StartAttackEvent(uint8_t id)
: ClientEvent(id){
}

void StartAttackEvent::updatePlayer(WorldModel &world) {
    world.startAttack(clientId);
}

