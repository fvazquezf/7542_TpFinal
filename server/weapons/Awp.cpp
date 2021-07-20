#include <iostream>
#include "Awp.h"

Awp::Awp(int ammo, int range, int accuracy, int damage, int firerate, int bounty): 
 Weapon(AWP, ammo, range, damage, bounty),
 firerate(firerate) {
    this->accuracy = static_cast<double>(accuracy)/100;
}


Awp::~Awp() {

}

bool Awp::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) {
    b2Vec2 bulletPosition(player);
    b2Vec2 bulletDirection(sin(angle * 3.14f/180.0f), -cos(angle * 3.14f/180.0f));
    double oldDist = INFINITY;
    double currDist;
    double bulletTravelledDistance = 0;

    while (bulletTravelledDistance < range) {
        bulletTravelledDistance+= bulletDirection.Length();
        bulletPosition.operator+=(bulletDirection);

        if ((currDist = (bulletPosition - enemy).Length()) < accuracy) return true;
        // si me aleje, entonces no le voy a pegar
        if (oldDist < currDist) return false;
        oldDist = currDist;
    }
    return false;
}

int Awp::hit() {
    return damage;
}

bool Awp::canShoot(bool isAttacking) {
    if (cooldown == 0 && clip != 0 && isAttacking) {
        clip--;
        cooldown = firerate;
        return true;
    } else {
        return false;
    }
}

void Awp::resetCooldown() {
    // no hace nada porque solo se puede volver a disparar cuando pasa el cooldown
    // no es como la pistola que dispara cada vez que haces click
}

