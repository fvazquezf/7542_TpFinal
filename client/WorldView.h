#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <vector>
#include <mutex>
#include <memory>
#include <map>
#include <cstdint>
#include <atomic>
#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include "anim/Character.h"
#include "Renderizable.h"
#include "Camera.h"
#include "Stencil.h"
#include "NonMovable.h"
#include "BuyingMenu.h"
#include "Hud.h"
#include "weapons/DroppedWeapon.h"
#include "SoundManager.h"
#include "MapView.h"
#include "LobbyScreen.h"
#include "Cursor.h"
#include "anim/Explosion.h"

class WorldView {
private:
    SdlWindow& window;
    YAML::Node& clientConfig;
    Camera camera;
    Stencil stencil;
    BuyingMenu menu;
    Hud hud;
    MapView map;
    LobbyScreen lobby;
    Cursor cursor;
    Explosion bombExplosion;

    std::atomic_bool lobbyTime;
    std::atomic_bool menuTime;
    std::atomic_bool done;

    SdlTexture terror;
    SdlTexture counterTerrorist;
    SdlTexture blood;
    SdlTexture legs;

    std::map<uint8_t, Character> entities;
    std::map<uint8_t, SdlTexture> weapons;
    std::map<uint8_t, SdlTexture> dropTextures;

    std::vector<DroppedWeapon> droppedWeapons; // va a mapView

    // varios hilos acceden de manera concurrente a la view
    // SDL, Drawer, Receiver
    // funciona como monitor

    std::mutex worldMutex;
    uint8_t playerId;
public:
    WorldView(SdlWindow& window, YAML::Node& clientConfig);

    WorldView(const WorldView& other) = delete;
    WorldView& operator=(const WorldView& other) = delete;

    WorldView(WorldView&& other) = delete;
    WorldView& operator=(WorldView&& other) = delete;

    bool menuButtonPressed(int mouseX, int mouseY);
    bool lobbyButtonPressed(int mouseX, int mouseY);
    uint8_t getPressedButtonCode();
    void setMenu(bool isIt);
    bool isMenuTime() const;

    void characterEntityCreate(uint8_t id, bool isPlayer, bool isCt);
    void changeWeapon(uint8_t weaponCode, uint8_t playerId);

    void updatePositions(std::map<uint8_t, std::pair<float, float>>& positionMap);
    void updateAngles(std::map<uint8_t, int16_t>& angles);
    void render(size_t iteration);

    ~WorldView();

    int16_t getPlayerAngle();

    void attack(uint8_t id);

    void hit(uint8_t id);

    void kill(uint8_t id);

    void dropWeapon(std::tuple<uint8_t, size_t, int16_t, int16_t>& weaponIdentification);

    void pickupWeapon(std::tuple<uint8_t, size_t, int16_t, int16_t>& weaponIdentification);

    void buildTeams(const std::map<uint8_t, bool> &teamMap);

    void assignPlayer(uint8_t aPlayerId);

    void updateHudTime(uint8_t time);

    void updateHudHealth(uint8_t health);

    void updateHudMoney(uint16_t money);

    void signalDone();
    bool isDone();

    void buildMap(const std::string &mapString);

    void stopLobby();

    void updateHudClip(uint8_t clip);

    void plantBomb(uint8_t planterId);

    void blowBomb();
};


#endif
