//
// Created by leogm99 on 5/7/21.
//

#include "GameDoneUpdate.h"

GameDoneUpdate::GameDoneUpdate() {
}

void GameDoneUpdate::serialize(std::function<void(std::vector<unsigned char>)> &callback) {
    protocol.handleByte(GAME_DONE, callback);
}

GameDoneUpdate::~GameDoneUpdate() {
}
