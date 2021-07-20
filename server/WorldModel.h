#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include "../libs/box2d/include/box2d/box2d.h"
#include "../common/Thread.h"
#include "Broadcaster.h"
#include "PlayerModel.h"
#include "MapLayout.h"
#include "updates/UpdateManager.h"
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

    // ref de la cola de la cual popeamos
    // para obtener los eventos de los clientes
    // cada receiver pushea a esta q
    ProtectedQueue<std::unique_ptr<ClientEvent>> usersEvents;

    Broadcaster& updates;
    UpdateManager updatesM;
    DroppedWeapons droppedWeapons;

    float timeStep;
	int32 velocityIterations;
	int32 positionIterations;

    bool purchaseFase;
    bool is_running;
    int roundMoneyWon;
    int roundMoneyLost;
    
    void roundPurchase();
    void roundCommon();
    void roundPlay();

    void swapTeams();
    void reviveAll();

    void bombStep();
    void resetRound();
    
    public:
        WorldModel(Broadcaster& updates, const std::map<int, int>& matchConfig);

        ~WorldModel() override;
        void run() override;
        void stop();
        bool isDead();

        WorldModel(const WorldModel&) = delete;
        WorldModel& operator=(const WorldModel&) = delete;

        WorldModel(WorldModel&& other) ;
        WorldModel& operator=(WorldModel&& other) ;

        ProtectedQueue<std::unique_ptr<ClientEvent>>& addPlayer(int clave);
        
        void loadMap(YAML::Node& mapInfo);
        
        void movePlayer(uint8_t id, uint8_t dir);
        void stopMovingPlayer(uint8_t id, uint8_t dir);
        void rotatePlayer(uint8_t id, int16_t angle);
        void startAttack(uint8_t id);
        void stopAttack(uint8_t id);
        void startBombHandling(uint8_t id);
        void stopBombHandling(uint8_t id);

        void buyWeapon(uint8_t id, uint8_t weaponCode);
        void equipWeapon(uint8_t id, uint8_t weaponType);
        void pickUpWeapon(uint8_t id);
        void reloadWeapon(uint8_t id);

        void step();
        void disconnectPlayer(uint8_t id);
};

#endif
