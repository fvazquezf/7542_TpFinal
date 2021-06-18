#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include "../libs/box2d/include/box2d/box2d.h"
#include "../common/thread.h"
#include "Broadcaster.h"
#include "PlayerModel.h"

#include <map>

class WorldModel: public Thread {
    b2World world;
    b2Body* anchor;
    std::map<int, PlayerModel> playerModels;

    float timeStep;
	int32 velocityIterations;
	int32 positionIterations;

    bool is_running;

    Broadcaster& updates;

    public:
        WorldModel(Broadcaster& updates);

        ~WorldModel() override;
        void run() override;
        void stop();
        bool isDead();

        WorldModel(const WorldModel&) = delete;
        WorldModel& operator=(const WorldModel&) = delete;
        WorldModel(WorldModel&& other) = delete;
        WorldModel& operator=(WorldModel&& other) = delete;

        // usar solo para probar cosas en demo_movimiento, esta se va a borrar
        PlayerModel& createPlayer(float x, float y, int clave);


        PlayerModel& addPlayer(int clave);
        void createBox(b2BodyDef& boxDef);
        void loadMap();

        void step();
};

#endif