#include "Shotgun.h"

Shotgun::Shotgun(int ammo, int range, int spread, int damage)
: Weapon(M3, ammo, range, damage),
  spread(spread){
    damageOutput = 0;
}


Shotgun::~Shotgun(){

}

bool Shotgun::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;
    if (ammo == 0) return false;
    ammo--;
    double dist = static_cast<double>((player - enemy).Length());
    if (dist < range) {
        double res = atan2(enemy.y - player.y, enemy.x - player.x);
        // el round creo que esta de mas
        int enemyAngle = std::round(res * 180/3.14) + 90;
        if (enemyAngle < 0){
            enemyAngle += 360;
        }
        int start = (angle) - accuracy;
        int end = (angle) + accuracy;
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
    damageOutput = damage/5;
    if (dist < range/2){
        damageOutput = damage/3;
        if (dist < range/5){
            damageOutput = damage;
        }
    }
}

int Shotgun::hit(){
    return damageOutput;
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

