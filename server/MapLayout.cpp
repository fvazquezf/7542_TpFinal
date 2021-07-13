#include "MapLayout.h"
#include <random>
#include <iostream>

MapLayout::MapLayout(): ctSpawn ({{45, 50}, {45, 50}}),
                        ttSpawn ({{40, 45}, {40, 45}}),
                        bombSite ({{40, 50}, {40, 50}}){
                                
}

// b-a = lado x del rectangulo
// d-c = lado y del rectangulo 
void MapLayout::setCtSpawn(int a, int b, int c, int d){ 
    ctSpawn =  {{a, b}, {c, d}};
}

void MapLayout::setTtSpawn(int a, int b, int c, int d){ 
    ttSpawn =  {{a, b}, {c, d}};
}

void MapLayout::setBombSite(int a, int b, int c, int d){ 
    bombSite =  {{a, b}, {c, d}};
}

void MapLayout::loadWalls(std::set<std::pair<int, int>> walls){
    this->walls.swap(walls);
}

bool MapLayout::checkTunneling(const b2Vec2& attacker, const b2Vec2& victim){
    int x0 = (int)round(attacker.x);
    int y0 = (int)round(attacker.y);
    int x1 = (int)round(victim.x);
    int y1 = (int)round(victim.y);

    return plotLine(x0, y0, x1, y1);
}

bool MapLayout::plotLine(int x0, int y0, int x1, int y1) {
    int dx =  abs(x1-x0);
    int sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0);
    int sy = y0<y1 ? 1 : -1;
    int err = dx+dy;  /* error value e_xy */
    for (int i = 0; i<50; i++) {
        if (walls.find({x0, y0}) != walls.end()) return true;
        if (x0 == x1 && y0 == y1) {
        	return false;
        }
        int e2 = 2*err;
        if (e2 >= dy) {/* e_xy+e_x > 0 */
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {/* e_xy+e_y < 0 */
            err += dx;
            y0 += sy;
        }
    }
    return false;
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