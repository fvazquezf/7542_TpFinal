#ifndef RENDERIZABLE_H
#define RENDERIZABLE_H
#include "../sdlwrap/SdlTexture.h"

class Camera;

class Renderizable {
protected:
    SdlTexture& texture;
    float posX;
    float posY;
    int16_t angle;
public:
    explicit Renderizable(SdlTexture& texture, float posX, float posY);

    virtual void update() = 0;
    void updatePosition(float x, float y);
    void updateAngle(int16_t newAngle);
    virtual void render(Camera& camera) = 0;

    virtual ~Renderizable();
};


#endif
