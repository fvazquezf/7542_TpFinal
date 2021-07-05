#ifndef BOMB_H
#define BOMB_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

class Bomb: public Weapon {
    private:
        bool planting;
        bool active;
        bool exploded;

        int plantingCooldown;
        int plantingTicks;

        int planter;

        int firerate;
        int spread;

    public:
        Bomb(int range, int spread, int damage, int firerate);
        ~Bomb() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool canShoot() override;
        void resetCooldown() override;
        int hit() override;

        bool startPlanting();
        void setPlanter(int id);
        int getPlanter();
        void stopPlanting();
        bool isPlanting();
        void tickPlanting();
        bool isActive();
        bool defuse();
};

#endif
