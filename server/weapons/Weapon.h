#ifndef WEAPON_H
#define WEAPON_H

#include <memory>
#include "../../libs/box2d/include/box2d/box2d.h"

#define AK47 0
#define M3 1
#define AWP 2
#define KNIFE 3
#define PISTOL 4
#define BOMB 5

class Weapon {
protected:
    int damage;
    int cooldown;
    uint8_t weaponCode;
public:
    explicit Weapon(uint8_t weaponCode);

    virtual bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) = 0;
    
    virtual bool tickCooldown() = 0;

    virtual void resetCooldown() = 0;

    virtual int hit() = 0;

    virtual ~Weapon();

    static std::shared_ptr<Weapon> getArmoryWeapon(uint8_t weaponCode);

    uint8_t getWeaponCode();
};


#endif
