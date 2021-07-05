#include "BombPlantUpdate.h"

BombPlantUpdate::BombPlantUpdate() {

}

void BombPlantUpdate::serialize(std::function<void(std::vector<unsigned char>)>& callback) {
    // protocol.updatePlayerState(BombPlanted_UPDATE, callback);
}

BombPlantUpdate::~BombPlantUpdate() {

}
