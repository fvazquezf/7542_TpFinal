#ifndef DROPPEDWEAPONS_H
#define DROPPEDWEAPONS_H


#include <vector>
#include <cstdint>
#include "../../libs/box2d/include/box2d/b2_math.h"
#include "../Broadcaster.h"

// uniquifier es unico entre demasiadas comillas,
// pero es un identificador de arma (puede que haya 2 dropeadas en la misma posicion
// como sabe el cliente cual dejar de dibujar? a traves del uniquifier
class DroppedWeapons {
private:
    size_t uniquifier;
    Broadcaster& broadcaster;
    std::vector<std::tuple<uint8_t, size_t, b2Vec2>> droppedWeapons;
public:
    // avisa si hay una nueva weapon tirada
    explicit DroppedWeapons(Broadcaster& updates);

    DroppedWeapons(const DroppedWeapons& other) = delete;
    DroppedWeapons& operator=(const DroppedWeapons& other) = delete;

    DroppedWeapons(DroppedWeapons&& other) ;
    DroppedWeapons& operator=(DroppedWeapons&& other) ;

    void dropWeapon(uint8_t weaponCode, const b2Vec2& position);
    int8_t pickUpAnyIfClose(const b2Vec2& playerPosition);


    ~DroppedWeapons();
};


#endif
