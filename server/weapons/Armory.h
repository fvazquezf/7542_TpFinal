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

// WeaponTypes, las armas que puede tener un jugador al mismo tiempo
#define PRIMARY 0
#define SECONDARY 1
#define MELEE 2
#define EXPLOSIVE 3


class Armory {
    std::map<int, std::shared_ptr<Weapon>> arsenal;
    std::map<uint8_t, int> prices;
    DroppedWeapons& dropped;

    std::shared_ptr<Weapon> awp;
    std::shared_ptr<Weapon> rifle;
    std::shared_ptr<Weapon> shotgun;
    std::shared_ptr<Bomb> bomb;

    int currentWeapon;

    void selectWeapon(uint8_t weaponCode);
    public:
        Armory(std::shared_ptr<Bomb> bomb, DroppedWeapons& dropped, const std::map<int, int>& matchConfig);

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy);
        void reload();
        int bounty();
        std::shared_ptr<Weapon> hit();
        bool canShoot(bool isAttacking);

        void tickCooldown();
        void resetCooldown();

        void giveBomb();

        bool startPlanting(int id);
        bool stopPlanting();
        bool startDefusing();
        bool stopDefusing();

        int equipWeapon(int weaponType);
        void dropWeapons(const b2Vec2& playerPosition);
        bool tryBuying(uint8_t weaponCode, int& playerMoney, const b2Vec2& playerPosition);
        int pickUpWeapon(const b2Vec2& position, bool isCt);

        int getClip() const;

        Armory(const Armory& other) = delete;
        Armory& operator=(const Armory& other) = delete;

        Armory(Armory&& other) ;
        Armory& operator=(Armory&& other) ;
};


#endif
