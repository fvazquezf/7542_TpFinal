#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <vector>
#include <mutex>
#include <memory>
#include <map>
#include <cstdint>
#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include "anim/Character.h"
#include "anim/Renderizable.h"
#include "Camera.h"

class WorldView {
private:
    SdlWindow& window;
    Camera camera;

    SdlTexture terror;
    SdlTexture blood;
    SdlTexture legs;
    //std::vector<Terrorist> textures;
    //std::vector<std::unique_ptr<Renderizable>> entities;

    std::map<uint8_t, Character> entities;
    std::map<uint8_t, SdlTexture> weapons;

    // Player player

    // varios hilos acceden de manera concurrente a la view
    // SDL, Drawer, Receiver
    // funciona como monitor

    std::mutex worldMutex;
    // Player player; -> lo podemos controlar, es distinto al resto
    // GameMap map; -> algo asi?

    void createPlayersAtReception(uint8_t id, float x, float y);
public:
    explicit WorldView(SdlWindow& window);

    WorldView(const WorldView& other) = delete;
    WorldView& operator=(const WorldView& other) = delete;

    WorldView(WorldView&& other) = delete;
    WorldView& operator=(WorldView&& other) = delete;

    void createTerrorist(uint8_t id, bool isPlayer, int posX, int posY);

    void updatePositions(std::map<uint8_t, std::pair<float, float>>& positionMap);
    void updateAngles(std::map<uint8_t, int16_t>& angles);
    void render(uint8_t iteration);

    ~WorldView();

    int16_t getPlayerAngle();

    void attack(uint8_t id);

    void hit(uint8_t id);

    void kill(uint8_t id);
};


#endif
