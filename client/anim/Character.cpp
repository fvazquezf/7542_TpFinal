#include "Character.h"
#include "../Camera.h"
#include <iostream>

#define PI 3.1416f

Character::Character(SdlTexture &texture,
                     float posX,
                     float posY,
                     bool player,
                     std::map<uint8_t, SdlTexture> &weapons,
                     SdlTexture& blood,
                     SdlTexture& legs)
: Renderizable(texture, posX, posY),
  player(player),
  bleeding(false),
  wasHit(false),
  moving(false),
  lastIter(0),
  weapon(weapons),
  movementAnimation(texture, 6, 2, 3, 32, player),
  bloodAnimation(blood, 16, 4, 4, 32, false),
  legAnimation(legs, 6, 3, 2, 32, false){
    movementAnimation.renderFromFrame(0);
    bloodAnimation.renderFromFrame(8);
    weaponCharacterFrameMap = {
            {KNIFE, 0},
            {PISTOL, 3},
            {AK47, 4},
            {AWP, 4},
            {BOMB, 4},
    };
    weapon.changeWeapon(KNIFE);
    legAnimation.setTicksToChange(15);
}

void Character::render(Camera &cam, size_t iteration) {
    if (player){
        cam.setLogicalCenter(posX, posY);
    } else {
        if (!cam.isVisible(posX, posY)){
            return;
        }
    }

    if (moving){
        legAnimation.renderFor(cam, posX, posY + 0.2, 0, iteration);
    }

    if (bleeding){
        bleeding = bloodAnimation.renderOld(cam, 255);
    }

    auto offset = movementAnimation.renderOne(cam, posX, posY, angle);
    weapon.draw(posX + std::get<0>(offset),
            posY + std::get<1>(offset),
            angle + std::get<2>(offset),
                    cam);
    if (wasHit){
        bloodAnimation.renderOneAndKeep(cam, posX + std::get<0>(offset), posY + std::get<0>(offset));
        bloodAnimation.advanceFrame();
        wasHit = false;
    }
    lastIter = iteration;
}

Character::~Character() {
}

Character::Character(Character &&other) noexcept
: Renderizable(std::move(other)),
  player(other.player),
  weapon(std::move(other.weapon)),
  movementAnimation(std::move(other.movementAnimation)),
  bloodAnimation(std::move(other.bloodAnimation)),
  legAnimation(std::move(other.legAnimation)){
    other.player = false;
}

Character &Character::operator=(Character &&other) noexcept {
    if (this == &other){
        return *this;
    }

    player = other.player;
    other.player = false;

    weapon = std::move(other.weapon);
    return *this;
}

void Character::die() {
    // play random dead sound
    // drop weapons in place
}

void Character::hit() {
    wasHit = true;
    bleeding = true;
}

void Character::attack() {
    weapon.animate(*this, posX, posY, angle);
}

void Character::pushPositionOffset(std::tuple<float, float, int> positionOffset) {
    movementAnimation.offsetRenderState(std::move(positionOffset));
}

void Character::changeWeapon(uint8_t weaponCode) {
    if (weapon.changeWeapon(weaponCode)){
        movementAnimation.setCurrentFrame(weaponCharacterFrameMap.at(weaponCode));
    }
}

void Character::updatePosition(float x, float y) {
    float diffX = abs(posX - x);
    float diffY = abs(posY - y);
    if (!moving && ((diffX > 0.005) || (diffY > 0.005))){
        moving = true;
        legAnimation.setStartingIteration(lastIter + 1);
    } else if (moving && ((diffX < 0.005) && (diffY < 0.005))){
        moving = false;
    }
    Renderizable::updatePosition(x, y);
}
