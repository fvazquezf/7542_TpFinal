#include "GameDoneUpdate.h"

GameDoneUpdate::GameDoneUpdate() {
}

void GameDoneUpdate::serialize(std::function<void(std::vector<unsigned char>)> &callback) {
    protocol.handleByte(GAME_DONE, callback);
}

GameDoneUpdate::~GameDoneUpdate() {
}
