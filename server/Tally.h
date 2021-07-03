#ifndef TALLY_H
#define TALLY_H

#include <map>
#include <unordered_set>
#include "../libs/box2d/include/box2d/box2d.h"

class Tally {
    std::map<int, std::pair<int, int>> ctSide;
    std::map<int, std::pair<int, int>> ttSide;
    std::unordered_set<int> deaths;

public:
    Tally();

    void placeInTeam(int id, bool team);
    void swapTeams();
    void playerKilledOther(int id, int other);
    bool isRoundOver();
    bool ctWon();
    bool ttWon();
};

#endif
