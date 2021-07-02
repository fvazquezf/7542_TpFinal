#include "Camera.h"
#include <iostream>
#include "Renderizable.h"
#include <cmath>
#define PI 3.141593f

Camera::Camera(SdlWindow& window)
: window(window),
  logicalCenterX(-100),
  logicalCenterY(-100) {
    centerPix = window.getCenter();
    width = 2*centerPix.x;
    height = 2*centerPix.y;
}

void Camera::render(Renderizable &renderizable, size_t iteration) {
    // renderizable.render(this) -> double dispatch
    // cada textura se debe renderizar segun su tipo
    // si no usamos double dispatch tenemos todos getters
    renderizable.render(*this, iteration);
}

// logical coordinates
// should only render if visible to player
void Camera::renderInSight(SdlTexture& texture,
                           Area& src,
                           float posX,
                           float posY,
                           float angle){
    auto rect = src.buildRectangle();
    int newX = centerPix.x - (logicalCenterX - posX) * M_TO_P;
    int newY = centerPix.y - (logicalCenterY - posY) * M_TO_P;
    Area dst(newX - (rect.w / 2),
             newY - (rect.h / 2),
             rect.w, rect.h);
    texture.render(src, dst, angle, SDL_FLIP_NONE);
}

bool Camera::isVisibleInX(float x){
    auto pixelX = abs(logicalCenterX - x) / M_TO_P;
    return (pixelX >= 0 && pixelX <= width);
}

bool Camera::isVisibleInY(float y){
    auto pixelY = abs(logicalCenterY - y) / M_TO_P;
    return (pixelY >= 0 && pixelY <= height);
}

bool Camera::isVisible(float x, float y){
    return isVisibleInX(x) && isVisibleInY(y);
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

void
Camera::renderWeapon(float playerX,
                     float playerY,
                     int16_t playerAngle,
                     int sizeX,
                     int sizeY,
                     SdlTexture &texture) {
    if (isVisibleInX(playerX) && isVisibleInY(playerY)){
        Area src(0, 0, sizeX, sizeY);
        int newX = centerPix.x - (logicalCenterX - playerX) * M_TO_P;
        int newY = centerPix.y - (logicalCenterY - playerY) * M_TO_P;
        Area dst(newX - (sizeX / 2),
                 newY - (sizeY / 2),
                 sizeX, sizeY);
        SDL_Point center{sizeX/2, sizeY};
        texture.render(src, dst, playerAngle,center,SDL_FLIP_NONE);
    }
}

void Camera::renderWithAlpha(SdlTexture &texture, Area &source, float x, float y, uint8_t alpha) {
    auto rect = source.buildRectangle();
    int newX = centerPix.x - (logicalCenterX - x) * M_TO_P;
    int newY = centerPix.y - (logicalCenterY - y) * M_TO_P;
    Area dst(newX - rect.w/2,
             newY - rect.h/2,
             rect.w,
             rect.h);
    texture.render(source, dst, alpha);
}
