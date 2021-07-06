#ifndef MAPLAYOUT_H
#define MAPLAYOUT_H

#include <tuple>
#include "../libs/box2d/include/box2d/box2d.h"

class MapLayout {
    std::pair<std::pair<int, int>, std::pair<int, int>> ctSpawn;
    std::pair<std::pair<int, int>, std::pair<int, int>> ttSpawn;

    std::pair<std::pair<int, int>, std::pair<int, int>> bombSite;

public:
    MapLayout();

    bool isInSite(const b2Vec2& position);

    b2Vec2 placeCt();

    b2Vec2 placeTt();
};

#endif
