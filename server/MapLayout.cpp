#include "MapLayout.h"
#include <random>
#include <iostream>
#include <string>
#include <tuple>

MapLayout::MapLayout(): ctSpawn ({{0, 1}, {0, 1}}),
                        ttSpawn ({{0, 1}, {0, 1}}),
                        bombSite ({{0, 1}, {0, 1}}){
                                
}

void MapLayout::loadMap(b2World& world, YAML::Node& mapInfo){
    std::vector<std::pair<int, int>> temp;
    std::vector<std::string> categories{"wall_1", "wall_2", "wall_3", "wall_4", "wall_5", "wall_6", "wall_7", "wall_8"};
    for (auto category: categories){
        if (mapInfo[category]){
            temp = mapInfo[category].as<std::vector<std::pair<int, int>>>();
            walls.insert(temp.begin(), temp.end());
        }
    }
    b2BodyDef boxDef;
    boxDef.type = b2_staticBody;
    for (auto& pos: walls){
        boxDef.position.Set(pos.first, pos.second);
        createBox(world, boxDef);
    }
    temp = mapInfo["zoneA"].as<std::vector<std::pair<int, int>>>();
    setCtSpawn(temp);

    temp = mapInfo["zoneB"].as<std::vector<std::pair<int, int>>>();
    setTtSpawn(temp);

    temp = mapInfo["zoneBomb"].as<std::vector<std::pair<int, int>>>();
    setBombSite(temp);

    int ySize = mapInfo["size_columns"].as<int>();
    int xSize = mapInfo["size_rows"].as<int>();
    createMapBorder(world, xSize, ySize);
}

void MapLayout::createBox(b2World& world, b2BodyDef& boxDef){
	b2Body* box = world.CreateBody(&boxDef);
    b2PolygonShape bodyBox;
	bodyBox.SetAsBox(.75f, 0.75f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bodyBox;
    box->CreateFixture(&fixtureDef);
}


void MapLayout::createMapBorder(b2World& world, int xSide, int ySide){
	float x = 0;
	float y = -0.95;

    b2BodyDef boxDef;
    boxDef.type = b2_staticBody;

	for (int i = 0; i < xSide ; i++){
		boxDef.position.Set(x, y);
		createBox(world, boxDef);
		boxDef.position.Set(x, y+ySide+1.15);
		createBox(world, boxDef);
		x = x + 1.5;
	}
    x = -0.95;
	y = 0;
	for (int i = 0; i < ySide ; i++){
		boxDef.position.Set(x, y);
		createBox(world, boxDef);
		boxDef.position.Set(x+xSide+1.15, y);
		createBox(world, boxDef);
		y = y + 1.5;
	}
}


std::pair<std::pair<int, int>, std::pair<int, int>> MapLayout::getPointsFromRectangle(std::vector<std::pair<int, int>> positions) {
// los puntos del mapa vienen ordenados por el editor
    int a = positions[1].first;
    int b = positions[2].first;
    int c = positions[0].second;
    int d = positions[1].second;
    
    return {{a, b}, {c, d}};
}

// b-a = lado x del rectangulo
// d-c = lado y del rectangulo 
void MapLayout::setCtSpawn(std::vector<std::pair<int, int>> positions){ 
    ctSpawn = std::move(getPointsFromRectangle(positions));
}

void MapLayout::setTtSpawn(std::vector<std::pair<int, int>> positions){ 
    ttSpawn = std::move(getPointsFromRectangle(positions));
}

void MapLayout::setBombSite(std::vector<std::pair<int, int>> positions){ 
    bombSite = std::move(getPointsFromRectangle(positions));
}


bool MapLayout::checkTunneling(const b2Vec2& attacker, const b2Vec2& victim){
    int x0 = static_cast<int>(round(attacker.x));
    int y0 = static_cast<int>(round(attacker.y));
    int x1 = static_cast<int>(round(victim.x));
    int y1 = static_cast<int>(round(victim.y));

    return plotLine(x0, y0, x1, y1);
}

bool MapLayout::plotLine(int x0, int y0, int x1, int y1) {
    int dx =  abs(x1-x0);
    int sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0);
    int sy = y0<y1 ? 1 : -1;
    int err = dx+dy;  
    for (int i = 0; i<50; i++) {
        if (walls.find({x0, y0}) != walls.end()) return true;
        if (x0 == x1 && y0 == y1) {
        	return false;
        }
        int e2 = 2*err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
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
    float x = randomIntBetween(ctSpawn.first.first, ctSpawn.first.second);
    float y = randomIntBetween(ctSpawn.second.first, ctSpawn.second.second);
    return b2Vec2(x, y);
}

b2Vec2 MapLayout::placeTt(){
    float x = randomIntBetween(ttSpawn.first.first, ttSpawn.first.second);
    float y = randomIntBetween(ttSpawn.second.first, ttSpawn.second.second);
    return b2Vec2(x, y);
}

int MapLayout::randomIntBetween(int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> integer(a, b);
    return integer(gen);
}
