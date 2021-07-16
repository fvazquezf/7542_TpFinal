#include "Pistol.h"
#include <iostream>

Pistol::Pistol(int ammo, int range, int accuracy, int damage)
: Weapon(PISTOL, ammo, range, damage){
    this->accuracy = static_cast<double>(accuracy)/100;
}


Pistol::~Pistol(){

}

bool Pistol::attack(const b2Vec2& player, int16_t angle, const b2Vec2& enemy){
    b2Vec2 bulletPosition(player);
    b2Vec2 bulletDirection(sin(angle * 3.14f/180.0f), -cos(angle * 3.14f/180.0f));
    double oldDist = INFINITY;
    double currDist;
    double bulletTravelledDistance = 0;

    while (bulletTravelledDistance < range){
        // la transformacion de ejes es (sin(angulo), -cos(angulo))
        // usar los angulos 0 90 180 270 para ver que las dirreciones
        // coinciden con los ejes estilo sdl2

        // trayectoria de una recta con origen en la posicion del jugador
        // viaja en la direccion de disparo
        bulletPosition.operator+=(bulletDirection);
        bulletTravelledDistance += bulletDirection.Length();
        // pasar el 0.5 a accuracy
        if ((currDist = (bulletPosition - enemy).Length()) < accuracy) {
            return true;
        }
        if (oldDist < currDist){
            return false;
        }
        oldDist = currDist;
    }
    return false;
}

int Pistol::hit(){
    return damage;
}

bool Pistol::canShoot(bool isAttacking){
    if (cooldown == 0 && clip != 0 && isAttacking) {
        clip--;
        cooldown = 80000; // Mas ticks que en 10 rondas -> casi infinito
        return true;
    } else {
        return false;
    }
}

void Pistol::resetCooldown(){
    cooldown = 0;
}
