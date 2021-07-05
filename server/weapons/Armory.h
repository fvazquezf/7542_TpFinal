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
#include "Rifle.h"
#include "Bomb.h"
#include "DroppedWeapons.h"


class Armory {
    std::map<int, std::shared_ptr<Weapon>> arsenal;
    std::map<uint8_t, int> prices;
    DroppedWeapons& dropped;

    std::shared_ptr<Weapon> awp;
    std::shared_ptr<Weapon> rifle;
    std::shared_ptr<Weapon> shotgun;

    int currentWeapon;

    void selectWeapon(uint8_t weaponCode);
    public:
        Armory(DroppedWeapons& dropped, const std::map<int, int>& matchConfig);

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy);

        void reload();
        
        std::shared_ptr<Weapon> hit();

        bool canShoot();

        void tickCooldown();

        void resetCooldown();

        void giveBomb(std::shared_ptr<Weapon> bomb);

        bool startPlanting();

        int equipWeapon(int weaponType);

        void dropPrimary(const b2Vec2& playerPosition);

        bool tryBuying(uint8_t weaponCode, int& playerMoney, const b2Vec2& playerPosition);

        bool pickUpWeapon(const b2Vec2& position);

        Armory(const Armory& other) = delete;
        Armory& operator=(const Armory& other) = delete;

        Armory(Armory&& other) noexcept;
        Armory& operator=(Armory&& other) noexcept;
};


#endif
