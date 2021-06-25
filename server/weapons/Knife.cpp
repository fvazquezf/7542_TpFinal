#include "Knife.h"

Knife::Knife(){
    damage = 40;
    cooldown = 0;
}


Knife::~Knife(){

}

bool Knife::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;
    float dist = (player - enemy).LengthSquared();
    // 2.25 es la distancia de ataque al cuadrado, si esta mas lejos no le pega.
    if (dist < 2.25f) {
        double res = atan2(enemy.y - player.y, enemy.x - player.x);
        // el round creo que esta de mas
        int enemyAngle = std::round(res * 180/3.14);

        int start = (angle - 90) - 60;
        int end = (angle - 90) + 60;
        if (start < end){
            return (start < enemyAngle && enemyAngle < end);
        } else {
            if (start < enemyAngle) return true;
            if (end > enemyAngle) return true;
        }
    }
    return false;
}

int Knife::hit(){
    return damage;
}

bool Knife::tickCooldown(){
    if (cooldown == 0) {
        // este 30 es variable, es el que determina el fireRate, se leeria del yaml de configuracion.
        cooldown = 30;
        return true;
    } else {
        cooldown--;
        return false;
    }
}

void Knife::resetCooldown(){
    cooldown = 0;
}

