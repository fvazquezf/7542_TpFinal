#ifndef RENDERIZABLE_H
#define RENDERIZABLE_H
#include "../sdlwrap/SdlTexture.h"

class Camera;

class Renderizable {
protected:
    SdlTexture& texture;
public:
    explicit Renderizable(SdlTexture& texture);

    virtual void update() = 0;
    virtual void render(Camera& camera) = 0;

    virtual ~Renderizable();
};


#endif
