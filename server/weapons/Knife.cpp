#include "Knife.h"

Knife::Knife(){
    damage = 40;
    cooldown = 0;
}


Knife::~Knife(){

}

bool Knife::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;
    double dist = static_cast<double>((player - enemy).LengthSquared());
    // 1.25 es la distancia(1.11m) de ataque al cuadrado, si esta mas lejos no le pega.
    if (dist < 1.25) {
        int res = static_cast<int>(atan2(enemy.y - player.y, enemy.x - player.x));
        // el round creo que esta de mas
        int enemyAngle = res * 180/3.14 + 90;
        if (enemyAngle < 0){
            enemyAngle += 360;
        }
        int start = (angle) - 60;
        int end = (angle) + 60;
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

