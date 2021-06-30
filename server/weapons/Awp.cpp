#include <iostream>
#include "Awp.h"

Awp::Awp()
: Weapon(AWP){
    damage = 100;
    cooldown = 0;
    precision = 1;
    hitDistance = 0;
    maxHittingDistance = 5; // metros
}


Awp::~Awp(){

}

bool Awp::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;

    b2Vec2 bulletPosition(player);

    b2Vec2 bulletDirection(sin(angle * 3.14f/180.0f), -cos(angle * 3.14f/180.0f));
    double oldDist = INFINITY;
    double currDist = 0;
    double bulletTravelledDistance = 0;

    while (bulletTravelledDistance < maxHittingDistance){
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

    /*double a = y - player.y;
    double b = x - player.x;
    double c = a*player.y + b * player.x;

    double latDist = abs(a * enemy.x + b * enemy.y - c)/ sqrt(a*a + b*b);

    if (latDist < 0.5){
        return true;
    }*/
    
    return false;
}

// para la awp el daño no depende de la dist
// lo que si depende es la precision (si le pego o no)
// si no le pego, daño = 0, si le pego, daño = max
int Awp::hit(){
    return damage;
}

bool Awp::tickCooldown(){
    if (cooldown == 0) {
        // este 60 es variable, es el que determina el fireRate, se leeria del yaml de configuracion.
        cooldown = 60;
        return true;
    } else {
        cooldown--;
        return false;
    }
}

void Awp::resetCooldown(){
}

