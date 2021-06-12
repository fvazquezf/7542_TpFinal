#include "ListGame.h"

ListGame::ListGame() {
}

void ListGame::serialize(std::function<void(std::vector<unsigned char>)> &callback,
                         const Protocol &protocol) {
    protocol.listGames(callback);
}

ListGame::~ListGame() {
}
