#include "BombPlantUpdate.h"

BombPlantUpdate::BombPlantUpdate(int id)
: planterId(id){
}

void BombPlantUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    protocol.updatePlayerState(BOMB_PLANT_UPDATE, planterId, callback);
}

BombPlantUpdate::~BombPlantUpdate() {

}
