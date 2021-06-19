#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "../libs/box2d/include/box2d/box2d.h"

class PlayerModel{
    b2Body* model;
    b2Vec2 netForce;

    public:
        PlayerModel();
        PlayerModel(b2Body* body);

        void startMove(int dir);

        void stopMove(int dir);

        void reposition(float x, float y);

        const b2Vec2& getPosition();

        void step();

};

#endif
