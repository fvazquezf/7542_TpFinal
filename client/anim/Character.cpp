#include "Character.h"
#include "../Camera.h"
#include <iostream>

#define PI 3.1416f

Character::Character(SdlTexture &texture,
                     float posX,
                     float posY,
                     bool player,
                     std::map<uint8_t, SdlTexture> &weapons,
                     SdlTexture& blood)
: Renderizable(texture, posX, posY),
  player(player),
  weapon(weapons),
  bloodAnimation(blood, 16, 4, 4, 32),
  currentBleedIteration(0){
    bloodAnimation.stay();
    // necesito este metodo pq
    // el blood splatter corresponde
    // al frame 8 en adelante de la imagen
    bloodAnimation.renderFromFrame(8);
}

void Character::render(Camera &cam, uint8_t iteration) {
    if (player){
        cam.setLogicalCenter(posX, posY);
        cam.renderAtCenter(texture, angle, 32, 32);
        weapon.draw(posX, posY, angle, cam);
    } else {
        cam.renderInSight(texture, posX, posY, angle, 32, 32);
        weapon.draw(posX, posY, angle, cam);
    }

    if (bleeding){
        currentBleedIteration++;
        bloodAnimation.renderOld(cam);
        if (currentBleedIteration == 1024){
            bleeding = false;
            currentBleedIteration = 0;
            bloodAnimation.reset();
        }
    }

    if (wasHit){
        bloodAnimation.render(cam, posX, posY, angle, iteration);
        wasHit = false;
        bleeding = true;
    }
}

void Character::update(){
}

Character::~Character() {
}

Character::Character(Character &&other) noexcept
: Renderizable(std::move(other)),
  player(other.player),
  weapon(std::move(other.weapon)),
  bloodAnimation(other.bloodAnimation){

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
}
