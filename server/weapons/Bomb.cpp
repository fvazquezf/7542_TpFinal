#include "Bomb.h"
#include <iostream>

Bomb::Bomb(int range, int spread, int damage, int firerate, int fuse, int activateTime, int bounty):
 Weapon(BOMB, 0, range, damage, bounty),
 firerate(firerate),
 spread(spread) {
    state = INACTIVE;
    planter = -1;
    plantingCooldown = activateTime;
    plantingTicks = 0;
    defusingTicks = 0;
    this->fuse = fuse;
    remainingTime = fuse;
    explosionRange = 10;
    position = b2Vec2(0, 0);
}

Bomb::~Bomb() {
}

bool Bomb::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy) {
    double dist = static_cast<double>((player - enemy).Length());
    if (dist < range) {
        int res = static_cast<int>(atan2(enemy.y - player.y, enemy.x - player.x));
        int enemyAngle = res * 180/3.14 + 90;
        if (enemyAngle < 0) {
            enemyAngle += 360;
        }
        int start = (angle) - spread;
        int end = (angle) + spread;
        if (start < end) {
            return (start < enemyAngle && enemyAngle < end);
        } else {
            if (start < enemyAngle) return true;
            if (end > enemyAngle) return true;
        }
    }
    return false;
}


int Bomb::hit() {
    return damage;
}

bool Bomb::canShoot(bool isAttacking) {
    if (cooldown == 0 && isAttacking) {
        cooldown = firerate;
        return true;
    } else {
        return false;
    }
}

void Bomb::resetCooldown() {
    cooldown = 0;
}

int Bomb::getClip() {
    return -1;
}

void Bomb::startPlanting(int id, const b2Vec2& pos) {
    if (state == INACTIVE) {
        state = PLANTING;
        planter = id;
        position = pos;
    }
}

void Bomb::stopPlanting() {
    if (state == PLANTING) {
        state = INACTIVE;
        plantingTicks = 0;
    }
}

void Bomb::startDefusing() {
    if (state == ACTIVE) {
        state = DEFUSING;
    }
}

void Bomb::stopDefusing() {
    if (state == DEFUSING) {
        state = ACTIVE;
        defusingTicks = 0;
    }
}

int Bomb::tic() {
    switch (state) {
        case PLANTING: {
            plantingTicks++;
            if (plantingTicks == plantingCooldown) {
                state = ACTIVE;
                return ACTIVATE;
            }
            return state;
        }
        case DEFUSING: {
            remainingTime--;
            if (remainingTime == 0) {
                state = EXPLODED;
            }
            defusingTicks++;
            if (defusingTicks == plantingCooldown) {
                state = DEFUSED;
            }
            return state;
        }
        case ACTIVE: {
            remainingTime--;
            if (remainingTime == 0) {
                state = EXPLODED;
            }
            return state;
        }
        default: 
            return INACTIVE;
    }
}

bool Bomb::explosionDamage(const b2Vec2& victim) {
    double dist = static_cast<double>((victim - position).Length());
    if (dist < explosionRange) {
        return true;
    }
    return false;
}


int Bomb::getPlanter() {
    return planter;
}

int Bomb::getFuse() {
    return (fuse/60);
}

int Bomb::getState() {
    return state;
}

void Bomb::reset() {
    state = INACTIVE;
    plantingTicks = 0;
    defusingTicks = 0;
    remainingTime = fuse;
}
