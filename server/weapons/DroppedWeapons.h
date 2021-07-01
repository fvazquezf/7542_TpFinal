#ifndef DROPPEDWEAPONS_H
#define DROPPEDWEAPONS_H


#include <vector>
#include <cstdint>
#include "../../libs/box2d/include/box2d/b2_math.h"
#include "../Broadcaster.h"

class DroppedWeapons {
private:
    Broadcaster& broadcaster;
    std::vector<std::pair<uint8_t, b2Vec2>> droppedWeapons;
public:
    // avisa si hay una nueva weapon tirada
    explicit DroppedWeapons(Broadcaster& updates);


    void dropWeapon(uint8_t weaponCode, const b2Vec2& position);
    int8_t pickUpAnyIfClose(const b2Vec2& playerPosition);


    ~DroppedWeapons();
};


#endif
