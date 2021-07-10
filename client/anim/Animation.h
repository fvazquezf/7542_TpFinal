#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <queue>
#include "../sdlwrap/SdlTexture.h"
#include "../sdlwrap/Area.h"
#include "../Camera.h"

// Fijo?
#define FRAMERATE 1000000 / 60

class Animation {
public:
    Animation(SdlTexture &texture,
              int numFrames,
              int framesW,
              int framesH,
              int sizeW,
              int sizeH,
              bool center);

    // square frames
    Animation(SdlTexture& texture, int numFrames, int framesW, int framesH, int size, bool center);

    void render(Camera& cam, float x, float y, float angle, size_t iteration);
    void renderFromFrame(int nFrame);

    ~Animation();

    bool renderOld(Camera &camera, int maxNumFrames);

    // renderiza unicamente la current frame
    std::tuple<float, float, int16_t> renderOne(Camera& camera,
                                                float posX,
                                                float posY,
                                                int16_t angle);

    void renderFor(Camera& cam, float posX, float posY, int16_t angle, size_t iteration);

    void renderOneAndKeep(Camera& camera, float posX, float posY);

    void advanceFrame();

    void offsetRenderState(std::tuple<float, float, int16_t> newOffset);

    void setCurrentFrame(uint8_t newFrame);

    void setTicksToChange(size_t ticks);
    void setStartingIteration(size_t iter);
protected:
    // textura del sprite
    SdlTexture &texture;

    // frame siendo renderizado
    size_t currentFrame;

    // numero de frames en el sprite
    size_t numFrames;

    int sizeW;
    int sizeH;

    // cuantos frames hay en la direccion vertical
    size_t numFramesH;

    // cuantos frames hay en la direccion horizontal
    size_t numFramesW;

    // vector de frames para una animacion
    std::vector<SDL_Rect> frames;

    // posiciones para renderizar las animaciones viejas
    // durante x tiempo
    std::vector<std::tuple<float, float, int, SDL_Rect>> oldRenders;

    // queue de updates de offset en el frame actual
    std::queue<std::tuple<float, float, int16_t>> modifiedState;

    // en vez de animar desde el frame 0
    // empiezo desde frameOffset
    int frameOffset;

    bool center;

    int ticksToChangeFrame;
    size_t startingFrom;
};


#endif
