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
    // crea terroristas en un lugar al azar de la ventana
    //entities.push_back(std::unique_ptr<Renderizable>(new Terrorist(terror, posX, posY, isPlayer)));
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
        entities.at(it.first)->updatePosition(it.second.first, it.second.second);
    }
}
