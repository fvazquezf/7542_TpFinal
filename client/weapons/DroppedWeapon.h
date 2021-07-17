#ifndef DROPPEDWEAPON_H
#define DROPPEDWEAPON_H


#include <map>
#include "../sdlwrap/SdlTexture.h"
#include "../NonMovable.h"

class DroppedWeapon {
private:
    std::map<uint8_t, std::pair<int, int>> droppedSizes = {
            {0, {64, 32}},
            {1, {64, 32}},
            {2, {64, 32}},
            {5, {24, 24}}
    };
    uint8_t weaponTypeId;
    size_t uniqueId;
    NonMovable droppedDrawable;
    int16_t posXmm;
    int16_t posYmm;
    bool show;
public:
    DroppedWeapon(SdlTexture& texture, uint8_t weaponType, size_t uniqueId, int16_t posX, int16_t posY);

    DroppedWeapon(const DroppedWeapon& other) = delete;
    DroppedWeapon& operator=(const DroppedWeapon& other) = delete;

    DroppedWeapon(DroppedWeapon&& other) ;
    DroppedWeapon& operator=(DroppedWeapon&& other) ;

    bool isWeaponTypeAndId(uint8_t weaponType, size_t uniqueId);

    void draw(Camera& cam);

    ~DroppedWeapon();

    void doNotShow();

    std::pair<float, float> getPosition();
};


#endif
