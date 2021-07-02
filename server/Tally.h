#ifndef TALLY_H
#define TALLY_H

#include <vector>
#include "../libs/box2d/include/box2d/box2d.h"

class Tally {
    std::vector<int> ctSide;
    std::vector<int> ttSide;

public:
    Tally();

    void placeInTeam(int id, bool team);
};

#endif
