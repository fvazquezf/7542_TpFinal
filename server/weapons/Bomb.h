#ifndef BOMB_H
#define BOMB_H

#include "../../libs/box2d/include/box2d/box2d.h"
#include "Weapon.h"

#define INACTIVE 0
#define PLANTING 1
#define ACTIVE 2
#define ACTIVATE 3
#define DEFUSING 4
#define DEFUSED 5
#define EXPLODED 6


class Bomb: public Weapon {
    private:
        int state;

        int plantingCooldown;
        int plantingTicks;
        int defusingTicks;

        int fuse;
        int remainingTime;

        int planter;
        b2Vec2 position;
        int explosionRange;

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

        void startPlanting(int id, const b2Vec2& pos);
        void stopPlanting();
        void startDefusing();  
        void stopDefusing();  
        int tic(); 

        bool explosionDamage(const b2Vec2& victim);

        int getState();    

        void reset();

        int getPlanter();
        int getFuse();
};

#endif 
