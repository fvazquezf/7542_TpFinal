#include "WorldView.h"
#include <random>
#include <iostream>
#include <cstdint>

WorldView::WorldView(SdlWindow& aWindow)
: window(aWindow),
  camera(window),
  terror("../sprites/gfx/player/t1.bmp", window),
  blood("../sprites/gfx/fragments.bmp",
        window,
        {0, 0, 0},
        {150, 0, 0}),
  legs("../sprites/gfx/player/legs.bmp", window){
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(0),
                    std::forward_as_tuple(
                            SdlTexture("../sprites/gfx/weapons/knife.bmp", window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(1),
                    std::forward_as_tuple(
                            SdlTexture("../sprites/gfx/weapons/glock.bmp", window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(2),
                    std::forward_as_tuple(
                            SdlTexture("../sprites/gfx/weapons/ak47.bmp", window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(3),
                    std::forward_as_tuple(
                            SdlTexture("../sprites/gfx/weapons/awp.bmp", window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(4),
                    std::forward_as_tuple(
                            SdlTexture("../sprites/gfx/weapons/bomb.bmp", window)));
}

WorldView::~WorldView() {
}

void WorldView::createTerrorist(uint8_t id, bool isPlayer, int posX, int posY) {
    std::lock_guard<std::mutex> lock(worldMutex);
    entities.emplace(std::piecewise_construct,
                     std::forward_as_tuple(id),
                     std::forward_as_tuple(terror, posX, posY, isPlayer, weapons, blood, legs));
}

void WorldView::render(uint8_t iteration) {
    std::lock_guard<std::mutex> lock(worldMutex);
    window.fill();
    for (auto& it : entities){
        camera.render(it.second, iteration);
    }
    Area src(0, 0, 128, 64);
    window.render();
}

void WorldView::updatePositions(std::map<uint8_t, std::pair<float, float>> &positionMap) {
    std::lock_guard<std::mutex> lock(worldMutex);
    for (auto& it : positionMap){
        if (!entities.count(it.first)){
            createPlayersAtReception(it.first, it.second.first, it.second.second);
            continue;
        }
        entities.at(it.first).updatePosition(it.second.first, it.second.second);
    }
}

void WorldView::createPlayersAtReception(uint8_t id, float x, float y) {
    entities.emplace(std::piecewise_construct,
                     std::forward_as_tuple(id),
                     std::forward_as_tuple(terror, x, y, false, weapons, blood, legs));
}

int16_t WorldView::getPlayerAngle() {
    std::lock_guard<std::mutex> lock(worldMutex);
    return camera.angleFromMouse();
}

void WorldView::updateAngles(std::map<uint8_t, int16_t> &angles) {
    std::lock_guard<std::mutex> lock(worldMutex);
    for (auto& it : angles){
        entities.at(it.first).updateAngle(it.second);
    }
}

void WorldView::hit(uint8_t id) {
    std::lock_guard<std::mutex> lock(worldMutex);
    entities.at(id).hit();
}

void WorldView::kill(uint8_t id) {
    std::lock_guard<std::mutex> lock(worldMutex);
    entities.at(id).die();
    // borramos el id
    //auto it = entities.find(id);
    //entities.erase(it);
}

void WorldView::attack(uint8_t id) {
    std::lock_guard<std::mutex> lock(worldMutex);
    entities.at(id).attack();
}
