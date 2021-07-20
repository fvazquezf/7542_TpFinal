#include "Explosion.h"
#include "../Camera.h"
#include <iostream>
#include <random>


Explosion::Explosion(SdlWindow& window, YAML::Node& config)
: explosionTexture(config["explosion"].as<std::string>(), window),
  shouldBlow(false),
  dstX(0),
  dstY(0),
  maxMiniExplosions(100),
  currentExplosions(0) {
}

Explosion::~Explosion() {
}

void Explosion::render(Camera& cam, size_t iteration) {
	if (!shouldBlow) {
	    return;
    }
    if (currentExplosions != maxMiniExplosions) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 3.0); // offset random desde el centro de la explosion
        PositionVector pos(dstX + dis(gen), dstY + dis(gen), 0);
        Animation an(explosionTexture, 25, 5, 64, iteration);
        auto explosionPair = std::make_pair(std::move(an), std::move(pos));
        miniExplosions.emplace_back(std::move(explosionPair));
        ++currentExplosions;
    }
    for (auto& explosion : miniExplosions) {
        if (!explosion.first.isDone()) {
            explosion.first.render(cam, explosion.second.x, explosion.second.y, 0, iteration);
        }
        shouldBlow |= !explosion.first.isDone(); // seguimos renderizando solo si alguna explosion no termino de animarse
    }
}

void Explosion::setExplosion(float posX, float posY) {
    currentExplosions = 0;
    shouldBlow = true;
    dstX = posX;
    dstY = posY;
}
