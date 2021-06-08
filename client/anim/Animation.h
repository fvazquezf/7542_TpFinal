#ifndef ANIMATION_H
#define ANIMATION_H

#include "../sdlwrap/SdlTexture.h"
#include "../sdlwrap/Area.h"
#define FRAMERATE 1000000.0f / 60.0f

class Animation {
public:
    Animation(const SdlTexture &texture, int numFrames, int size);

    ~Animation();

    void update(float dt);

    void render(const Area& src, const Area& dst, const SDL_RendererFlip &flipType);
    void render(const Area& src, const Area& dst, float angle, const SDL_RendererFlip &flipType);

protected:
    // metodo que avanza el frame
    void advanceFrame();

    // textura del sprite
    const SdlTexture &texture;

    // frame siendo renderizado
    int currentFrame;

    // numero de frames en el sprite
    int numFrames;

    // size de un frame
    int size;

    // tiempo transcurrido desde el ultimo update
    float elapsed;

    // cuantos frames hay en la direccion vertical
    int numFramesH;

    // cuantos frames hay en la direccion horizontal
    int numFramesW;
};


#endif 