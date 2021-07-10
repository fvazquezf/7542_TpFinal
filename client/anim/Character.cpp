#include "Character.h"
#include "../Camera.h"
#include <iostream>
#include "../SoundManager.h"

#define PI 3.1416f

Character::Character(SdlTexture &texture,
                     float posX,
                     float posY,
                     bool player,
                     std::map<uint8_t, SdlTexture> &weapons,
                     SdlTexture& blood,
                     SdlTexture& legs)
: Renderizable(texture, 32, 32, posX, posY),
  player(player),
  bleeding(false),
  wasHit(false),
  moving(false),
  lastIter(0),
  weapon(weapons),
  movementAnimation(texture, 6, 2, 3, 32, 32),
  bloodAnimation(blood, 16, 4, 32),
  legAnimation(legs, 6, 3, 2, 32, 32),
  currentMovingUpdates(0){
    movementAnimation.renderFromFrame(0);
    bloodAnimation.renderFromFrame(8);
    weaponCharacterFrameMap = {
            {KNIFE, 0},
            {PISTOL, 3},
            {AK47, 4},
            {M3, 4},
            {AWP, 4},
            {BOMB, 4},
    };
    weapon.changeWeapon(KNIFE);
    legAnimation.setTicksToChange(15);
}

void Character::render(Camera &cam, size_t iteration) {
    if (player){
        cam.setLogicalCenter(posX, posY);
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
  legAnimation(std::move(other.legAnimation)),
  weaponCharacterFrameMap(std::move(other.weaponCharacterFrameMap)),
  currentMovingUpdates(other.currentMovingUpdates){
    other.player = false;
}

Character &Character::operator=(Character &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    player = other.player;
    other.player = false;
    weapon = std::move(other.weapon);
    movementAnimation = std::move(other.movementAnimation);
    bloodAnimation = std::move(other.bloodAnimation);
    legAnimation = std::move(other.legAnimation);
    weaponCharacterFrameMap = std::move(other.weaponCharacterFrameMap);
    currentMovingUpdates = other.currentMovingUpdates;

    return *this;
}

void Character::die(float distanceToCenter) {
    SoundManager::playSound(SoundManager::soundRepertoire::DIE1, distanceToCenter);
}

void Character::hit() {
    wasHit = true;
    bleeding = true;
    SoundManager::playSound(SoundManager::soundRepertoire::HIT1, 0);
}

void Character::attack() {
    weapon.animate(*this, posX, angle);
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
        currentMovingUpdates = 0;
    }
    if (moving){
        ++currentMovingUpdates;
        if ((currentMovingUpdates % 25) == 0){
            SoundManager::playSound(SoundManager::STEP1, 0);
        }
    }
    Renderizable::updatePosition(x, y);
}

std::pair<float, float> Character::getPosition() {
    return {posX, posY};
}
