#include "Awp.h"

Awp::Awp(){
    damage = 100;
    cooldown = 0;
}


Awp::~Awp(){

}

bool Awp::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;

    int y = cos((angle - 90) * 180/3.14);
    int x = sin((angle - 90) * 180/3.14);

    int a = y - player.y;
    int b = x - player.x;
    int c = a*player.y + b * player.x;

    int latDist = abs(a * enemy.x + b * enemy.y - c)/ sqrt(a*a + b*b);

    if (latDist < 0.125){
        return true;
    }
    
    return false;
}

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

