#include "WorldView.h"
#include <random>

WorldView::WorldView(SdlWindow& aWindow)
: window(aWindow),
  terror("../sprites/gfx/player/t1.bmp", window){
}

WorldView::~WorldView() {
}

void WorldView::createTerrorist() {
    // crea terroristas en un lugar al azar de la ventana
    std::lock_guard<std::mutex> lock(worldMutex);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> w(0,800);
    std::uniform_int_distribution<std::mt19937::result_type> h(0,600);
    textures.emplace_back(terror, w(rng), h(rng));
}

void WorldView::update() {
    std::lock_guard<std::mutex> lock(worldMutex);
    window.fill();
    for (auto& it : textures){
        it.update(0);
    }
}

void WorldView::render() {
    std::lock_guard<std::mutex> lock(worldMutex);
    for (auto& it : textures){
        it.render();
    }
    window.render();
}
