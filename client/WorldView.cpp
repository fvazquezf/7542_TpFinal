#include "WorldView.h"
#include <random>
#include <iostream>

WorldView::WorldView(SdlWindow& aWindow)
: window(aWindow),
  camera(window),
  terror("../sprites/gfx/player/t1.bmp", window){
}

WorldView::~WorldView() {
}

void WorldView::createTerrorist(uint8_t id, bool isPlayer, int posX, int posY) {
    std::lock_guard<std::mutex> lock(worldMutex);
    auto terrorist = std::unique_ptr<Renderizable>(new Terrorist(terror, posX, posY, isPlayer));
    entities.insert(std::make_pair(id, std::move(terrorist)));
}

void WorldView::render() {
    std::lock_guard<std::mutex> lock(worldMutex);
    window.fill();
    for (auto& it : entities){
        camera.render(*it.second);
    }
    window.render();
}

void WorldView::updatePositions(std::map<uint8_t, std::pair<float, float>> &positionMap) {
    std::lock_guard<std::mutex> lock(worldMutex);
    for (auto& it : positionMap){
        if (!entities.count(it.first)){
            createPlayersAtReception(it.first, it.second.first, it.second.second);
            continue;
        }
        entities.at(it.first)->updatePosition(it.second.first, it.second.second);
    }
}

void WorldView::createPlayersAtReception(uint8_t id, float x, float y) {
    auto terrorist = std::unique_ptr<Renderizable>(new Terrorist(terror, x, y, false));
    entities.insert(std::make_pair(id, std::move(terrorist)));
}

int16_t WorldView::getPlayerAngle() {
    std::lock_guard<std::mutex> lock(worldMutex);
    return camera.angleFromMouse();
}

void WorldView::updateAngles(std::map<uint8_t, int16_t> &angles) {
    std::lock_guard<std::mutex> lock(worldMutex);
    for (auto& it : angles){
        entities.at(it.first)->updateAngle(it.second);
    }
}
