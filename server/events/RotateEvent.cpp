#include "RotateEvent.h"

RotateEvent::RotateEvent(uint8_t id, int16_t angle)
: ClientEvent(id),
  angle(angle){
}

void RotateEvent::updatePlayer(std::map<int, PlayerModel> &players) {
    players.at(clientId).setAngle(angle);
}

RotateEvent::~RotateEvent() {
}
