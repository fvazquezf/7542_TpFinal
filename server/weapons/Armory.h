#ifndef ARMORY_H
#define ARMORY_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include <map>
#include <memory>
#include "Weapon.h"
#include "Knife.h"
#include "Pistol.h"
#include "Shotgun.h"
#include "Awp.h"


class Armory {

    std::map<int, std::shared_ptr<Weapon>> arsenal;

    int currentWeapon;

    public:
        Armory();

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy);
        
        std::shared_ptr<Weapon> hit();

        bool tickCooldown();

        void resetCooldown();

        void equipKnife();
        int equipPrimary();
        void equipSecondary();
        bool equipBomb();
};


#endif
