#ifndef KNIFE_H
#define KNIFE_H

#include "../libs/box2d/include/box2d/box2d.h"

class Knife {
    private:
        int damage;
        int cooldown;

    public:
        Knife();

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy);
        void tickCooldown();
        void resetCooldown();
        int hit();
};

#endif
