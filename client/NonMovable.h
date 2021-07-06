#ifndef TILE_H
#define TILE_H


#include "Renderizable.h"

class NonMovable : public Renderizable{
private:
    int rescaling;
public:
    NonMovable(SdlTexture& texture,
         int sizeW,
         int sizeH,
         float posX,
         float posY);

    NonMovable(SdlTexture& texture,
               int sizeW,
               int sizeH,
               float posX,
               float posY,
               int rescaling);


    void render(Camera &camera, size_t iteration) override;

    NonMovable(const NonMovable& other) = delete;
    NonMovable& operator=(const NonMovable& other) = delete;

    NonMovable(NonMovable&& other) noexcept;
    NonMovable& operator=(NonMovable&& other) noexcept;

    ~NonMovable() override;

};


#endif
