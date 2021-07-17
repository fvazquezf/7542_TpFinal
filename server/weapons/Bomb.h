#ifndef BOMB_H
#define BOMB_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

#define INACTIVE 0
#define PLANTING 1
#define ACTIVE 2
#define DEFUSING 3
#define DEFUSED 4
#define EXPLODED 5


class Bomb: public Weapon {
    private:
        int state;

        int plantingCooldown;
        int plantingTicks;
        int defusingTicks;

        int fuse;
        int remainingTime;

        int planter;

        int firerate;
        int spread;

    public:
        Bomb(int range, int spread, int damage, int firerate, int fuse, int activateTime, int bounty);
        ~Bomb() override;

        bool attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) override;
        bool canShoot(bool isAttacking) override;
        void resetCooldown() override;
        int hit() override;
        int getClip() override;

        void startPlanting(int id);
        void stopPlanting();
        void startDefusing();  
        void stopDefusing();  
        int tic(); 

        int getState();    

        void reset();

        int getPlanter();
        int getFuse();
};

#endif 
