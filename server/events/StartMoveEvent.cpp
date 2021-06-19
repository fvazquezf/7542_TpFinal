#include "StartMoveEvent.h"

StartMoveEvent::StartMoveEvent(int id, int dir):
    ClientEvent(id){
    this->dir = dir;
}


void StartMoveEvent::updatePlayer(std::map<int, PlayerModel>& players){
    PlayerModel player = players[this->clientId];
    player.startMove(this->dir);
}
