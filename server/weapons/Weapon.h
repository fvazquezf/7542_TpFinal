#ifndef WEAPON_H
#define WEAPON_H

#include "../../libs/box2d/include/box2d/box2d.h"

class Weapon {
protected:
    int damage;
    int cooldown;
public:
    Weapon();

    virtual bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) = 0;
    
    virtual bool tickCooldown() = 0;

    virtual void resetCooldown() = 0;

    virtual int hit() = 0;

    virtual ~Weapon();
};


#endif
