#include "StopMoveEvent.h"
#include "../WorldModel.h"

StopMoveEvent::StopMoveEvent(int id, int dir):
    ClientEvent(id){
    this->dir = dir;
}


void StopMoveEvent::updatePlayer(WorldModel &world){
    world.stopMovingPlayer(clientId, dir);
}
