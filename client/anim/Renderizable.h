#ifndef RENDERIZABLE_H
#define RENDERIZABLE_H
#include "../sdlwrap/SdlTexture.h"

class Camera;

class Renderizable {
protected:
    SdlTexture& texture;
    float posX;
    float posY;
public:
    explicit Renderizable(SdlTexture& texture, float posX, float posY);

    virtual void update() = 0;
    void updatePosition(float x, float y);
    virtual void render(Camera& camera) = 0;

    virtual ~Renderizable();
};


#endif
