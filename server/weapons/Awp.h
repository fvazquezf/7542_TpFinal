#ifndef AWP_H
#define AWP_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

class Awp: public Weapon {
    private:
        // distancia al hit, sirve para ajustar la precision
        double hitDistance;
        double accuracy;
        int firerate;
    public:
        Awp(int ammo, int range, int accuracy, int damage, int firerate);
        ~Awp() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool tickCooldown() override;
        void resetCooldown() override;
        int hit() override;


};

#endif
