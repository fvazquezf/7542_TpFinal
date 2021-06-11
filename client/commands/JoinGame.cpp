#include "JoinGame.h"

JoinGame::JoinGame(const std::string &gameName)
: gameName(gameName){
}

void JoinGame::serialize(std::function<void(std::vector<unsigned char>)> &callback, const Protocol &protocol) {
    protocol.joinGame(gameName, callback);
}

JoinGame::~JoinGame() {
}
