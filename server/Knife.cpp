#include "Knife.h"

Knife::Knife(){
    damage = 40;
    cooldown = 30;
}

bool Knife::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;
    float dist = (player - enemy).LengthSquared();
    if (dist < 2.25f) {
        double res = atan2(enemy.y - player.y, enemy.x - player.x);
        int enemyAngle = std::round(res * 180/3.14);

        int start = (angle + 90) - 60;
        int end = (angle + 90) + 60;
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

void Knife::tickCooldown(){
    if (cooldown == 0) {
        cooldown = 30;
    } else {
        cooldown--;
    }
}

void Knife::resetCooldown(){
    cooldown = 0;
}

