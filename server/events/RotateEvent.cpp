#include "RotateEvent.h"
#include "../WorldModel.h"

RotateEvent::RotateEvent(uint8_t id, int16_t angle)
: ClientEvent(id),
  angle(angle){
}

void RotateEvent::updatePlayer(WorldModel &world) {
    world.rotatePlayer(clientId, angle);
}

RotateEvent::~RotateEvent() {
}
