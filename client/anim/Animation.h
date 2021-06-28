#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <queue>
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
              int sizeH,
              bool center);

    // square frames
    Animation(SdlTexture& texture, int numFrames, int framesW, int framesH, int size, bool center);

    void render(Camera& cam, float x, float y, float angle, uint8_t iteration);
    void stay();
    void renderFromFrame(int nFrame);
    void reset();

    ~Animation();

    bool renderOld(Camera &camera, int maxNumFrames);

    // renderiza unicamente la current frame
    std::tuple<float, float, int16_t> renderOne(Camera& camera,
                                                float posX,
                                                float posY,
                                                int16_t angle);

    void renderFor(Camera& cam, float posX, float posY, int16_t angle, uint8_t iteration);

    void renderOneAndKeep(Camera& camera, float posX, float posY);

    void advanceFrame();

    void offsetRenderState(std::tuple<float, float, int16_t> newOffset);

    void setCurrentFrame(uint8_t newFrame);

    // reescaling factor
    void rescale(float factor);

    void setTicksToChange(uint8_t ticks);
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
    std::vector<std::tuple<float, float, int, SDL_Rect>> oldRenders;

    // queue de updates de offset en el frame actual
    std::queue<std::tuple<float, float, int16_t>> modifiedState;

    bool shouldStay = false;

    // en vez de animar desde el frame 0
    // empiezo desde frameOffset
    int frameOffset;

    bool center;

    int ticksToChangeFrame;
};


#endif
