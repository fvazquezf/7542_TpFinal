#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include "../libs/box2d/include/box2d/box2d.h"
#include "PlayerModel.h"

#include <map>

class WorldModel{
    b2World world;
    b2Body* anchor;
    std::map<std::string, PlayerModel> playerModels;

    float timeStep;
	int32 velocityIterations;
	int32 positionIterations;

    public:
        WorldModel();

        // usar solo para probar cosas en demo_movimiento, esta se va a borrar
        PlayerModel& createPlayer(float x, float y, std::string clave);


        PlayerModel& addPlayer(std::string clave);
        void createBox(b2BodyDef& boxDef);
        void loadMap();

        void step();
};

#endif