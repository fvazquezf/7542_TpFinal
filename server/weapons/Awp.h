#ifndef AWP_H
#define AWP_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

class Awp: public Weapon {
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
        Awp();
        ~Awp() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool tickCooldown() override;
        void resetCooldown() override;
        int hit() override;


};

#endif
