#include "StartMoveEvent.h"

StartMoveEvent::StartMoveEvent(int id, int dir):
    ClientEvent(id){
    this->dir = dir;
}


void StartMoveEvent::updatePlayer(std::map<int, PlayerModel>& players){
    players[this->clientId].startMove(this->dir);
}
