#ifndef BOMB_H
#define BOMB_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

class Bomb: public Weapon {
    private:
        bool planting;
        bool active;
        bool exploded;
        bool defusing;
        bool defused;

        int plantingCooldown;
        int plantingTicks;
        int defusingTicks;

        int fuse;
        int remainingTime;

        int planter;

        int firerate;
        int spread;

    public:
        Bomb(int range, int spread, int damage, int firerate, int fuse, int activateTime);
        ~Bomb() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool canShoot() override;
        void resetCooldown() override;
        int hit() override;
        int getClip() override;

        bool startPlanting();
        void stopPlanting();
        void tickPlanting();
        void tickFuse();

        bool startDefusing();  
        bool stopDefusing();  
        void tickDefuse();   

        bool isPlanting();
        bool isActive();
        bool isDefusing();
        bool isBoom();
        bool isDefused();       

        void reset();

        void setPlanter(int id);
        int getPlanter();
        int getFuse();
};

#endif
