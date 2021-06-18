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

void WorldView::createTerrorist(bool isPlayer) {
    // crea terroristas en un lugar al azar de la ventana
    entities.push_back(std::unique_ptr<Renderizable>(new Terrorist(terror, 3, 3, isPlayer)));
}


void WorldView::createTerrorist(bool isPlayer, int posX, int posY) {
    // crea terroristas en un lugar al azar de la ventana
    entities.push_back(std::unique_ptr<Renderizable>(new Terrorist(terror, posX, posY, isPlayer)));
}

void WorldView::update() {
    std::lock_guard<std::mutex> lock(worldMutex);
    window.fill();
    /*for (auto& it : textures){
        it.update(0);
    }*/
}

void WorldView::render() {
    std::lock_guard<std::mutex> lock(worldMutex);
    for (auto& it : entities){
        it->update();
        camera.render(*it);
    }
    window.render();
}
