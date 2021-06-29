#ifndef KNIFE_H
#define KNIFE_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"
#include <random>

class Knife: public Weapon {
    private:
        int damage;
        int cooldown;

    public:
        Knife();
        ~Knife() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool tickCooldown() override;
        void resetCooldown() override;
        int hit() override;


};

#endif
