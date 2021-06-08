#include "Terrorist.h"
#include <cmath>

#define PI 3.1416f

Terrorist::Terrorist(SdlTexture& texture, int posX, int posY)
:
  animation(texture, 1, 32),
  posX(posX),
  posY(posY){
  	movingLeft = false;
  	movingRight = false;
  	movingUp = false;
  	movingDown = false;
  	scrolling = false;
  	shooting = false;
  	angle = 0.0;
  	knifeAngle = 0.0;
}

void Terrorist::moveLeft(){
	movingLeft = true;
}

void Terrorist::moveRight(){
  	movingRight = true;
}

void Terrorist::moveUp(){
  	movingUp = true;
}

void Terrorist::moveDown(){
  	movingDown = true;
}

void Terrorist::scroll() {
    scrolling = true;
}

void Terrorist::stopMoving(){
	movingDown = movingUp = movingLeft = movingRight = scrolling = false;
}

void Terrorist::render(){
	Area src(0, 0, 32, 32);
	Area dst(posX, posY, 32, 32);
	animation.render(src, dst, angle + knifeAngle,SDL_FLIP_NONE);
}

void Terrorist::update(float dt){
	if (movingLeft) {
        posX -= 2;
    }
	if (movingRight){
        posX += 2;
	}
    if (movingUp){
        posY -= 2;
    }
	if (movingDown){
		posY += 2;
	}
	if (scrolling){
        int x, y = 0;
        SDL_GetMouseState(&x, &y);
        angle = atan2f((float) (posY - y), (float) (posX - x)) * 180.0f / PI - 90.0f;
	}
	if (shooting && knifeAngle < 50){
	    knifeAngle += 15;
	}
	if (!shooting && knifeAngle > 0){
	    knifeAngle -= 5;
	}
	animation.update(dt);
}

Terrorist::~Terrorist(){
}

void Terrorist::gunAction() {
    shooting = true;
}

void Terrorist::stopGunAction() {
    shooting = false;
    knifeAngle = 0;
}

