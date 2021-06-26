#ifndef AWP_H
#define AWP_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

class Awp: public Weapon {
    private:
        int damage;
        int cooldown;

    public:
        Awp();
        ~Awp() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool tickCooldown() override;
        void resetCooldown() override;
        int hit() override;


};

#endif
