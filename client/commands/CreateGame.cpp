#include "CreateGame.h"

void CreateGame::serialize(std::function<void(std::vector<unsigned char>)> &callback,
                           const Protocol &protocol) {
    protocol.createGame(gameName, callback);
}

CreateGame::CreateGame(std::string gameName)
: gameName(std::move(gameName)){
}

CreateGame::~CreateGame() {

}
