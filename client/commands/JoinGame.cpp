#include "JoinGame.h"

JoinGame::JoinGame(std::string gameName)
: gameName(std::move(gameName)) {
}

void JoinGame::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.joinGame(gameName, callback);
}

JoinGame::~JoinGame() {
}
