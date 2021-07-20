#include "DisconnectEvent.h"
#include "../WorldModel.h"

DisconnectEvent::DisconnectEvent(uint8_t id)
: ClientEvent(id) {
}

void DisconnectEvent::updatePlayer(WorldModel &world) {
    world.disconnectPlayer(clientId);
}

DisconnectEvent::~DisconnectEvent() {

}
