#include "WorldView.h"
#include <random>
#include <iostream>
#include <cstdint>
#include <algorithm>

WorldView::WorldView(SdlWindow& aWindow)
: window(aWindow),
  camera(window),
  stencil(window, 45, 0, 0),
  menu(window),
  hud(window),
  menuTime(false),
  terror("../sprites/gfx/player/t1.bmp", window),
  blood("../sprites/gfx/fragments.bmp",
        window,
        {0, 0, 0},
        {200, 0, 0}),
  legs("../sprites/gfx/player/legs.bmp",window),
  backgroundTiles("../sprites/gfx/backgrounds/aztec.png", window){
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(0),
                    std::forward_as_tuple(
                            SdlTexture("../sprites/gfx/weapons/ak47.bmp", window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(1),
                    std::forward_as_tuple(
                            SdlTexture("../sprites/gfx/weapons/m3.bmp", window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(2),
                    std::forward_as_tuple(
                            SdlTexture("../sprites/gfx/weapons/awp.bmp", window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(3),
                    std::forward_as_tuple(
                            SdlTexture("../sprites/gfx/weapons/knife.bmp", window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(4),
                    std::forward_as_tuple(
                            SdlTexture("../sprites/gfx/weapons/glock.bmp", window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(5),
                    std::forward_as_tuple(
                            SdlTexture("../sprites/gfx/weapons/bomb.bmp", window)));

    dropTextures.emplace(std::piecewise_construct,
                  std::forward_as_tuple(0),
                  std::forward_as_tuple(SdlTexture("../sprites/gfx/weapons/ak47_d.bmp", window)));

    dropTextures.emplace(std::piecewise_construct,
                  std::forward_as_tuple(1),
                  std::forward_as_tuple(SdlTexture("../sprites/gfx/weapons/m3_d.bmp", window)));

    dropTextures.emplace(std::piecewise_construct,
                         std::forward_as_tuple(2),
                         std::forward_as_tuple(SdlTexture("../sprites/gfx/weapons/awp_d.bmp", window)));

    dropTextures.emplace(std::piecewise_construct,
                  std::forward_as_tuple(5),
                  std::forward_as_tuple(SdlTexture("../sprites/gfx/weapons/bomb_d.bmp", window)));
    for (size_t i = 40; i < 70; ++i)
        for (size_t j = 40; j < 70; ++j)
            tiles.emplace_back(backgroundTiles, 32, 32, i, j);
}

WorldView::~WorldView() {
}

void WorldView::createTerrorist(uint8_t id, bool isPlayer, int posX, int posY) {
    std::lock_guard<std::mutex> lock(worldMutex);
    entities.emplace(std::piecewise_construct,
                     std::forward_as_tuple(id),
                     std::forward_as_tuple(terror, posX, posY, isPlayer, weapons, blood, legs));
}

void WorldView::render(size_t iteration) {
    std::lock_guard<std::mutex> lock(worldMutex);
    window.fill();
    for (auto& tile : tiles){
        camera.render(tile, iteration);
    }
    for (auto& weapon : droppedWeapons){
        weapon.draw(camera);
    }
    for (auto& it : entities){
        camera.render(it.second, iteration);
    }
    if (menuTime){
        menu.showMenu();
    }
    //hud.show();
    //stencil.applyFilter(camera.angleFromMouse());
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

void WorldView::changeWeapon(uint8_t weaponCode, uint8_t playerId) {
    std::lock_guard<std::mutex> lock(worldMutex);
    entities.at(playerId).changeWeapon(weaponCode);
}

bool WorldView::menuButtonPressed(int mouseX, int mouseY) {
    std::lock_guard<std::mutex> lock(worldMutex);
    if (!menuTime){
        return false;
    }
    return menu.isButtonPressed(mouseX, mouseY);
}

uint8_t WorldView::getPressedButtonCode() {
    std::lock_guard<std::mutex> lock(worldMutex);
    return menu.getPressedButtonCode();
}

void WorldView::setMenu(bool isIt) {
    menuTime = isIt;
}

bool WorldView::isMenuTime() const {
    return menuTime;
}

void WorldView::dropWeapon(std::tuple<uint8_t, size_t, int16_t, int16_t>& weaponId) {
    std::lock_guard<std::mutex> lock(worldMutex);
    uint8_t id = std::get<0>(weaponId);
    size_t uniqueIdentifier = std::get<1>(weaponId);
    int16_t posX = std::get<2>(weaponId);
    int16_t posY = std::get<3>(weaponId);
    auto& texture = dropTextures.at(id);
    droppedWeapons.emplace_back(texture, id, uniqueIdentifier, posX, posY);
}

void WorldView::pickupWeapon(std::tuple<uint8_t, size_t, int16_t, int16_t>& weaponId) {
    std::lock_guard<std::mutex> lock(worldMutex);
    uint8_t weaponType = std::get<0>(weaponId);
    size_t uniqueIdentifier = std::get<1>(weaponId);
    for (auto& it : droppedWeapons){
        if (it.isWeaponTypeAndId(weaponType, uniqueIdentifier)){
            it.doNotShow();
            break;
        }
    }
}

