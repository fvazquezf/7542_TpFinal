#include <weapons/DroppedWeapon.h>
#include "CharacterManager.h"

CharacterManager::CharacterManager(SdlWindow& window, YAML::Node& config)
: blood(config["blood"].as<std::string>(),
      window,
      {0, 0, 0},
      {200, 0, 0}),
  legs(config["legs"].as<std::string>(), window),
  terrorist(nullptr),
  counterTerrorist(nullptr),
  playerId(0){
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(0),
                    std::forward_as_tuple(
                            SdlTexture(config["ak47"].as<std::string>(), window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(1),
                    std::forward_as_tuple(
                            SdlTexture(config["m3"].as<std::string>(), window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(2),
                    std::forward_as_tuple(
                            SdlTexture(config["awp"].as<std::string>(), window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(3),
                    std::forward_as_tuple(
                            SdlTexture(config["knife"].as<std::string>(), window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(4),
                    std::forward_as_tuple(
                            SdlTexture(config["glock"].as<std::string>(), window)));
    weapons.emplace(std::piecewise_construct,
                    std::forward_as_tuple(5),
                    std::forward_as_tuple(
                            SdlTexture(config["bomb"].as<std::string>(), window)));
}

void CharacterManager::assignTeams(std::map<uint8_t, bool> teamMap) {
    if (!teams.empty()) {
        teams = std::move(teamMap);
        changeSides();
    } else {
        teams = std::move(teamMap);
    }
}

void CharacterManager::createCharacters(SdlTexture& terroristTex, SdlTexture& counterTex) {
    for (auto& entity : teams){
        if (entity.second){
            entities.emplace(std::piecewise_construct,
                             std::forward_as_tuple(entity.first),
                             std::forward_as_tuple(counterTex, 0, 0,
                                                   entity.first == playerId,
                                                   weapons, blood, legs));
        } else {
            entities.emplace(std::piecewise_construct,
                             std::forward_as_tuple(entity.first),
                             std::forward_as_tuple(terroristTex, 0, 0,
                                                   entity.first == playerId,
                                                   weapons, blood, legs));
        }
    }
    terrorist = &terroristTex;
    counterTerrorist = &counterTex;
}

void CharacterManager::changeSides() {
    entities.clear();
    createCharacters(*terrorist, *counterTerrorist);
}

void CharacterManager::setPlayerId(uint8_t id) {
    playerId = id;
}

void CharacterManager::updatePositions(std::map<uint8_t, std::pair<float, float>> &positionMap, Camera& camera) {
    for (auto& it : positionMap) {
        try {
            Character& character = entities.at(it.first);
            character.updatePosition(it.second.first, it.second.second);
            character.move(camera.calculateDistanceToCenter(it.second.first, it.second.second));
        } catch (const std::exception& e){
        }
    }
}

void CharacterManager::updateAngles(std::map<uint8_t, int16_t> &angles) {
    for (auto& it : angles){
        try {
            entities.at(it.first).updateAngle(it.second);
        } catch (const std::exception& e){
        }
    }
}

void CharacterManager::hit(uint8_t id, Camera& camera) {
    Character& character = entities.at(id);
    auto position = character.getPosition();
    character.hit(camera.calculateDistanceToCenter(position.first, position.second));
}

void CharacterManager::kill(uint8_t id, Camera& camera) {
    auto position = entities.at(id).getPosition();
    float distCenter = camera.calculateDistanceToCenter(position.first, position.second);
    entities.at(id).die(distCenter);
}

void CharacterManager::attack(uint8_t id, Camera& camera) {
    Character& character = entities.at(id);
    auto position = character.getPosition();
    entities.at(id).attack(camera.calculateDistanceToCenter(position.first, position.second));
}

CharacterManager::~CharacterManager() {
}

void CharacterManager::draw(Camera& camera, size_t iteration) {
    for (auto& entity : entities){
        camera.render(entity.second, iteration);
    }
}

void CharacterManager::changeWeapon(uint8_t weaponCode, uint8_t playerId) {
    try {
        entities.at(playerId).changeWeapon(weaponCode);
    } catch (const std::exception& e){
    }
}

void CharacterManager::plantBomb(uint8_t planterId,
                                 std::vector<DroppedWeapon> &bombDrop,
                                 SdlTexture& droppedBomb) {
    auto planterPosition = entities.at(planterId).getPosition();
    bombDrop.emplace_back(droppedBomb, BOMB, 0,
                                100 * planterPosition.first,
                                100 * planterPosition.second);
    SoundManager::playSound(SoundManager::soundRepertoire::BOMB_PLANTED, 0);
}

void CharacterManager::reviveAll() {
    for (auto& character : entities){
        character.second.revive();
    }
}
