#include "Terrorist.h"
#include "../Camera.h"
#include <iostream>

#define PI 3.1416f

Terrorist::Terrorist(SdlTexture &texture,
                     float posX,
                     float posY,
                     bool player,
                     std::map<uint8_t, SdlTexture> &weapons)
: Renderizable(texture, posX, posY),
  player(player),
  weapon(weapons){
}
void Terrorist::render(Camera &cam, uint8_t iteration) {
    if (player){
        cam.setLogicalCenter(posX, posY);
        cam.renderAtCenter(texture, angle, 32, 32);
        weapon.draw(posX, posY, angle, cam);
    } else {
        cam.renderInSight(texture, posX, posY, angle, 32, 32);
        weapon.draw(posX, posY, angle, cam);
    }
}

void Terrorist::update(){
}

Terrorist::~Terrorist() {
}
