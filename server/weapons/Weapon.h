#ifndef WEAPON_H
#define WEAPON_H

#include <memory>
#include "../../libs/box2d/include/box2d/box2d.h"

#define RIFLE 0
#define M3 1
#define AWP 2
#define KNIFE 3
#define PISTOL 4
#define BOMB 5

class Weapon {
protected:
    int ammo;
    int clip;
    double range;
    int damage;
    int cooldown;
    int bounty;
    uint8_t weaponCode;
public:
    Weapon(uint8_t weaponCode, int ammo, int range, int damage, int bounty);

    virtual bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) = 0;
    virtual bool canShoot(bool isAttacking) = 0;
    void tickCooldown();
    virtual void resetCooldown() = 0;
    void reload();
    virtual int hit() = 0;
    int getBounty();

    virtual ~Weapon();

    uint8_t getWeaponCode();
    virtual int getClip();
};


#endif
