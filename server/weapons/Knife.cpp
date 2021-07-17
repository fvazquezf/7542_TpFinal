#include "Knife.h"

Knife::Knife(int range, int spread, int damage, int firerate, int bounty):
 Weapon(KNIFE, 0, range, damage, bounty),
 firerate(firerate),
 spread(spread){
}

Knife::~Knife(){
}

bool Knife::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    double dist = static_cast<double>((player - enemy).Length());
    if (dist < range) {
        int res = static_cast<int>(atan2(enemy.y - player.y, enemy.x - player.x));
        int enemyAngle = res * 180/3.14 + 90;
        if (enemyAngle < 0){
            enemyAngle += 360;
        }
        int start = (angle) - spread;
        int end = (angle) + spread;
        if (start < end){
            return (start < enemyAngle && enemyAngle < end);
        } else {
            if (start < enemyAngle) return true;
            if (end > enemyAngle) return true;
        }
    }
    return false;
}

// cuchillo
// produce daño random entre min y max damage
// distribucion uniforme
int Knife::hit(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dmgDist(0, damage);
    return dmgDist(gen);
}

bool Knife::canShoot(bool isAttacking){
    if (cooldown == 0 && isAttacking) {
        cooldown = firerate;
        return true;
    } else {
        return false;
    }
}

void Knife::resetCooldown(){
    cooldown = 0;
}

int Knife::getClip(){
    return -1;
}

