#include "StopMoveEvent.h"

StopMoveEvent::StopMoveEvent(int id, int dir):
    ClientEvent(id){
    this->dir = dir;
}


void StopMoveEvent::updatePlayer(std::map<int, PlayerModel>& players){
    players[this->clientId].stopMove(this->dir);
}
