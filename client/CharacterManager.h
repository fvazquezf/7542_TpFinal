#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H


#include <cstdint>
#include <map>
#include "anim/Character.h"
#include <yaml-cpp/yaml.h>
#include "sdlwrap/SdlWindow.h"
#include "weapons/DroppedWeapon.h"

class CharacterManager {
private:
    std::map<uint8_t, bool> teams;
    std::map<uint8_t, Character> entities;
    std::map<uint8_t, SdlTexture> weapons;
    SdlTexture blood;
    SdlTexture legs;
    SdlTexture* terrorist;
    SdlTexture* counterTerrorist;
    uint8_t playerId;
    void changeSides();
public:
    CharacterManager(SdlWindow& window, YAML::Node& config);

    void setPlayerId(uint8_t id);
    bool assignTeams(std::map<uint8_t, bool> teamMap);
    void createCharacters(SdlTexture& terroristTexture, SdlTexture& counterTexture);

    void updatePositions(std::map<uint8_t, std::pair<float, float>> &positionMap, Camera& camera);
    void updateAngles(std::map<uint8_t, int16_t> &angles);
    void hit(uint8_t id, Camera& camera);
    void kill(uint8_t id, Camera& camera);
    void changeWeapon(uint8_t weaponCode, uint8_t playerId);
    void attack(uint8_t id, Camera& camera);

    void draw(Camera& camera, size_t iteration);

    ~CharacterManager();

    void plantBomb(uint8_t dropperId, std::vector<DroppedWeapon> &bombDrop, SdlTexture& droppedBomb);
    void reviveAll();
};


#endif
