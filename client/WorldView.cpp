#include "WorldView.h"
#include <cstdint>
#include <algorithm>
#include <iostream>

WorldView::WorldView(SdlWindow& aWindow, YAML::Node& clientConfig)
: window(aWindow),
  clientConfig(clientConfig),
  camera(window),
  stencil(window,
          clientConfig["stencil_angle"].as<int>(),
          clientConfig["stencil_radius"].as<float>(),
          clientConfig["stencil_opacity"].as<int>(),
          clientConfig["stencil_triangle_brightness"].as<int>()),
  menu(window),
  hud(window),
  map(window, clientConfig),
  lobby(window),
  lobbyTime(true),
  menuTime(false),
  done(false),
  terror("../sprites/gfx/player/t1.bmp", window),
  counterTerrorist("../sprites/gfx/player/ct1.bmp", window),
  blood("../sprites/gfx/fragments.bmp",
        window,
        {0, 0, 0},
        {200, 0, 0}),
  legs("../sprites/gfx/player/legs.bmp",window){
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
}

WorldView::~WorldView() {
}

// SOLO ACCEDIDO POR RECEIVER DESDE BUILD TEAMS (CON EL LOCK)
void WorldView::characterEntityCreate(uint8_t id, bool isPlayer, bool isCt) {
    entities.emplace(std::piecewise_construct,
                     std::forward_as_tuple(id),
                     std::forward_as_tuple(isCt ? counterTerrorist : terror, 0, 0, isPlayer,
                                                   weapons, blood, legs));
}

void WorldView::render(size_t iteration) {
    std::lock_guard<std::mutex> lock(worldMutex);
    window.fill(0, 0, 0, 0);
    if (lobbyTime){
        lobby.draw();
        window.render();
        return;
    }
    map.render(camera);
    for (auto& weapon : droppedWeapons){
        weapon.draw(camera);
    }
    for (auto& it : entities){
        camera.render(it.second, iteration);
    }
    stencil.createStencilTexture(camera.angleFromMouse());
    if (menuTime){
        menu.showMenu();
    }
    hud.show();
    window.render();
}

void WorldView::updatePositions(std::map<uint8_t, std::pair<float, float>> &positionMap) {
    std::lock_guard<std::mutex> lock(worldMutex);
    for (auto& it : positionMap){
        entities.at(it.first).updatePosition(it.second.first, it.second.second);
    }
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
    auto position = entities.at(id).getPosition();
    float distCenter = camera.calculateDistanceToCenter(position.first, position.second);
    entities.at(id).die(distCenter);
}

void WorldView::attack(uint8_t id) {
    std::lock_guard<std::mutex> lock(worldMutex);
    entities.at(id).attack();
}

void WorldView::changeWeapon(uint8_t weaponCode, uint8_t characterId) {
    std::lock_guard<std::mutex> lock(worldMutex);
    entities.at(characterId).changeWeapon(weaponCode);
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
    if (!isIt){
        SoundManager::playSound(SoundManager::soundRepertoire::GO, 0);
    }
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
    float dist = camera.calculateDistanceToCenter(posX, posY);
    SoundManager::playSound(SoundManager::soundRepertoire::DROP_WEAPON, dist);
}

void WorldView::pickupWeapon(std::tuple<uint8_t, size_t, int16_t, int16_t>& weaponId) {
    std::lock_guard<std::mutex> lock(worldMutex);
    uint8_t weaponType = std::get<0>(weaponId);
    size_t uniqueIdentifier = std::get<1>(weaponId);
    // por que no lo borro?
    // porque los iteradores serian invalidados por el receiver
    // y puede que el drawer este descheduled en draw, justamente dibujando las armas
    // al suceder el context switch...
    // va a levantar iteradores con "basura" (invalidos al fin)
    // por ende, no los puedo eliminar aca
    for (auto& it : droppedWeapons){
        if (it.isWeaponTypeAndId(weaponType, uniqueIdentifier)){
            it.doNotShow();
            break;
        }
    }
    SoundManager::playSound(SoundManager::soundRepertoire::PICKUP_WEAPON, 0);
}

void WorldView::buildTeams(const std::map<uint8_t, bool> &teamMap) {
    std::lock_guard<std::mutex> lock(worldMutex);
    for (auto& it : teamMap){
        uint8_t characterId = it.first;
        bool isCt = it.second;
        // si no existe el jugador, debo crearlo
        if (!entities.count(characterId)){
            characterEntityCreate(characterId, characterId == playerId, isCt);
        } else { // si existe, significa que estamos cambiando de bando
            entities.erase(characterId);
            characterEntityCreate(characterId, characterId == playerId, isCt);
        }
    }
}

void WorldView::assignPlayer(uint8_t aPlayerId) {
    playerId = aPlayerId;
}

void WorldView::updateHudTime(uint8_t time) {
    std::lock_guard<std::mutex> lock(worldMutex);
    hud.updateTime(time);
}

void WorldView::updateHudHealth(uint8_t health) {
    std::lock_guard<std::mutex> lock(worldMutex);
    hud.updateHealth(health);
}

void WorldView::updateHudMoney(uint16_t money) {
    std::lock_guard<std::mutex> lock(worldMutex);
    hud.updateMoney(money);
}

void WorldView::signalDone() {
    std::lock_guard<std::mutex> lock(worldMutex);
    SDL_Event quit;
    quit.type = SDL_QUIT;
    SDL_PushEvent(&quit);
    done = true;
}

bool WorldView::isDone() {
    return done;
}

void WorldView::buildMap(const std::string &mapString) {
    std::lock_guard<std::mutex> lock(worldMutex);
    map.loadMap(mapString);
}

void WorldView::stopLobby() {
    std::lock_guard<std::mutex> lock(worldMutex);
    if (lobbyTime){
        lobbyTime = false;
        lobby.stopPlayingLobbyMusic();
    }
}

bool WorldView::isLobbyTime() const {
    return lobbyTime;
}

bool WorldView::lobbyButtonPressed(int mouseX, int mouseY) {
    std::lock_guard<std::mutex> lock(worldMutex);
    if (!lobbyTime){
        return false;
    }
    return lobby.isButtonPressed(mouseX, mouseY);
}

