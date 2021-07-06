#include "Bomb.h"
#include <iostream>

Bomb::Bomb(int range, int spread, int damage, int firerate):
 Weapon(BOMB, 0, range, damage),
 firerate(firerate),
 spread(spread){
    planting = false;
    defusing = false;
    defused = false;
    planter = -1;
    active = false;
    exploded = false;
    plantingCooldown = 180;
    plantingTicks = 0;
    defusingTicks = 0;
    fuse = 600;
}

Bomb::~Bomb(){
}

bool Bomb::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
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


int Bomb::hit(){
    return damage;
}

bool Bomb::canShoot(){
    if (cooldown == 0) {
        cooldown = firerate;
        return true;
    } else {
        return false;
    }
}

void Bomb::resetCooldown(){
    cooldown = 0;
}


bool Bomb::startPlanting(){
    // aca hay que chequear que este en el site
    planting = true;
    std::cout << "bomb start Planting" << std::endl;
}

void Bomb::setPlanter(int id){
    planter = id;
}

int Bomb::getPlanter(){
    return planter;
}

void Bomb::stopPlanting(){
    planting = false;
    plantingTicks = 0;
    std::cout << "bomb stop Planting" << std::endl;
}

bool Bomb::isPlanting(){
    return planting;
}

void Bomb::tickPlanting(){
    plantingTicks++;
    if (plantingTicks == plantingCooldown){
        active = true;
        std::cout << "bomb activated" << std::endl;
    }
}

void Bomb::tickFuse(){
    fuse--;
    if (fuse == 0){
        active = false;
        exploded = true;
    }
}

bool Bomb::isBoom(){
    return exploded;
}

bool Bomb::isActive(){
    return active;
}

bool Bomb::startDefusing(){
    // aca hay que chequear si esta cerca de la bomba
    defusing = true;
    return true;
}

void Bomb::tickDefuse(){
    defusingTicks++;
    if (defusingTicks == plantingCooldown){
        defused = true;
        std::cout << "bomb defused" << std::endl;
    }
}

bool Bomb::isDefusing(){
    return defusing;
}

bool Bomb::isDefused(){
    return defused;
}


void Bomb::reset(){
    planting = false;
    defusing = false;
    defused = false;
    active = false;
    exploded = false;
    plantingTicks = 0;
    defusingTicks = 0;
    fuse = 300;
}
