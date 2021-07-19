#ifndef TALLY_H
#define TALLY_H

#include <map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include <memory>
#include "../libs/box2d/include/box2d/box2d.h"
#include "weapons/Bomb.h"
#include "PlayerModel.h"

class Tally {
    // los enteros del par son kills/deaths de cada jugador
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
    void addDeath(int id);

    void startBombTiming();
    bool tickTime();
    int getTime() const;
    void resetRound();

    int getTerrorist();

    int isRoundOver();

    std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>> getScores(const std::map<int, PlayerModel>& playerModels);

protected:
    bool ctWon();
    bool ttWon();
};

#endif
