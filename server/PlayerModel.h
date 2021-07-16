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
    bool isFrozen;
    bool isAttacking;

    int maxHp;
    int hp;
    int money;

    Armory armory;

    void freeze();
    void unfreeze();

    public:
        PlayerModel(b2Body* body, std::shared_ptr<Bomb> bomb, DroppedWeapons& dropped, const std::map<int, int>& matchConfig);

        PlayerModel(const PlayerModel& other) = delete;
        PlayerModel& operator=(const PlayerModel& other) = delete;

        PlayerModel(PlayerModel&& other) noexcept;
        PlayerModel& operator=(PlayerModel&& other) noexcept;

        void startMove(int dir);
        void stopMove(int dir);

        void startAttack();
        void stopAttack();

        void step();

        void reposition(MapLayout& mapLayout);
        const b2Vec2& getPosition() const;

        void setAngle(int16_t newAngle);
        const int16_t getAngle() const;

        bool attack(const b2Vec2& enemy);
        void reload();
        std::shared_ptr<Weapon> hit();
        bool gotHitAndDied(std::shared_ptr<Weapon> weapon);
        bool canShoot();

        void giveBomb();
        bool startPlanting();
        bool stopPlanting();

        bool startDefusing();
        bool stopDefusing();

        // void resetCooldown();

        int equipWeapon(int weaponType);
        bool buyWeapon(uint8_t weaponCode);
        int pickUpWeapon();

        void die();
        void kill();
        void revive();

        void changeSide();

        bool getSide() const;
        int getHp() const;
        int getMoney() const;
        int getClip() const;
};

#endif
