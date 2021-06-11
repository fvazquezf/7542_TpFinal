#include "./game.h"

Game::Game() {
}

void Game::addUser(std::string id, User* user) {
    this->users[id] = user;
    user->start();
}
void Game::removeUser(std::string id) {
    this->users.erase(id);
}

Game::~Game() {
}
