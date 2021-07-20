#include "StopAttackEvent.h"
#include "../WorldModel.h"

StopAttackEvent::StopAttackEvent(uint8_t id)
: ClientEvent(id) {
}

void StopAttackEvent::updatePlayer(WorldModel &world) {
    world.stopAttack(clientId);
}
