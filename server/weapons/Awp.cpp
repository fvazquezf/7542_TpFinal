#include <iostream>
#include "Awp.h"

Awp::Awp(int ammo, int range, int accuracy, int damage, int firerate): 
 Weapon(AWP, ammo, range, accuracy, damage),
 firerate(firerate) {
    hitDistance = 0;
}


Awp::~Awp(){

}

bool Awp::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;
    if (clip == 0) return false;
    clip--;

    b2Vec2 bulletPosition(player);
    b2Vec2 bulletDirection(sin(angle * 3.14f/180.0f), -cos(angle * 3.14f/180.0f));
    double oldDist = INFINITY;
    double currDist = 0;
    double bulletTravelledDistance = 0;

    while (bulletTravelledDistance < range){
        bulletTravelledDistance+= bulletDirection.Length();
        bulletPosition.operator+=(bulletDirection);

        if ((currDist = (bulletPosition - enemy).Length()) < accuracy) {
            hitDistance = currDist;
            return true;
        }
        // si me aleje, entonces no le voy a pegar
        if (oldDist < currDist){
            return false;
        }
        oldDist = currDist;
    }
    return false;
}

int Awp::hit(){
    return damage;
}

bool Awp::tickCooldown(){
    if (cooldown == 0) {
        cooldown = firerate;
        return true;
    } else {
        cooldown--;
        return false;
    }
}

void Awp::resetCooldown(){
    // no hace nada porque solo se puede volver a disparar cuando pasa el cooldown
    // no es como la pistola que dispara cada vez que haces click
}

