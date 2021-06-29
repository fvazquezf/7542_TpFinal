#ifndef PISTOL_H
#define PISTOL_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

class Pistol: public Weapon {
    private:
        int damage;
        int cooldown;

        // distancia maxima de "viaje" de la bala
        double maxHittingDistance;
    public:
        Pistol();
        ~Pistol() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool tickCooldown() override;
        void resetCooldown() override;
        int hit() override;


};

#endif
