#include <iostream>
#include "Rifle.h"

Rifle::Rifle(int ammo, int range, int accuracy, int damage, int firerate)
: Weapon(RIFLE, ammo, range, damage){
    this->firerate = firerate;
    this->accuracy = static_cast<double>(accuracy)/100;
    bulletCount = 0;
}


Rifle::~Rifle(){

}

bool Rifle::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    b2Vec2 bulletPosition(player);

    b2Vec2 bulletDirection(sin(angle * 3.14f/180.0f), -cos(angle * 3.14f/180.0f));
    double oldDist = INFINITY;
    double currDist;
    double bulletTravelledDistance = 0;

    while (bulletTravelledDistance < range){
        bulletTravelledDistance+= bulletDirection.Length();
        bulletPosition.operator+=(bulletDirection);

        if ((currDist = (bulletPosition - enemy).Length()) < 0.5) return true;
        // si me aleje, entonces no le voy a pegar
        if (oldDist < currDist) return false;
        oldDist = currDist;
    }
    return false;
}

int Rifle::hit(){
    return damage;
}

bool Rifle::canShoot(bool isAttacking){
    if (isAttacking || bulletCount != 0) {
        if (cooldown == 0 && clip != 0) {
            if (bulletCount == 3) {
                bulletCount = 0;
                return false;    
            }
            clip--;
            bulletCount++;
            cooldown = firerate;
            return true;
        }
    }
    return false;
}

void Rifle::resetCooldown(){

}
