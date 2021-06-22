#include "Camera.h"
#include <iostream>
#include "anim/Renderizable.h"
#include <cmath>
#define PI 3.141593f

Camera::Camera(SdlWindow& window)
: window(window),
  logicalCenterX(-100),
  logicalCenterY(-100) {
    centerPix = std::move(window.getCenter());
}

void Camera::render(Renderizable& renderizable){
    // renderizable.render(this) -> double dispatch
    // cada textura se debe renderizar segun su tipo
    // si no usamos double dispatch tenemos todos getters
    renderizable.render(*this);
}

// renders texture at the center of the screen
// only for player
void Camera::renderAtCenter(SdlTexture& texture, float angle,
                    int sizeX, int sizeY){
    Area src(0, 0, sizeX, sizeY);
    // dibuja desde el centro!
    Area dst(centerPix.x - (sizeX / 2), centerPix.y - (sizeY / 2), sizeX, sizeY);
    texture.render(src, dst, angle, SDL_FLIP_NONE);
}

// logical coordinates
// only renders if visible to player
void Camera::renderInSight(SdlTexture& texture, float x, float y,
                           float angle, int sizeX, int sizeY){
    if (isVisibleInX(x) && isVisibleInY(y)){
        Area src(0, 0, sizeX, sizeY);
        int newX = centerPix.x - (logicalCenterX - x) * M_TO_P;
        int newY = centerPix.y - (logicalCenterY - y) * M_TO_P;
        Area dst(newX - (sizeX / 2),
                 newY - (sizeY / 2),
                 sizeX, sizeY);
        texture.render(src, dst, angle, SDL_FLIP_NONE);
    }
    // si no es visible no hago nada jajaja xd
}

bool Camera::isVisibleInX(float x){
    return (x >= logicalCenterX - (logicalCenterX / 2)) && (x <= logicalCenterX + (logicalCenterX/2));
}

bool Camera::isVisibleInY(float y){
    return (y >= logicalCenterY - (logicalCenterY/2)) && (y <= logicalCenterY + (logicalCenterY/2));
}

void Camera::setLogicalCenter(float x, float y){
    logicalCenterX = x;
    logicalCenterY = y;
}

Camera::~Camera(){
}

int16_t Camera::angleFromMouse() {
    int x, y = 0;
    SDL_GetMouseState(&x, &y);
    float angle = SDL_atan2(y - centerPix.y, x - centerPix.x) * (180.000f / PI) + 90;
    if (angle < 0){
        angle = 360 + angle;
    }
    return angle;
}
