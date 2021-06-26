#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "../sdlwrap/SdlTexture.h"
#include "../sdlwrap/Area.h"
#include "../Camera.h"

#define FRAMERATE 1000000 / 60

class Animation {
public:
    Animation(SdlTexture &texture,
              int numFrames,
              int framesW,
              int framesH,
              int sizeW,
              int sizeH);

    // square frames
    Animation(SdlTexture& texture, int numFrames, int framesW, int framesH, int size);

    void render(Camera& cam, float x, float y, float angle, uint8_t iteration);
    void stay();
    void renderFromFrame(int nFrame);
    void reset();

    ~Animation();

    void renderOld(Camera &camera);

protected:
    // textura del sprite
    SdlTexture &texture;

    // frame siendo renderizado
    int currentFrame;

    // numero de frames en el sprite
    int numFrames;

    int sizeW;
    int sizeH;

    // cuantos frames hay en la direccion vertical
    int numFramesH;

    // cuantos frames hay en la direccion horizontal
    int numFramesW;

    // vector de frames para una animacion
    std::vector<SDL_Rect> frames;

    // posiciones para renderizar las animaciones viejas
    // durante x tiempo
    std::vector<std::tuple<float, float, SDL_Rect>> renderCoordinates;

    bool shouldStay = false;

    // en vez de animar desde el frame 0
    // empiezo desde frameOffset
    int frameOffset;
};


#endif
