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
#include "DroppedWeapons.h"


class Armory {
    std::map<int, std::shared_ptr<Weapon>> arsenal;
    std::map<uint8_t, int> prices;
    DroppedWeapons& dropped;

    int currentWeapon;

    public:
        explicit Armory(DroppedWeapons& dropped);

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy);
        
        std::shared_ptr<Weapon> hit();

        bool tickCooldown();

        void resetCooldown();

        int equipWeapon(int weaponType);

        bool tryBuying(uint8_t weaponCode, int& playerMoney, const b2Vec2& playerPosition);

        Armory(const Armory& other) = delete;
        Armory& operator=(const Armory& other) = delete;

        Armory(Armory&& other) noexcept;
        Armory& operator=(Armory&& other) noexcept;
};


#endif
