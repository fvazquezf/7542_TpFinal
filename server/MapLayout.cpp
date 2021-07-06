#include "MapLayout.h"
#include <random>

MapLayout::MapLayout(): ctSpawn ({{45, 50}, {45, 50}}),
                        ttSpawn ({{40, 45}, {40, 45}}),
                        bombSite ({{40, 50}, {40, 50}}){
}

bool MapLayout::isInSite(const b2Vec2& position){
    if ((bombSite.first.first < position.x) && (position.x < bombSite.first.second)){
        if ((bombSite.second.first < position.y) && (position.y < bombSite.second.second)){
            return true;
        }
    }
    return false;
}

b2Vec2 MapLayout::placeCt(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xPos(ctSpawn.first.first, ctSpawn.first.second);
    float x = xPos(gen);
    std::uniform_int_distribution<> yPos(ctSpawn.second.first, ctSpawn.second.second);
    float y = yPos(gen);
    return b2Vec2(x, y);
}

b2Vec2 MapLayout::placeTt(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xPos(ttSpawn.first.first, ttSpawn.first.second);
    float x = xPos(gen);
    std::uniform_int_distribution<> yPos(ttSpawn.second.first, ttSpawn.second.second);
    float y = yPos(gen);
    return b2Vec2(x, y);
}