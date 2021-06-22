#ifndef CAMERA_H
#define CAMERA_H

#include "sdlwrap/SdlWindow.h"
#include "sdlwrap/SdlTexture.h"
#include "anim/Renderizable.h"

// 32 pixeles (tamaño de tile) <-> 1 metro logico (server)
#define M_TO_P 32

class Camera{
private:
    SdlWindow& window;
    // center width and height
    // depends on screen resolution
    SDL_Point centerPix;

    float logicalCenterX;
    float logicalCenterY;

    int width;
    int height;

public:
    Camera(SdlWindow& window);

    // recibiria primero al player
    // luego al resto de las entidades
    void render(Renderizable& renderizable);

    // renders texture at the center of the screen
    // only for player
    void renderAtCenter(SdlTexture& texture, float angle,
                        int sizeX, int sizeY);

    void setLogicalCenter(float x, float y);

    // checks if the given logical coordinate pair
    // is in sight of the player
    // should render only if both shield true
    bool isVisibleInX(float x);
    bool isVisibleInY(float y);

    // logical coordinates
    // only renders if visible to player
    void renderInSight(SdlTexture& texture, float x,
                       float y, float angle,
                       int sizeX, int sizeY);

    ~Camera();

    int16_t angleFromMouse();
};

#endif
