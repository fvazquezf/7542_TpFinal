#ifndef Weapon_H
#define Weapon_H

#include "../../libs/box2d/include/box2d/box2d.h"

class Weapon {
protected:
    int damage;
    int cooldown;
public:
    Weapon();

    virtual bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy);
    
    virtual bool tickCooldown();

    virtual void resetCooldown();

    virtual int hit();

    virtual ~Weapon();
};


#endif
