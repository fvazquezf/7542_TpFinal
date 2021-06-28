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

        //double y = sin((angle) * 180/3.14) + player.y;
        //double x = cos((angle) * 180/3.14)+ player.x;

        // la transformacion de ejes es (sin(angulo), -cos(angulo))
        // usar los angulos 0 90 180 270 para ver que las dirreciones
        // coinciden con los ejes estilo sdl2

        // direcciones en x y en y del vector de la bala
        b2Vec2 bulletDirectionVector(sin(angle * 3.14/180.0f), -cos(angle * 3.14/180.0f));
        std::cout << bulletDirectionVector.x << " " << bulletDirectionVector.y << "\n";

        double bulletX = player.x;
        double bulletY = player.y;

        b2Vec2 bulletPosition(bulletX, bulletY);

        // se podria calcular una sola vez
        // despues iterar por todos los players
        // ver cual esta mas cerca y ademas si esta en distancia de hit
        // y pegarle a ese
        double oldDist = INFINITY;
        double currDist = 0;
        for (size_t i = 0; i < 100; ++i){
            // trayectoria de una recta con origen en la posicion del jugador
            // viaja en la direccion de disparo
            bulletPosition.operator+=(bulletDirectionVector);
            // hitbox
            if ((currDist = (bulletPosition - enemy).Length()) < 0.5) {
                return true;
            }
            // si me aleje, entonces no le voy a pegar
            if (oldDist < currDist){
                return false;
            }
            oldDist = currDist;
        }
        return false;
        /*double x = sin(angle / 3.14) + player.x;
        double y = -cos(angle / 3.14) + player.y;

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
        // }*/
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

