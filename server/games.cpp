#include "./games.h"

Games::Games() {
}

void Games::newGame(std::string name, Game* g) {
    games[name] = g;
}

Game*& Games::operator[](std::string game_name) {
    return games[game_name];
}

Games::~Games() {
}
