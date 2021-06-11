#ifndef GAME_H_
#define GAME_H_
#include <unordered_map>
#include "user.h"

class Game {
 public:
  Game();
  void addUser(std::string id, User* user);
  void removeUser(std::string id);
  ~Game();
 private:
    std::unordered_map<std::string, User*> users;
};

#endif    // GAME_H_
