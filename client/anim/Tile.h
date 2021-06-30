#ifndef TILE_H
#define TILE_H


#include "Renderizable.h"

class Tile : public Renderizable{
public:
    Tile(SdlTexture& texture, float posX, float posY);

    void render(Camera &camera, size_t iteration) override;

    Tile(const Tile& other) = delete;
    Tile& operator=(const Tile& other) = delete;

    Tile(Tile&& other) noexcept;
    Tile& operator=(Tile&& other) noexcept;

    ~Tile() override;

};


#endif
