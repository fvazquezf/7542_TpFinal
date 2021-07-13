#ifndef TALLY_H
#define TALLY_H

#include <map>
#include <unordered_set>
#include <memory>
#include "../libs/box2d/include/box2d/box2d.h"
#include "weapons/Bomb.h"

class Tally {
    std::map<int, std::pair<int, int>> ctSide;
    std::map<int, std::pair<int, int>> ttSide;
    std::unordered_set<int> deaths;


    std::shared_ptr<Bomb> bomb;

    int time;
    int ticks;

    // ct/tt
    std::pair<int, int> score;

public:
    Tally(std::shared_ptr<Bomb> bomb);

    void placeInTeam(int id, bool team);
    void swapTeams();
    
    void playerKilledOther(int id, int other);

    void startBombTiming();
    bool tickTime();
    int getTime();
    void resetRound();

    int getTerrorist();

    int isRoundOver();

protected:
    bool ctWon();
    bool ttWon();
};

#endif
