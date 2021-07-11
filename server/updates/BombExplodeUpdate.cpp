#include "BombExplodeUpdate.h"

BombExplodeUpdate::BombExplodeUpdate() {
}

void BombExplodeUpdate::serialize(std::function<void(std::vector<unsigned char>)> &callback) {
    // protocol.handleByte(BOMB_EXPLODE_DONE, callback);
}

BombExplodeUpdate::~BombExplodeUpdate() {
}
