#include "Shotgun.h"

Shotgun::Shotgun(){
    damage = 0;
    cooldown = 0;
}


Shotgun::~Shotgun(){

}

bool Shotgun::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;
    float dist = (player - enemy).LengthSquared();
    // 900 es la distancia(30m) maxima de ataque al cuadrado, si esta mas lejos no le pega.
    if (dist < 900.0f) {
        double res = atan2(enemy.y - player.y, enemy.x - player.x);
        // el round creo que esta de mas
        int enemyAngle = std::round(res * 180/3.14) + 90;
        if (enemyAngle < 0){
            enemyAngle += 360;
        }
        int start = (angle) - 30;
        int end = (angle) + 30;
        if (start < end){
            if (start < enemyAngle && enemyAngle < end){
                calcDamage(dist);
                return true;
            } 
        } else {
            if (start < enemyAngle) {
                calcDamage(dist);
                return true;
            } 
            if (end > enemyAngle) {
                calcDamage(dist);
                return true;
            } 
        }
    }
    return false;
}

void Shotgun::calcDamage(float dist){
    damage = 20;
    if (dist < 400.0f){
        damage = 50;
        if (dist < 64.0f){
            damage = 100;
        }
    }
}

int Shotgun::hit(){
    return damage;
}

bool Shotgun::tickCooldown(){
    if (cooldown == 0) {
        cooldown = 1;
        return true;
    } else {
        return false;
    }
}

void Shotgun::resetCooldown(){
    cooldown = 0;
}

