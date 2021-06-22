#include "StartMoveEvent.h"

StartMoveEvent::StartMoveEvent(int id, int dir):
    ClientEvent(id){
    this->dir = dir;
}


void StartMoveEvent::updatePlayer(WorldModel &world){
    world.movePlayer(clientId, dir);
}
