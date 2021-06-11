#ifndef GAMES_H_
#define GAMES_H_
#include <unordered_map>
#include "./game.h"

class Games {
 public:
  Games();
  void newGame(std::string name, Game* g);
  Game* & operator[](std::string);
  ~Games();
  private:
    std::unordered_map<std::string, Game*> games;
};

#endif    // GAMES_H_
