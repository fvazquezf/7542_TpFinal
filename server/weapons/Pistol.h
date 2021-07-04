#ifndef PISTOL_H
#define PISTOL_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

class Pistol: public Weapon {
    private:

    public:
        Pistol(int ammo, int range, int accuracy, int damage);
        ~Pistol() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool tickCooldown() override;
        void resetCooldown() override;
        int hit() override;


};

#endif
