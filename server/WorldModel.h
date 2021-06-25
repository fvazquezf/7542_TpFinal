#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include "../libs/box2d/include/box2d/box2d.h"
#include "../common/Thread.h"
#include "Broadcaster.h"
#include "PlayerModel.h"
#include "events/ClientEvent.h"
#include "../common/ProtectedQueue.h"
#include <memory>
#include <utility>

#include <map>
#include <unordered_set>

class WorldModel: public Thread {
    b2World world;
    b2Body* anchor;
    std::map<int, PlayerModel> playerModels;

    std::unordered_set<int> attackingPlayers;

    // ref de la cola de la cual popeamos
    // para obtener los eventos de los clientes
    // cada receiver pushea a esta q
    ProtectedQueue<std::unique_ptr<ClientEvent>> usersEvents;

    Broadcaster& updates;

    float timeStep;
	int32 velocityIterations;
	int32 positionIterations;

    bool is_running;

    public:
        explicit WorldModel(Broadcaster& updates);

        ~WorldModel() override;
        void run() override;
        void stop();
        bool isDead();

        WorldModel(const WorldModel&) = delete;
        WorldModel& operator=(const WorldModel&) = delete;

        WorldModel(WorldModel&& other) noexcept;
        WorldModel& operator=(WorldModel&& other) noexcept;

        ProtectedQueue<std::unique_ptr<ClientEvent>>& addPlayer(int clave);

        void updateAngles();
        void updateAttack(int id);
        void updateHit(int id);
        void updateDead(int id);

        void movePlayer(uint8_t id, uint8_t dir);
        void stopMovingPlayer(uint8_t id, uint8_t dir);
        void rotatePlayer(uint8_t id, int16_t angle);
        void startAttack(uint8_t id);
        void stopAttack(uint8_t id);


        void createBox(b2BodyDef& boxDef);
        void loadMap();

        void step();

    void updatePositions();
};

#endif