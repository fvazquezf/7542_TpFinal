#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

class Shotgun: public Weapon {
    private:
        int damage;
        int cooldown;

    protected:
        void calcDamage(float dist);

    public:
        Shotgun();
        ~Shotgun() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool tickCooldown() override;
        void resetCooldown() override;
        int hit() override;


};

#endif
