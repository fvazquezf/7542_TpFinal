#include "Bomb.h"

Bomb::Bomb()
: Weapon(BOMB){
    damage = 10;
    cooldown = 0;
}


Bomb::~Bomb(){

}

bool Bomb::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;
    double dist = static_cast<double>((player - enemy).LengthSquared());
    // 1.25 es la distancia(1.11m) de ataque al cuadrado, si esta mas lejos no le pega.
    if (dist < 1.15) {
        int res = static_cast<int>(atan2(enemy.y - player.y, enemy.x - player.x));
        int enemyAngle = res * 180/3.14 + 90;
        if (enemyAngle < 0){
            enemyAngle += 360;
        }
        int start = (angle) - 45;
        int end = (angle) + 45;
        if (start < end){
            return (start < enemyAngle && enemyAngle < end);
        } else {
            if (start < enemyAngle) return true;
            if (end > enemyAngle) return true;
        }
    }
    return false;
}


int Bomb::hit(){
    return damage;
}

bool Bomb::tickCooldown(){
    if (cooldown == 0) {
        cooldown = 30;
        return true;
    } else {
        cooldown--;
        return false;
    }
}

void Bomb::resetCooldown(){
    cooldown = 0;
}

