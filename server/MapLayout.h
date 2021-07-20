#ifndef MAPLAYOUT_H
#define MAPLAYOUT_H

#include <tuple>
#include <set>
#include "../libs/box2d/include/box2d/box2d.h"
#include "yaml-cpp/yaml.h"

class MapLayout {
    std::pair<std::pair<int, int>, std::pair<int, int>> ctSpawn;
    std::pair<std::pair<int, int>, std::pair<int, int>> ttSpawn;

    std::pair<std::pair<int, int>, std::pair<int, int>> bombSite;

    std::set<std::pair<int, int>> walls;

    // Bresenhams Line Algoritm
    bool plotLine(int x0, int y0, int x1, int y1);

    int randomIntBetween(int a, int b);

    void createBox(b2World& world, b2BodyDef& boxDef);
    void createMapBorder(b2World& world, int xSide, int ySide);
    std::pair<std::pair<int, int>, std::pair<int, int>> getPointsFromRectangle(std::vector<std::pair<int, int>> positions);

    void setCtSpawn(std::vector<std::pair<int, int>> positions);
    void setTtSpawn(std::vector<std::pair<int, int>> positions);
    void setBombSite(std::vector<std::pair<int, int>> positions);

public:
    MapLayout();

    void loadMap(b2World& world, YAML::Node& mapInfo);

    bool checkTunneling(const b2Vec2& attacker, const b2Vec2& victim);

    bool isInSite(const b2Vec2& position);

    b2Vec2 placeCt();

    b2Vec2 placeTt();
};

#endif
