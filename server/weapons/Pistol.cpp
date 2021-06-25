#include "Pistol.h"

Pistol::Pistol(){
    damage = 25;
    cooldown = 0;
}


Pistol::~Pistol(){

}

bool Pistol::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;
    float dist = (player - enemy).LengthSquared();
    // 2500 es la distancia de ataque al cuadrado, si esta mas lejos no le pega.
    if (dist < 2500.0f) {

        int y = cos((angle - 90) * 180/3.14);
        int x = sin((angle - 90) * 180/3.14);

        int a = y - (int)(player.y);
        int b = x - (int)(player.x);
        int c = a*(int)(player.y) + b * (int)(player.x);

        int latDist = abs(a * enemy.x + b * enemy.y - c)/ sqrt(a*a + b*b);

        if (latDist < 0.25){
            return true;
        }

        // if (start < end){
        //     return (start < enemyAngle && enemyAngle < end);
        // } else {
        //     if (start < enemyAngle) return true;
        //     if (end > enemyAngle) return true;
        // }
    }
    return false;
}

int Pistol::hit(){
    return damage;
}

bool Pistol::tickCooldown(){
    if (cooldown == 0) {
        cooldown = 1;
        return true;
    } else {
        return false;
    }
}

void Pistol::resetCooldown(){
    cooldown = 0;
}

