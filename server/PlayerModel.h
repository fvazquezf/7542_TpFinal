#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "../libs/box2d/include/box2d/box2d.h"
#include "weapons/Armory.h"
#include "MapLayout.h"
#include <memory>

class PlayerModel{
    b2Body* model;
    b2Vec2 netForce;
    int16_t angle;

    int dirAmount;

    bool isCt;

    int hp;
    int money;
    bool isAlive;

    Armory armory;

    public:
        PlayerModel(b2Body* body, DroppedWeapons& dropped, const std::map<int, int>& matchConfig);

        PlayerModel(const PlayerModel& other) = delete;
        PlayerModel& operator=(const PlayerModel& other) = delete;

        PlayerModel(PlayerModel&& other) noexcept;
        PlayerModel& operator=(PlayerModel&& other) noexcept;

        void startMove(int dir);
        void stopMove(int dir);

        void step();

        void reposition(MapLayout& mapLayout);
        const b2Vec2& getPosition();

        void setAngle(int16_t newAngle);
        int16_t getAngle() const;

        bool attack(PlayerModel& enemy);
        void reload();
        std::shared_ptr<Weapon> hit();
        bool gotHitAndDied(std::shared_ptr<Weapon> weapon);
        int getHp();
        int getMoney();

        bool canShoot();
        void resetCooldown();

        int equipWeapon(int weaponType);
        bool buyWeapon(uint8_t weaponCode);
        bool pickUpWeapon();

        void die();
        void revive();

        void changeSide();
        bool getSide();
};

#endif
