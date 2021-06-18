#include "Terrorist.h"
#include "../Camera.h"
#include <cmath>
#include <iostream>

#define PI 3.1416f

Terrorist::Terrorist(SdlTexture& texture, float posX, float posY, bool player)
:
  //animation(texture, 1, 32
  Renderizable(texture),
  posX(posX),
  posY(posY),
  player(player){
  	//movingLeft = false;
  	//movingRight = false;
  	//movingUp = false;
  	//movingDown = false;
  	//scrolling = false;
  	//shooting = false;
  	angle = 0.0;
  	//knifeAngle = 0.0;
}

void Terrorist::render(){
	/*Area src(0, 0, 32, 32);
	Area dst(posX, posY, 32, 32);
	animation.render(src, dst, angle + knifeAngle,SDL_FLIP_NONE);*/
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
    if (player){
        posY -= 0.0625f;
    }
}

Terrorist::~Terrorist() {
}

/*void Terrorist::gunAction() {

    shooting = true;
}

void Terrorist::stopGunAction() {
    shooting = false;
    knifeAngle = 0;
}*/
