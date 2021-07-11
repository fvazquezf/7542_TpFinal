#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include "../libs/box2d/include/box2d/box2d.h"
#include "../common/Thread.h"
#include "Broadcaster.h"
#include "PlayerModel.h"
#include "MapLayout.h"
#include "Tally.h"
#include "events/ClientEvent.h"
#include "../common/ProtectedQueue.h"
#include <memory>
#include <utility>
#include "yaml-cpp/yaml.h"

#include <map>
#include <unordered_set>

class WorldModel: public Thread {
    b2World world;
    b2Body* anchor;
    const std::map<int, int>& matchConfig;
    std::map<int, PlayerModel> playerModels;
    std::shared_ptr<Bomb> bomb;

    MapLayout mapLayout;
    Tally tally;
    

    std::unordered_set<int> attackingPlayers;

    // ref de la cola de la cual popeamos
    // para obtener los eventos de los clientes
    // cada receiver pushea a esta q
    ProtectedQueue<std::unique_ptr<ClientEvent>> usersEvents;

    Broadcaster& updates;
    DroppedWeapons droppedWeapons;

    float timeStep;
	int32 velocityIterations;
	int32 positionIterations;

    bool purchaseFase;
    bool is_running;
    
    public:
        WorldModel(Broadcaster& updates, const std::map<int, int>& matchConfig);

        ~WorldModel() override;
        void run() override;
        void stop();
        bool isDead();

        WorldModel(const WorldModel&) = delete;
        WorldModel& operator=(const WorldModel&) = delete;

        WorldModel(WorldModel&& other) noexcept;
        WorldModel& operator=(WorldModel&& other) noexcept;

        ProtectedQueue<std::unique_ptr<ClientEvent>>& addPlayer(int clave);

        void createBox(b2BodyDef& boxDef);
        void createMapBorder(b2BodyDef& boxDef, int xSide, int ySide);
        void loadMap(YAML::Node& mapInfo);

        void updatePositions();
        void updateAngles();
        void updateAttack(int id);
        void updateHit(int id);
        void updateDead(int id);
        void updateWeapon(uint8_t id, uint8_t code);
        void updateBuying(bool buying);
        void updateTeams();
        void updateHp(int id);
        void updateMoney(int id);
        void updateTime();
        void updateBombPlanted(int id);
        void updateCtWinRound();
        void updateTtWinRound();
        void updateBombExplode();

        
        void movePlayer(uint8_t id, uint8_t dir);
        void stopMovingPlayer(uint8_t id, uint8_t dir);
        void rotatePlayer(uint8_t id, int16_t angle);
        void startAttack(uint8_t id);
        void stopAttack(uint8_t id);
        void startPlanting(uint8_t id);
        void stopPlanting(uint8_t id);


        void buyWeapon(uint8_t id, uint8_t weaponCode);
        void equipWeapon(uint8_t id, uint8_t weaponType);
        void pickUpWeapon(uint8_t id);
        void reloadWeapon(uint8_t id);

        void roundPurchase();
        void roundCommon();
        void roundPlay();

        void swapTeams();
        void reviveAll();

        void step();


    void plantingLogic();
    void resetRound();
    void disconnectPlayer(uint8_t id);
};

#endif
