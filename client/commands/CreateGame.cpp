#include "CreateGame.h"

void CreateGame::serialize(std::function<void(std::vector<unsigned char>)> &callback,
                           const Protocol &protocol) {
    protocol.createGame(gameName, mapName, callback);
}

CreateGame::CreateGame(std::string gameName, std::string mapName)
: gameName(std::move(gameName)),
  mapName(std::move(mapName)) {
}

CreateGame::~CreateGame() {

}
