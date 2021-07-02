#ifndef RENDERIZABLE_H
#define RENDERIZABLE_H
#include "sdlwrap/SdlTexture.h"

class Camera;

class Renderizable {
protected:
    SdlTexture& texture;
    int sizeW;
    int sizeH;
    float posX;
    float posY;
    int16_t angle;
public:
    explicit Renderizable(SdlTexture& texture,
                          int sizeW,
                          int sizeH,
                          float posX,
                          float posY);

    Renderizable(const Renderizable& other) = delete;
    Renderizable& operator=(const Renderizable& other) = delete;

    Renderizable(Renderizable&& other) noexcept;
    Renderizable& operator=(Renderizable&& other) noexcept;

    virtual void updatePosition(float x, float y);
    void updateAngle(int16_t newAngle);
    virtual void render(Camera &camera, size_t iteration) = 0;

    virtual ~Renderizable();
};


#endif
