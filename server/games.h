#ifndef GAMES_H_
#define GAMES_H_

#include <unordered_map>
#include "./match.h"

class Games {
 public:
  Games();
  void newGame(std::string name, Match* m);
  Match* & operator[](std::string);
  ~Games();
  private:
    std::unordered_map<std::string, Match*> matches;
};

#endif    // GAMES_H_
