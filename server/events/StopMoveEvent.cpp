#include "StopMoveEvent.h"

StopMoveEvent::StopMoveEvent(int id, int dir):
    ClientEvent(id){
    this->dir = dir;
}


void StopMoveEvent::updatePlayer(std::map<int, PlayerModel>& players){
    PlayerModel player = players[this->clientId];
    player.stopMove(this->dir);
}
