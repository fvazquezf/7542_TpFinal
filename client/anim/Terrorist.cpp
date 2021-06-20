#include "Terrorist.h"
#include "../Camera.h"
#include <cmath>
#include <iostream>

#define PI 3.1416f

Terrorist::Terrorist(SdlTexture& texture, float posX, float posY, bool player)
: Renderizable(texture, posX, posY),
  player(player){
  	angle = 0.0;
}

void Terrorist::render(Camera& cam){
    if (player){
        cam.setLogicalCenter(posX, posY);
        cam.renderAtCenter(texture, angle, 32, 32);
    } else {
        cam.renderInSight(texture, posX, posY, angle, 32, 32);
    }
}

void Terrorist::update(){
}

Terrorist::~Terrorist() {
}
