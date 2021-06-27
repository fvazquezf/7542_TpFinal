#include "Pistol.h"
#include <iostream>

Pistol::Pistol(){
    damage = 20;
    cooldown = 0;
}


Pistol::~Pistol(){

}

bool Pistol::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    if (cooldown != 0) return false;
    double dist = static_cast<double>((player - enemy).LengthSquared());
    // 2500 es la distancia(50m) de ataque al cuadrado, si esta mas lejos no le pega.
    std::cout << "absDist: " << dist << std::endl;
    if (dist < 2500) {

        std::cout << "angle: " << angle << std::endl;

        double y = sin((angle) * 180/3.14) + player.y;
        double x = cos((angle) * 180/3.14)+ player.x;

        b2Vec2 extra(x, y);

        double a = sqrt(dist);
        double b = 1;
        double c = static_cast<double>((extra - enemy).Length());

        double temp = (a*a+b-c*c)/(2*a);

        double lambda = acos((a*a+b-c*c)/(2*a)); 

        std::cout << "posAngle: (" << x << ", " << y << ")" << std::endl;
        std::cout << "posSelf: (" << player.x << ", " << player.y << ")" << std::endl;
        std::cout << "posEnemy: (" << enemy.x << ", " << enemy.y << ")" << std::endl << std::endl;

        // double latDist = abs((enemy.y - a * enemy.x - b)/a);
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;
        std::cout << "c: " << c << std::endl;

        std::cout << "preCos: " << temp << std::endl;


        std::cout << "lambda: " << lambda << std::endl;
        std::cout << std::endl;

        if (lambda < 1){
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

