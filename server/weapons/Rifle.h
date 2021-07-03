#ifndef RIFLE_H
#define RIFLE_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

class Rifle: public Weapon {
    private:
        int damage;
        int cooldown;
        // probabilidad de que el disparo sea o no hit
        // depende de la distancia al enemigo
        double precision;
        // distancia al hit, sirve para ajustar la precision
        double hitDistance;
        // distancia maxima de "viaje" de la bala
        double maxHittingDistance;
    public:
        Rifle();
        ~Rifle() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool tickCooldown() override;
        void resetCooldown() override;
        int hit() override;


};

#endif
