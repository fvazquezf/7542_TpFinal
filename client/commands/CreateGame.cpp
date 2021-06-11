#include "CreateGame.h"

void CreateGame::serialize(std::function<void(std::vector<unsigned char>)> &callback,
                           const Protocol &protocol) {
    protocol.createGame(gameName, callback);
}

CreateGame::CreateGame(const std::string &gameName)
: gameName(gameName){
}

CreateGame::~CreateGame() {

}
