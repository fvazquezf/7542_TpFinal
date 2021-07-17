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
  hud(window, clientConfig),
  map(window, clientConfig),
  cursor(clientConfig["cursor_type"].as<int>(),
         window,
         clientConfig["cursor_source_file"].as<std::string>(),
         clientConfig["cursor_size"].as<int>()),
  bombExplosion(window, clientConfig),
  characterManager(window, clientConfig),
  score(window, hud, clientConfig),
  lobbyTime(true),
  menuTime(false),
  skinTime(false),
  done(false),
  hudButton(clientConfig["hud_button"].as<std::string>(), window),
  lobby(window, hudButton, clientConfig),
  menu(window, hudButton, clientConfig),
  skins(window, clientConfig, hudButton, true, characterManager){
    dropTextures.emplace(std::piecewise_construct,
                  std::forward_as_tuple(0),
                  std::forward_as_tuple(SdlTexture(clientConfig["ak47_drop"].as<std::string>(), window)));

    dropTextures.emplace(std::piecewise_construct,
                  std::forward_as_tuple(1),
                  std::forward_as_tuple(SdlTexture(clientConfig["m3_drop"].as<std::string>(), window)));

    dropTextures.emplace(std::piecewise_construct,
                         std::forward_as_tuple(2),
                         std::forward_as_tuple(SdlTexture(clientConfig["awp_drop"].as<std::string>(), window)));

    dropTextures.emplace(std::piecewise_construct,
                  std::forward_as_tuple(5),
                  std::forward_as_tuple(SdlTexture(clientConfig["bomb_drop"].as<std::string>(), window)));
    SDL_ShowCursor(SDL_DISABLE);
    SoundManager::playMusic();
}

WorldView::~WorldView() {
}

void WorldView::render(size_t iteration) {
    std::lock_guard<std::mutex> lock(worldMutex);
    window.fill(0, 0, 0, 0);
    if (lobbyTime){
        lobby.draw();
        cursor.draw();
        window.render();
        return;
    }
    map.render(camera);
    for (auto& weapon : droppedWeapons){
        weapon.draw(camera);
    }
    characterManager.draw(camera, iteration);
    stencil.createStencilTexture(camera.angleFromMouse());

    bombExplosion.render(camera, iteration);

    if (menuTime){
        menu.showMenu();
    }
    score.show();
    skins.draw();
    hud.show();
    cursor.draw();
    window.render();
}

void WorldView::updatePositions(std::map<uint8_t, std::pair<float, float>> &positionMap) {
    std::lock_guard<std::mutex> lock(worldMutex);
    characterManager.updatePositions(positionMap, camera);
}

int16_t WorldView::getPlayerAngle() {
    std::lock_guard<std::mutex> lock(worldMutex);
    return camera.angleFromMouse();
}

void WorldView::updateAngles(std::map<uint8_t, int16_t> &angles) {
    std::lock_guard<std::mutex> lock(worldMutex);
    characterManager.updateAngles(angles);
}

void WorldView::hit(uint8_t id) {
    std::lock_guard<std::mutex> lock(worldMutex);
    characterManager.hit(id, camera);
}

void WorldView::kill(uint8_t id) {
    std::lock_guard<std::mutex> lock(worldMutex);
    characterManager.kill(id, camera);
}

void WorldView::attack(uint8_t id) {
    std::lock_guard<std::mutex> lock(worldMutex);
    characterManager.attack(id, camera);
}

void WorldView::changeWeapon(uint8_t weaponCode, uint8_t characterId) {
    std::lock_guard<std::mutex> lock(worldMutex);
    characterManager.changeWeapon(weaponCode, characterId);
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
    std::lock_guard<std::mutex> lock(worldMutex);
    menuTime = isIt;
    if (!isIt){
        // si el jugador no selecciono un skin
        // asignamos skins random
        skins.setRandomSkinsIfNotSelected();
        hud.resetHud(); // desactivamos la pantalla de winner
        // GO, GO, GO!
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
    float dist = camera.calculateDistanceToCenter(posX / 100, posY / 100);
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
    std::pair<float, float> pos;
    for (auto& it : droppedWeapons){
        if (it.isWeaponTypeAndId(weaponType, uniqueIdentifier)){
            it.doNotShow();
            pos = it.getPosition();
            break;
        }
    }
    float distance = camera.calculateDistanceToCenter(pos.first, pos.second);
    SoundManager::playSound(SoundManager::soundRepertoire::PICKUP_WEAPON, distance);
}

void WorldView::buildTeams(std::map<uint8_t, bool> teamMap) {
    std::lock_guard<std::mutex> lock(worldMutex);
    skinTime = true;
    skins.setPlayerTeam(teamMap.at(playerId));
    characterManager.assignTeams(std::move(teamMap));
    // swappea el puntaje de los tts y cts
    hud.swapTeamScores();
}

void WorldView::assignPlayer(uint8_t aPlayerId) {
    std::lock_guard<std::mutex> lock(worldMutex);
    playerId = aPlayerId;
    characterManager.setPlayerId(aPlayerId);
    score.setPlayerId(aPlayerId);
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
    try {
        map.loadMap(mapString);
    } catch (const std::exception& e){
        SDL_Event quit;
        quit.type = SDL_QUIT;
        SDL_PushEvent(&quit);
        done = true;
    }
}

void WorldView::stopLobby() {
    std::lock_guard<std::mutex> lock(worldMutex);
    if (lobbyTime){
        lobbyTime = false;
        lobby.stopPlayingLobbyMusic();
    }
}

bool WorldView::lobbyButtonPressed(int mouseX, int mouseY) {
    std::lock_guard<std::mutex> lock(worldMutex);
    if (!lobbyTime){
        return false;
    }
    return lobby.isButtonPressed(mouseX, mouseY);
}

void WorldView::updateHudClip(uint8_t clip) {
    std::lock_guard<std::mutex> lock(worldMutex);
    hud.updateClip(clip);
}

void WorldView::plantBomb(uint8_t planterId) {
    std::lock_guard<std::mutex> lock(worldMutex);
    characterManager.plantBomb(planterId, droppedWeapons, dropTextures.at(BOMB));
}

void WorldView::blowBomb() {
    std::lock_guard<std::mutex> lock(worldMutex);
    std::pair<float, float> pos;
    auto dropped = droppedWeapons.begin();
    while (dropped != droppedWeapons.end()){
        if (dropped->isWeaponTypeAndId(BOMB, 0)){
            pos = dropped->getPosition();
            dropped = droppedWeapons.erase(dropped);
            break;
        }
        ++dropped;
    }
    bombExplosion.setExplosion(pos.first, pos.second);
    SoundManager::playSound(SoundManager::soundRepertoire::BOMB_EXPLODE, 0);
}

void WorldView::updateHudWinner(bool ctIsWinner) {
    std::lock_guard<std::mutex> lock(worldMutex);
    hud.updateWinner(ctIsWinner);
}

bool WorldView::skinSelectionTime() {
    std::lock_guard<std::mutex> lock(worldMutex);
    return skinTime;
}

void WorldView::selectSkin() {
    std::lock_guard<std::mutex> lock(worldMutex);
    try {
        skins.assignTexturesFromButtonPressed();
        skinTime = false;
    } catch (std::exception& e){
    }
}

void WorldView::setScoreData(const std::vector<std::tuple<uint8_t, uint8_t, uint8_t, uint16_t, bool>> &scores) {
    std::lock_guard<std::mutex> lock(worldMutex);
    score.setScoreData(scores);
    score.setEnable();
}
