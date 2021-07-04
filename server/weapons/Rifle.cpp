#include <iostream>
#include "Rifle.h"

Rifle::Rifle(int ammo, int range, int accuracy, int damage, int firerate)
: Weapon(RIFLE, ammo, range, accuracy, damage){
    hitDistance = 0;
}


Rifle::~Rifle(){

}

bool Rifle::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;
    if (ammo == 0) return 0;
    ammo--;

    b2Vec2 bulletPosition(player);

    b2Vec2 bulletDirection(sin(angle * 3.14f/180.0f), -cos(angle * 3.14f/180.0f));
    double oldDist = INFINITY;
    double currDist = 0;
    double bulletTravelledDistance = 0;

    while (bulletTravelledDistance < range){
        bulletTravelledDistance+= bulletDirection.Length();
        bulletPosition.operator+=(bulletDirection);

        if ((currDist = (bulletPosition - enemy).Length()) < 0.5) {
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
// para la Rifle el daño no depende de la dist
// lo que si depende es la accuracy (si le pego o no)
// si no le pego, daño = 0, si le pego, daño = max
int Rifle::hit(){
    return damage;
}

bool Rifle::tickCooldown(){
    if (cooldown == 0) {
        // este 60 es variable, es el que determina el fireRate, se leeria del yaml de configuracion.
        cooldown = firerate;
        return true;
    } else {
        cooldown--;
        return false;
    }
}

void Rifle::resetCooldown(){
}
